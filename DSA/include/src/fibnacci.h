//#pragma once
namespace DSA {

	// ���ֵݹ��?  O(2^N)
	static long long fibR(int n) {
		return n < 2 ? n : fibR(n - 1) + fibR(n - 2);
	}

	// ���Եݹ�汾��? O(n)
	// �����n�� �����ʽΪfibL(n,prev)
	// ������������������?
	static long long fibL(int n, long long& prev) {
		if (n == 0) {
			// fin(-1) = 1
			prev = 1;
			// fib(0) = 0
			return 0;
		}
		else {
			long long prev_prev;
			prev = fibL(n - 1, prev_prev);
			return prev_prev + prev;
		}
	}

	//  ������  O(n)
	static long long fibI(int n) {
		// fib(-1) = 1, fib(0) = 0
		long long f = 1, g = 0;
		while (n--) {
			// f(n) = f(n-1) + f(n-2)
			g += f;
			// f(n-1) = f(n) - f(n-2)
			f = g - f;
		}
		return g;
	}

	// Fibonacci ������
	template<typename T = int>
	class Fibonacci {
	private:
		T f, g;
	public:
		// ��ʼ��Ϊ��С��n����СFib�O(log(n))ʱ��
		explicit Fibonacci(T n = 0) {
			// f(-1)
			f = 1;
			// f(0)
			g = 0;
			while (g < n) {
				next();
			}
		}
		T get() const { return g;}

		// ��ȡ��ǰFibnonacci�O(1)ʱ��
		T next() {
			// f(n) = f(n-1)+f(n-2)
			g += f;
			// f(n-1) = f(n) - f(n-2)
			f = g - f;
			return g;
		}

		// ת����һ��Fibonacci��,O(1)ʱ��
		T prev() {
			// f(n-2) = f(n) - f(n-1)
			f = g - f;
			// f(n-1) = f(n) - f(n-2)
			g -= f;
			return g;
		}
	}; // end of Fibonacci class

} // end of namespace