
#include<iostream>
#include<cstring>

// 定义 _DEBUG_NEW_ 宏
// 从而在这个实现文件中不再继续重载new运算符
// 从而避免编译冲突
#define __NEW_OVERLOAD_IMPLEMENTATION__
#include"LeakDetector.h"

typedef struct _MemoryList{
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

// 保存未释放内存的大小
static unsigned long _memory_allocated = 0;
// 第一个元素
// 其前后指针都指向自己
// 申请的内存大小为0，且不是数组
// 文件指针为空，行号为0
static _MemoryList _root = {
		&_root,&_root,
		0,false,
		NULL,0
};

unsigned int _leak_detector::callCount = 0;

// 用这个结构来分配内存

// 从  _MemoryList头部开始分配
void* AllocateMemory(size_t _size, bool _array, char* _file, unsigned _line) {
	// 计算新的大小
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
	//记录到为释放的内存数中
	_memory_allocated += _size;

	// 返回申请的内存，将newElem强制转换为char* 来严格控制指针每次+1之移动一个byte
	return (char*)(newElem)+sizeof(_MemoryList);
}

// delete 操作
void DeleteMemory(void* _ptr, bool _array) {
	// 返回 MemoryList的开始处
	_MemoryList* currentElem = (_MemoryList*)((char*)_ptr - sizeof(_MemoryList));
	if (currentElem->isArray != _array) return;

	// 更新列表
	currentElem->prev->next = currentElem->next;
	currentElem->next->prev = currentElem->prev;
	_memory_allocated -= currentElem->size;

	// 记得释放文件信息时申请的内存
	if (currentElem->file) free(currentElem->file);

	free(currentElem);
}

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

unsigned int _leak_detector::LeakDetector(void) noexcept {
	unsigned int count = 0;
	// 遍历列表，有内存泄露则_LeakRoot.next 中不是指向自己
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