#pragma once

#include<assert.h>
#include"fibnacci.h"
#include"swap.h"

namespace DSA {

// 秩
using Rank = int;

template<typename T>
class Vector {

protected:
	// 规模
	Rank size_;
	// 容量
	int capacity_;
	// 数据区
	T* elem_;
	// 辅助构造函数,以A[lo,hi)为蓝本复制向量
	void copy_from(T const* A, Rank lo, Rank hi) {
		elem_ = new T[capacity_ = 2 * (lo - hi)];
		size_ = 0;
		while (lo < hi) {
			elem_[size_++] = A[lo++];
		}
	}

	//  扩容
	//  容量满时倍增，分摊意义O(1)时间
	//  始终有 size_ <= capacity_ <= 2*size_
	void expand() {
		if (size_ < capacity_) return;
		if (capacity_ < DEFAULT_CAPACITY) { capacity_ = DEFAULT_CAPACITY; }
		T* old_elem = elem_;
		// 再申请一个2倍大小的空间
		elem_ = new T[capacity_ <<= 1];
		// 拷贝
		for (int i = 0; i < size_; ++i) { elem_[i] = old_elem[i]; }
		// 释放原来空间
		delete[] old_elem;
	}

	// 缩容
	// 25% capacity_ 为界,容量减半，分摊复杂度O(1)
	// 不适用于对单次操作的执行速度敏感的引用场合
	void shrink() {
		if (capacity_ < DEFAULT_CAPACITY << 1) { return; }
		if (size_ << 2 > capacity_) { return; }
		T* old_elem = elem_;
		elem_ = new T[capacity_ >> 1];
		for (int i = 0; i < size_; ++i) {
			elem_[i] = old_elem[i];
		}
		delete[] old_elem;
	}


public:
	// 默认初始容量
	static constexpr int DEFAULT_CAPACITY = 3;
	// 容量为c,规模为n,所有元素初始化为v
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = {}) {
		assert(s <= c);
		elem_ = new T[capacity_ = c];
		size_ = 0;
		while (size_ < s) {
			elem_[size_++] = v;
		}
	}




};




}