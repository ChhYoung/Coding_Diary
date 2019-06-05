
#include<iostream>
#include<cstring>

// ���� _DEBUG_NEW_ ��
// �Ӷ������ʵ���ļ��в��ټ�������new�����
// �Ӷ���������ͻ
#define __NEW_OVERLOAD_IMPLEMENTATION__
#include"LeakDetector.h"

typedef struct _MemoryList{
	struct _MemoryList* next, * prev;
	// �����ڴ�Ĵ�С
	size_t size;
	// �Ƿ�����������
	bool isArray;
	// �洢���ڵ��ļ�
	char* file; 
	// �������ڵ���
	unsigned  int line;
}_MemoryList;

// ����δ�ͷ��ڴ�Ĵ�С
static unsigned long _memory_allocated = 0;
// ��һ��Ԫ��
// ��ǰ��ָ�붼ָ���Լ�
// ������ڴ��СΪ0���Ҳ�������
// �ļ�ָ��Ϊ�գ��к�Ϊ0
static _MemoryList _root = {
		&_root,&_root,
		0,false,
		NULL,0
};

unsigned int _leak_detector::callCount = 0;

// ������ṹ�������ڴ�

// ��  _MemoryListͷ����ʼ����
void* AllocateMemory(size_t _size, bool _array, char* _file, unsigned _line) {
	// �����µĴ�С
	size_t newSize = sizeof(_MemoryList) + _size;

	// ����new�����أ�ֻ����malloc�������ڴ�
	_MemoryList* newElem = (_MemoryList*)malloc(newSize);

	// ��ͷ��ʼ���䣬����Ԫ�ز��뵽root��
	newElem->next = _root.next;
	newElem->prev = &_root;
	newElem->size = _size;
	newElem->isArray = _array;
	newElem->file = NULL;

	// ������ļ���Ϣ����������
	if (_file) {
		newElem->file = (char*)malloc(strlen(_file) + 1);
		strcpy(newElem-> file, _file);
	}
	// �����к�
	newElem->line = _line;
	// �����б�
	_root.next->prev = newElem;
	_root.next = newElem;
	//��¼��Ϊ�ͷŵ��ڴ�����
	_memory_allocated += _size;

	// ����������ڴ棬��newElemǿ��ת��Ϊchar* ���ϸ����ָ��ÿ��+1֮�ƶ�һ��byte
	return (char*)(newElem)+sizeof(_MemoryList);
}

// delete ����
void DeleteMemory(void* _ptr, bool _array) {
	// ���� MemoryList�Ŀ�ʼ��
	_MemoryList* currentElem = (_MemoryList*)((char*)_ptr - sizeof(_MemoryList));
	if (currentElem->isArray != _array) return;

	// �����б�
	currentElem->prev->next = currentElem->next;
	currentElem->next->prev = currentElem->prev;
	_memory_allocated -= currentElem->size;

	// �ǵ��ͷ��ļ���Ϣʱ������ڴ�
	if (currentElem->file) free(currentElem->file);

	free(currentElem);
}

// ����new �� delete�����
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
	// �����б����ڴ�й¶��_LeakRoot.next �в���ָ���Լ�
	_MemoryList* ptr = _root.next;
	while (ptr && ptr != &_root) {
		// �������й¶����Ϣ
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