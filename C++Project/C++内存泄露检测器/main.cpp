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
	// �����ͷ�ָ��b���ڴ棬�Ӷ������ڴ�й¶
	int* a = new int;
	int* b = new int;
	//delete a;
	//delete b;

	// 0 Ϊ�������ݸ����캯���������쳣���Ӷ������쳣��֧���ڴ�й¶
	
	try {
		Err* e = new Err(0);
		delete e;
	}
	catch (int& ex) {
		std::cout << "Exception catch: " << ex << std::endl;
	};
	return 1;
}