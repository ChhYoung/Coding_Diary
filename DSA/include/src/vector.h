//#pragma once

#include<assert.h>
#include"fibnacci.h"
#include"swap.h"

namespace DSA {

// ��
using Rank = int;

template<typename T>
class Vector {

protected:
	// ��ģ
	Rank size_;
	// ����
	int capacity_;
	// ������
	T* elem_;
	// �������캯��,��A[lo,hi)Ϊ������������
	void copy_from(T const* A, Rank lo, Rank hi) {
		elem_ = new T[capacity_ = 2 * (lo - hi)];
		size_ = 0;
		while (lo < hi) {
			elem_[size_++] = A[lo++];
		}
	}

	//  ����
	//  ������ʱ��������̯����O(1)ʱ��
	//  ʼ���� size_ <= capacity_ <= 2*size_
	void expand() {
		if (size_ < capacity_) return;
		if (capacity_ < DEFAULT_CAPACITY) { capacity_ = DEFAULT_CAPACITY; }
		T* old_elem = elem_;
		// ������һ��2����С�Ŀռ�
		elem_ = new T[capacity_ <<= 1];
		// ����
		for (int i = 0; i < size_; ++i) { elem_[i] = old_elem[i]; }
		// �ͷ�ԭ���ռ�
		delete[] old_elem;
	}

	// ����
	// 25% capacity_ Ϊ��,�������룬��̯���Ӷ�O(1)
	// �������ڶԵ��β�����ִ���ٶ����е����ó���
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
	// Ĭ�ϳ�ʼ����
	static constexpr int DEFAULT_CAPACITY = 3;
	// ����Ϊc,��ģΪn,����Ԫ�س�ʼ��Ϊv
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