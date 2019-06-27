#pragma once
namespace DSA {

	// 二分递归版  O(2^N)
	static __int64 fibR(int n) {
		return n < 2 ? n : fibR(n - 1) + fibR(n - 2);
	}

	// 线性递归版本， O(n)
	// 计算第n项 入口形式为fibL(n,prev)
	// 巧妙地利用引用来传值
	static __int64 fibL(int n, __int64& prev) {
		if (n == 0) {
			// fin(-1) = 1
			prev = 1;
			// fib(0) = 0
			return 0;
		}
		else {
			__int64 prev_prev;
			prev = fibL(n - 1, prev_prev);
			return prev_prev + prev;
		}
	}

	//  迭代版  O(n)
	static __int64 fibI(int n) {
		// fib(-1) = 1, fib(0) = 0
		__int64 f = 1, g = 0;
		while (n--) {
			// f(n) = f(n-1) + f(n-2)
			g += f;
			// f(n-1) = f(n) - f(n-2)
			f = g - f;
		}
		return g;
	}

	// Fibonacci 数列类
	template<typename T = int>
	class Fibonacci {
	private:
		T f, g;
	public:
		// 初始化为不小于n地最小Fib项，O(log(n))时间
		explicit Fibonacci(T n = 0) {
			// f(-1)
			f = 1;
			// f(0)
			g = 0;
			while (g < n) {
				next();
			}
		}

		// 获取当前Fibnonacci项，O(1)时间
		T next() {
			// f(n) = f(n-1)+f(n-2)
			g += f;
			// f(n-1) = f(n) - f(n-2)
			f = g - f;
			return g;
		}

		// 转至上一个Fibonacci项,O(1)时间
		T prev() {
			// f(n-2) = f(n) - f(n-1)
			f = g - f;
			// f(n-1) = f(n) - f(n-2)
			g -= f;
			return g;
		}
	}; // end of Fibonacci class

} // end of namespace