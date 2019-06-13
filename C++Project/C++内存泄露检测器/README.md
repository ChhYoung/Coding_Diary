# C++ 实现内存泄露检查器

[TOC]

## 1.  基础知识：

1. 动态内存 和 静态内存：

   ​	静态内存分配在栈区，使用后自动释放，不会产生内存泄露问题，如` int a = 10;`

   ​    动态内存分配在堆区，有程序员自己管理分配与释放，`int* m = new int(10); delete m;`

    若在调用`new`后不调用`delete`释放内存则会引起内存泄露,由动态内存分配引起
   
2. 内存泄露：在现代操作系统中，程序执行完后，为释放的内存会被系统回收，所以一个短暂运行的程序导致的内存泄露不会产生较大的影响。 但在服务器上运行的程序，因为会已知保持运行状态，所以一旦有内存泄露的逻辑，将很可能造成泄露的内存增加，降低计算机性能。


## 2. 编写测试代码

- 在`main.cpp`中执行测试,代码如下

```c++
#include<iostream>
// 实现内存泄露检查
#include"LeakDetector.h"

class Err {
public:
	Err(int n) {
		if (n == 0) throw 1000;
		auto data = new int[n];
	}
	~Err() {
		delete[] data;
	}
private:
	int* data;
};

int main() {
	// 忘记释放指针b的内存，从而导致内存泄露
	int* a = new int;
	int* b = new int;
	delete a;

	// 0 为参数传递给构造函数将发生异常，从而导致异常分支的内存泄露
	
	try {
		Err* e = new Err(0);
		delete e;
	}
	catch (int& ex) {
		std::cout << "Exception catch: " << ex << std::endl;
	};
	return 1;
}
```

## 3. 内存泄露器的设计

要检查内存泄露可以从一下两点来思考：

- 内存泄露产生于`new`后没有调用`delete`
- 最先被创建的对象最后释放

解决：

- 重载`new`
- 创建一个静态对象，当程序退出时才调用这个对象的析构函数

在 `LeakDetector.h`中实现

```c++
#ifndef _LEAK_DETECTOR_H__
#define _LEAK_DETECTOR_H__

// 重载new 
void* operator new(size_t _size,char* _fil, unsigned int _line);
void* operator new[](size_t _size, char* _fil, unsigned int _line);

// 为了在实现文件 LeakDetector.cpp中不重载new，防止编译冲突
#ifndef __NEW_OVERLOAD_IMPLEMENTATION__
#define new new(__FILE__,__LINE__)
#endif 

class _leak_detector {
public:
	static unsigned int callCount;
	_leak_detector() noexcept {
		++callCount;
	}
	~_leak_detector() noexcept {
        // 类似与 std::sahre_ptr 当count为0时，调用析构函数
		if (--callCount == 0)
			LeakDetector();
	}

private:
	static unsigned int LeakDetector() noexcept;
};

// 当析构 _exit_counter 时，其他所有申请都完成了析构，
// 此时调用LeakDetector()来检查是否有内存没有被释放
static _leak_detector _exit_counter;
#endif // _LEAK_DETECTOR_H__
```

## 4.内存检查器的实现

对于内存检测器来说实际并不知道代码在运行的什么时候会申请内存空间，所以用一个动态结构来作为代码申请的内存空间，处于使用便捷性的考虑，使用**双向链表**

```c++
#include<iostream>
#include<cstring>

// 定义 _DEBUG_NEW_ 宏
// 从而在这个实现文件中不再继续重载new运算符
// 从而避免编译冲突
#define __NEW_OVERLOAD_IMPLEMENTATION__
#include"LeakDetector.h"

// 双向链表的节点
typedef struct _MemoryList{
    // 指向前后节点的指针
    struct _MemoryList* next, * prev;
    // 申请内存的大小
	size_t size;
    // 是否申请了数组
	bool isArray;
    // 存储所在的文件
	char* file; 
    // 保存所在的行
	unsigned  int line;
}_MemoryList;

// 保存未释放的内存的大小
static unsigned long _memory_allocated = 0;

// 链表的第一个元素
// 其前后指针都指向自己
// 申请的内存大小为0，且不是数组
// 文件指针为空，行号为0
static _MemoryList _root={
   		 &_root,&_root,
		0,
    	false,
		NULL,
    	0
};

// 初始化callCount
unsigned int _leak_detector::callCount = 0;

// 内存分配函数
// 从  _MemoryList头部开始分配
void* AllocateMemory(size_t _size, bool _array, char* _file, unsigned _line) {
	// 计算要插入的大小
	size_t newSize = sizeof(_MemoryList) + _size;

	// 由于new被重载，只用用malloc来分配内存
	_MemoryList* newElem = (_MemoryList*)malloc(newSize);

	// 从头开始分配，将新元素插入到root后
	newElem->next = _root.next;
	newElem->prev = &_root;
	newElem->size = _size;
	newElem->isArray = _array;
	newElem->file = NULL;

	// 如果有文件信息，保存下来
	if (_file) {
		newElem->file = (char*)malloc(strlen(_file) + 1);
		strcpy(newElem-> file, _file);
	}
	// 保存行号
	newElem->line = _line;
	// 更新列表
	_root.next->prev = newElem;
	_root.next = newElem;
	//记录到未释放的内存数中
	_memory_allocated += _size;

	// 返回申请的内存，将newElem强制转换为char* 来严格控制指针每次+1之移动一个byte
	return (char*)(newElem)+sizeof(_MemoryList);
}

//delete操作
void DeleteMemory(void* _ptr, bool _array) {
	// 返回 MemoryList的开始处
	_MemoryList* currentElem = (_MemoryList*)((char*)_ptr - sizeof(_MemoryList));
	if (currentElem->isArray != _array) return;

	// 更新列表, 在链表移除currentElem
	currentElem->prev->next = currentElem->next;
	currentElem->next->prev = currentElem->prev;
	_memory_allocated -= currentElem->size;

	// 记得释放文件信息时申请的内存
	if (currentElem->file) free(currentElem->file);
	// 释放当前元素
	free(currentElem);
}

// 基于上面的AllocateMemory，DeleteMemory重载new delete
// 重载new 和 delete运算符
void* operator new(size_t _size) {
	return AllocateMemory(_size, false, NULL, 0);
}

void* operator new[](size_t _size) {
	return AllocateMemory(_size, true, NULL, 0);
}

void* operator new(size_t _size,char* _file,unsigned int _line) {
	return AllocateMemory(_size, false,_file, _line);
}

void* operator new[](size_t _size, char* _file, unsigned int _line) {
	return AllocateMemory(_size, true, _file, _line);
}

void operator delete(void* _ptr) noexcept {
	DeleteMemory(_ptr, false);
}

void operator delete[](void* _ptr) noexcept {
	DeleteMemory(_ptr, true);
}

// 实现LeakDetector()
unsigned int _leak_detector::LeakDetector(void) noexcept {
    // 记录方式内存泄露的数量
	unsigned int count = 0;
	// 遍历列表，有内存泄露则_LeakRoot.next 总不是指向自己
	_MemoryList* ptr = _root.next;
	while (ptr && ptr != &_root) {
		// 输出存在泄露的信息
		if (ptr->isArray)
			std::cout << "leak[] ";
		else
			std::cout << "leak ";
		std::cout << ptr << " size " << ptr->size;
		if (ptr->file)
			std::cout << " (locate in " << ptr->file << " line " << ptr->line << " ) ";
		else
			std::cout << " (Cannot find position)";
		std::cout << std::endl;

		++count;
		ptr = ptr->next;
	}
	if (count)
		std::cout << "Total " << count << " leaks,size " << _memory_allocated << " byte." << std::endl;
	return count;
}
```

