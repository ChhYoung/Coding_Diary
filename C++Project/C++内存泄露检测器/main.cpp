#include<iostream>



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
	//delete a;
	//delete b;

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