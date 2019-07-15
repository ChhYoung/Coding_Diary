//#pragma once
#ifndef _DSA_INCLUDE_SRC_VECTOR_H__
#define _DSA_INCLUDE_SRC_VECTOR_H__


#include<assert.h>
#include"fibnacci.h"
#include"swap.h"
#include<initializer_list> // �б��ʼ��
#include"rand.h"

namespace DSA {

using Rank = int; // ��
template<typename T>
class Vector{
protected:
/**************************��������************************/
    // ��ģ
    Rank size_; 
    // ����
    int capacity_;
    // ����
    T* elem_;
/**************************��������************************/ 
    // �������죬��������A[lo,hi)
    void copy_from(T const* A,Rank lo,Rank hi);
    // ����
    void expand();
    // ����
    void shrink();
    
    
public:
/**************************���� �� ����************************/
    // Ĭ�ϳ�ʼ������
    static constexpr int DEFAULT_CAPACITY = 3;
    // ��ģn,����c�����г�ʼԪ��Ϊv
    Vector(int c = DEFAULT_CAPACITY,int s = 0,T v = {}){
    	assert(s<=c);
    	elem_ = new T[capacity_ = c];
    	size_ = 0;
    	while(size_ < s){
        	elem_[size_++] = v;
    	}
	}
    // ���������幹�죬nΪA�Ĺ�ģ
    Vector(T const* A,Rank n){copy_from(A,0,n);};
    // ���������乹��
    Vector(T const* A,Rank lo,Rank hi){copy_from(A,lo,hi);};
    // �������帴��
    Vector(Vector<T> const& V){copy_from(V.elem_,0,V.size_);};
    // �������临��
    Vector(Vector<T> const& V,Rank lo,Rank hi){copy_from(V.elem_,lo,hi);};
    // �������ز��������������帴��
    Vector<T>& operator=(Vector<T> const& V);



    // ��������
    ~Vector(){
		delete[] elem_;
    	size_ = 0;
    	capacity_ = 0;
	};
/**************************** ֻ���ӿ�  *****************************/
    Rank size() const { return size_; }
    bool empty() const { return !size_; }
    // ��������Ե�����
    int disordered() const;
    /******�������������Ĳ���*********/
    // ��������
    Rank find(T const& e,Rank lo,Rank hi) const;
    // ��������
    Rank find(T const& e) const;
    /******�������������Ĳ���*********/
    // ��������
    Rank search(T const& e,Rank lo,Rank hi) const;
    // ��������
    Rank search(T const& e){ return (0>=size_)?-1:search(e,0,size_);}
    
    static Rank binary_search_A(T* A,T const& e,Rank lo,Rank hi){
        while(lo<hi){
            Rank mi = (lo + hi)>>1;
            if(e < A[mi]) { hi = mi;}
            else if(e > A[mi]) { lo = mi+1;}
   		    else return mi;
        }
        // ����ʧ��
        return -1;
    }
	static Rank binary_search_B(T* A,T const& e,Rank lo,Rank hi){
        Rank mi = (hi + lo)>>1;
	    while(1 < hi - lo){
		    (e<A[mi])?hi = mi: lo=mi;
	    }
        return (e==A[lo])?lo:-1;
    }
	static Rank binary_search_C(T* A,T const& e,Rank lo,Rank hi){
        while(lo<hi){
            Rank mi = (lo+hi)>>1;
            (e<A[mi])?hi = mi: lo = mi+1;
        }
        return lo--;
    }
	//static Rank binary_search(T* A,T const& e,Rank lo,Rank hi){

    
	static Rank fibonacci_search_A(T* A,T const& e,Rank lo,Rank hi){
        Fibonacci<int> fib(hi-lo); // ��O(log_phi(hi-lo))��ʱ�䴴��fib����
        while(lo < hi){
        //  ��ȡ��С��hi-lo����Сfib�����Դ�������Ϊ���������ֵĳ���
        //  �ڷ�̯������O(1)ʱ�临�Ӷ�
            while(hi - lo < fib.get()){
                fib.prev(); 
            }
            Rank mi = lo+fib.get()-1;
            if(e<A[mi]) hi = mi;
            else if(e>A[mi]) lo = mi+1;
            else return mi;
            }
        return -1;
    }

	static Rank fibonacci_search_B(T* A,T const& e,Rank lo,Rank hi){
        Fibonacci<int> fib(hi-lo);
        while(lo < hi){
            while(hi - lo < fib.get()){fib.prev();}
            Rank mi = lo + fib.get() - 1;
            (e<A[mi])? hi=mi: lo=mi+1;    
        }
    return --lo;
    }

    static Rank interploation_search(T* A ,T const& e,Rank lo,Rank hi){
        assert(0 <= lo && lo <= hi && hi <= A->size_);
        while(A[lo] <= e && e <= A[hi]){
            Rank mi = lo + (hi-lo)*(e-A[lo])/(A[hi]-A[lo]);
            if(e < A[mi]) lo = mi+1;
            else if(e > A[mi]) hi = mi-1;
            else return mi;
        }
        if(A[lo] == e) return lo;
        else return -1;
    }

    static Rank fibonacci_search(T* A,T const& e,Rank lo,Rank hi){
#if TEST_BUILD
        switch(rand()%2){
            case 0 :return fibonacci_search_A(A,e,lo,hi);
            default:return fibonacci_search_B(A,e,lo,hi);
        }
#else
        return fibonacci_search_B(A,e,lo,hi);
#endif    
    }

    static Rank binary_search(T* A,T const& e,Rank lo,Rank hi){
#if TEST_BUILD
        switch(rand()%3){
            case 0 : return binary_search_A(A,e,lo,hi);
            case 1 : return binary_search_B(A,e,lo,hi);
		    default: return binary_search_C(A,e,lo,hi);            
        }
#else
        return binary_search_C(A,e,lo,hi);   
#endif    
    }


    Rank search(T* A,T const& e,Rank lo,Rank hi){
        assert(0 <= lo && lo <= hi && hi <= A->size_);
#if TEST_BUILD
        return (rand()%2)?binary_search_C(A,e,lo,hi):fibonacci_search_B(A,e,lo,hi);
#else
        return fibonacci_search_B(A,e,lo,hi);
#endif    
    }
  



	//static Rank fibonacci_search(T* A,T const& e,Rank lo,Rank hi);
/*************************** ��д���ʽӿ�    *****************************/	
    // �������
    void clear();
    // �±����ز�����
    T& operator[](Rank r) const{
        assert(0<=r && r<size_);
        return elem_[r];
    };
    // ����Ԫ��
    Rank insert(Rank r,T const& e);
    // ��ΪĩβԪ�ز���
    Rank insert(T const& e);
    // ɾ��[lo,hi)�ڵ�Ԫ��
    int remove(Rank lo,Rank hi);
    // ɾ��Ԫ�� O(n)
    T remove(Rank r);
    // ��[lo,hi)��Ԫ������
    void sort(Rank lo,Rank hi);
    // ��������
    void sort(){ sort(0,size_); }
    // ��[lo,hi)�ȸ����������
    void unsort(Rank lo,Rank hi);
    // ��������
    void unsort(){unsort(0,size_);}
    // ����ȥ�ظ�
    int deduplicate();
    // ����ȥ��
    int uniquify();
    // ð��
    bool bubble(Rank lo,Rank hi);
    // ð������
    void bubble_sort(Rank lo,Rank hi);
    // ���ٰ�
    Rank bubble_fast(Rank lo, Rank hi);
    void bubble_sort_fast(Rank lo,Rank hi);
    Rank bubble_fast_2(Rank lo, Rank hi);
    void bubble_sort_fast_2(Rank lo,Rank hi);
    // ��·����
    void merge(Rank lo,Rank mi,Rank hi);
    // �鲢����
    void merge_sort(Rank lo,Rank hi);
    
};

template<typename T>
void Vector<T>::copy_from(T const* A,Rank lo,Rank hi){
    // ����ռ䣬��ȷ������
    elem_ = new T[capacity_ = 2*(hi - lo)];
    size_ = 0;
    // ����Ԫ��
    while(lo<hi)
        elem_[size_++] = A[lo++];
}

template<typename T>
void Vector<T>::expand(){
    // ��û��ʱ������
    if(size_ < capacity_) return;
    // ��������С����
    if(capacity_ < DEFAULT_CAPACITY) capacity_ = DEFAULT_CAPACITY;
    T* old_elem_ = elem_;
    elem_ = new T[capacity_ <<= 1];
    for(int i=0; i<size_; ++i){
        elem_[i] = old_elem_[i];
    }
    delete[] old_elem_;
}

template<typename T>
void Vector<T>::shrink(){
    // ��������С����С����
    if(capacity_ < DEFAULT_CAPACITY<<1) return ;
    // ��25%Ϊ��,��������25%
    if(size_<<2 > capacity_) return;
    // ����С��25%
    T* old_elem_ = elem_;
    elem_ = new T[capacity_>>1];
    for(int i=0;i<size_;++i){
        elem_[i] = old_elem_[i];
    }
    delete[] old_elem_;
}

template<typename T> 
Vector<T>& Vector<T>::operator=(Vector<T> const& V){
	if(elem_){
         delete[] elem_;
	}
	copy_from(V.elem_,0,V.size_);
    return *this;
}

template<typename T>
int Vector<T>::disordered() const{
	int cnt=0;
	for(int i=1;i<size_;++i){
		if(elem_[i-1] > elem_[i]) { ++cnt;}
	}
	return cnt;
}

template<typename T>
Rank Vector<T>::find(T const& e,Rank lo,Rank hi) const{
    while((lo<hi--)&&(e != elem_[hi]));
    return hi;
}

template<typename T>
Rank Vector<T>::find(T const& e) const{
    return find(e,0,size_);
}

template<typename T>
Rank Vector<T>::search(T const& e,Rank lo,Rank hi) const{
    assert(0 <= lo && lo<=hi  && hi<=size_);
#if TEST_BUILD
    return (rand()%2)?
        binary_search(elem_,lo,hi):fibnacci_search(elem_,lo,hi);
#else
    return fibnacci_search(elem_,lo,hi);
#endif    
}

template<typename T>
Rank Vector<T>::insert(Rank r,T const& e){
    assert(0<=r && r<=size_);
    expand();
    for(int i=size_-1;i>r;--i)
        elem_[i] = elem_[i-1];
    elem_[r] = e;
    ++size_;
    return r;
}

template<typename T>
Rank Vector<T>::insert(T const& e){
    return insert(size_,e);
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi){
    assert(0<=lo && lo<=hi && hi<=size_);
    if(lo == hi) return 0;
    while(hi < size_ ){
        elem_[lo++] = elem_[hi++];
    }
    // ���¹�ģ��ֱ�Ӷ���[lo,size_ = hi)����
    size_ = lo;
    // shrink();
    return hi-lo;
}

template<typename T>
T Vector<T>::remove(Rank r){
    assert(0<=r && r<size_);
    T e = elem_[r];
    remove(r,r+1);
    return e;
}

template<typename T>
int Vector<T>::deduplicate(){
    int old_size = size_;
    int i=0;
    while(i<size_){
    	find(elem_[i],0,i)<0?++i:remove(i);
    }
    return old_size - size_;
}

template<typename T>
int Vector<T>::uniquify(){
    // i����¼����Ԫ�ص�λ�ã�j��������������
    Rank i=0,j=0;
    while(++j < size_){
        // ��Ԫ���ظ���i���䣬++j���ӵ�Ԫ�ز���ͬʱ���ټ�������
        if(elem_[i] != elem_[j]){
            elem_[++i] = elem_[j];
        }
    }
    size_ = ++i;
    shrink();
    return j-i;
}

// ����ɨ��
template<typename T>
bool Vector<T>::bubble(Rank lo,Rank hi){
    bool sorted = true;
    while(++lo < hi){
        if(elem_[lo-1] > elem_[lo]){
            swap(elem_[lo-1],elem_[lo]);
            sorted = false;
        }
    }
    return sorted;
}

template<typename T>
void Vector<T>::bubble_sort(Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= size_);
    while(!bubble(lo,hi--)){};
}

template<typename T>
Rank Vector<T>::bubble_fast(Rank lo, Rank hi){
    Rank last = lo;
    while(++lo < hi){
        if(elem_[lo-1]>elem_[lo]){
            last = lo;
            swap(elem_[lo-1],elem_[lo]);
        }
    }
    return last;
}

template<typename T>
void Vector<T>::bubble_sort_fast(Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= size_);
    while(lo < (hi = bubble_fast(lo,hi)) ){}
}

template<typename T>
Rank Vector<T>::bubble_fast_2(Rank lo, Rank hi){
    Rank first = hi;
    while(lo < --hi){
        if(elem_[hi]>elem_[hi+1]){
            first = hi;
            swap(elem_[hi],elem_[hi+1]);
        }
    }
    return first;
}


template<typename T>
void Vector<T>::bubble_sort_fast_2(Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= size_);
    while( (lo=bubble_fast_2(lo,hi)) < (hi = bubble_fast(lo,hi)) ){}
}

template<typename T>
void Vector<T>::merge_sort(Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= size_);
    // �ݹ��
    if(hi - lo < 2)
        return;
    Rank mi = (hi + lo)>>1;
    merge_sort(lo,mi);
    merge_sort(mi,hi);
    // �ڽϺ����������Ҫ�ϲ�ʱ������ٶ�
    if(elem_[mi-1] > elem_[mi]){
        merge(lo,mi,hi);
    }
}

// �鲢���������������[lo,mi)��[mi,hi)
template<typename T>
void Vector<T>::merge(Rank lo,Rank mi,Rank hi){
    // �ϲ��������A=elem_[lo,hi)
    T* A = elem_ + lo;
    // ��¼�����ĳ���
    int lengthB = mi - lo;
    // ���ڴ洢�м��� [lo,mi)
    T* B = new T[lengthB];
    // ��A[lo,mi)���帴�Ƶ�B��
    for(int i=0;i<lengthB;++i){
        B[i] = A[i];
    }
    T* C = elem_ + mi; // [mi,hi)
    int lengthC = hi - mi;
    // B[j] �� C[k]�е���С�߼ӵ�A�ĺ���
    for(int i=0,j=0,k=0;(j<lengthB)||(k<lengthC);){
        // ��B��С  ���� CԪ������ʱ
        if( (j<lengthB) && (!(k<lengthC) || B[j]<=C[k]) ){
            A[i++] = B[j++];
        }
        // ��C��С  ���� BԪ������ʱ
        if( (k<lengthC) && (!(j<lengthB) || C[k]<=B[k]) ){
            A[i++] = C[k++];
        }
    }
    delete[] B;   
}

}

#endif // _DSA_INCLUDE_SRC_VECTOR_H__