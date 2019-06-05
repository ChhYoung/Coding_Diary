#ifndef _LEAK_DETECTOR_H__
#define _LEAK_DETECTOR_H__

void* operator new(size_t _size,char* _fil, unsigned int _line);
void* operator new[](size_t _size, char* _fil, unsigned int _line);

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
		if (--callCount == 0)
			LeakDetector();
	}

private:
	static unsigned int LeakDetector() noexcept;

};

// 当_exit_counter析构时，其他所有申请的都完成析构，此时调用LeakDetector()，
// 若LeakDetector()检测到有
static _leak_detector _exit_counter;

#endif // _LEAK_DETECTOR_H__