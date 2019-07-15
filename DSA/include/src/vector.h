//#pragma once
#ifndef _DSA_INCLUDE_SRC_VECTOR_H__
#define _DSA_INCLUDE_SRC_VECTOR_H__


#include<assert.h>
#include"fibnacci.h"
#include"swap.h"
#include<initializer_list> // 列表初始化
#include"rand.h"

namespace DSA {

using Rank = int; // 秩
template<typename T>
class Vector{
protected:
/**************************向量属性************************/
    // 规模
    Rank size_; 
    // 容量
    int capacity_;
    // 数据
    T* elem_;
/**************************辅助函数************************/ 
    // 辅助构造，复制区间A[lo,hi)
    void copy_from(T const* A,Rank lo,Rank hi);
    // 扩容
    void expand();
    // 缩容
    void shrink();
    
    
public:
/**************************构造 及 析构************************/
    // 默认初始化容量
    static constexpr int DEFAULT_CAPACITY = 3;
    // 规模n,容量c，所有初始元素为v
    Vector(int c = DEFAULT_CAPACITY,int s = 0,T v = {}){
    	assert(s<=c);
    	elem_ = new T[capacity_ = c];
    	size_ = 0;
    	while(size_ < s){
        	elem_[size_++] = v;
    	}
	}
    // 从数组整体构造，n为A的规模
    Vector(T const* A,Rank n){copy_from(A,0,n);};
    // 从数组区间构造
    Vector(T const* A,Rank lo,Rank hi){copy_from(A,lo,hi);};
    // 向量整体复制
    Vector(Vector<T> const& V){copy_from(V.elem_,0,V.size_);};
    // 向量区间复制
    Vector(Vector<T> const& V,Rank lo,Rank hi){copy_from(V.elem_,lo,hi);};
    // 基于重载操作符的向量整体复制
    Vector<T>& operator=(Vector<T> const& V);



    // 析构函数
    ~Vector(){
		delete[] elem_;
    	size_ = 0;
    	capacity_ = 0;
	};
/**************************** 只读接口  *****************************/
    Rank size() const { return size_; }
    bool empty() const { return !size_; }
    // 相邻逆序对的总数
    int disordered() const;
    /******对于无序向量的查找*********/
    // 区间搜索
    Rank find(T const& e,Rank lo,Rank hi) const;
    // 整体搜索
    Rank find(T const& e) const;
    /******对于有序向量的查找*********/
    // 区间搜索
    Rank search(T const& e,Rank lo,Rank hi) const;
    // 整体搜索
    Rank search(T const& e){ return (0>=size_)?-1:search(e,0,size_);}
    
    static Rank binary_search_A(T* A,T const& e,Rank lo,Rank hi){
        while(lo<hi){
            Rank mi = (lo + hi)>>1;
            if(e < A[mi]) { hi = mi;}
            else if(e > A[mi]) { lo = mi+1;}
   		    else return mi;
        }
        // 查找失败
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
        Fibonacci<int> fib(hi-lo); // 用O(log_phi(hi-lo))的时间创建fib数列
        while(lo < hi){
        //  获取不小于hi-lo的最小fib数，以此数列作为接下来划分的长度
        //  在分摊意义下O(1)时间复杂度
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
/*************************** 可写访问接口    *****************************/	
    // 清除数据
    void clear();
    // 下表重载操作符
    T& operator[](Rank r) const{
        assert(0<=r && r<size_);
        return elem_[r];
    };
    // 插入元素
    Rank insert(Rank r,T const& e);
    // 作为末尾元素插入
    Rank insert(T const& e);
    // 删除[lo,hi)内的元素
    int remove(Rank lo,Rank hi);
    // 删除元素 O(n)
    T remove(Rank r);
    // 对[lo,hi)内元素排序
    void sort(Rank lo,Rank hi);
    // 整体排序
    void sort(){ sort(0,size_); }
    // 对[lo,hi)等概率随机置乱
    void unsort(Rank lo,Rank hi);
    // 整体置乱
    void unsort(){unsort(0,size_);}
    // 无序去重复
    int deduplicate();
    // 有序去重
    int uniquify();
    // 冒泡
    bool bubble(Rank lo,Rank hi);
    // 冒泡排序
    void bubble_sort(Rank lo,Rank hi);
    // 加速版
    Rank bubble_fast(Rank lo, Rank hi);
    void bubble_sort_fast(Rank lo,Rank hi);
    Rank bubble_fast_2(Rank lo, Rank hi);
    void bubble_sort_fast_2(Rank lo,Rank hi);
    // 二路并归
    void merge(Rank lo,Rank mi,Rank hi);
    // 归并排序
    void merge_sort(Rank lo,Rank hi);
    
};

template<typename T>
void Vector<T>::copy_from(T const* A,Rank lo,Rank hi){
    // 申请空间，并确定容量
    elem_ = new T[capacity_ = 2*(hi - lo)];
    size_ = 0;
    // 复制元素
    while(lo<hi)
        elem_[size_++] = A[lo++];
}

template<typename T>
void Vector<T>::expand(){
    // 当没满时不扩容
    if(size_ < capacity_) return;
    // 不低于最小容量
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
    // 不缩减到小于最小容量
    if(capacity_ < DEFAULT_CAPACITY<<1) return ;
    // 以25%为界,容量大于25%
    if(size_<<2 > capacity_) return;
    // 容量小于25%
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
    // 更新规模，直接丢弃[lo,size_ = hi)区间
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
    // i来记录独立元素的位置，j来遍历整个向量
    Rank i=0,j=0;
    while(++j < size_){
        // 当元素重复是i不变，++j，加到元素不相同时，再继续覆盖
        if(elem_[i] != elem_[j]){
            elem_[++i] = elem_[j];
        }
    }
    size_ = ++i;
    shrink();
    return j-i;
}

// 交换扫描
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
    // 递归基
    if(hi - lo < 2)
        return;
    Rank mi = (hi + lo)>>1;
    merge_sort(lo,mi);
    merge_sort(mi,hi);
    // 在较好情况即不需要合并时，提高速度
    if(elem_[mi-1] > elem_[mi]){
        merge(lo,mi,hi);
    }
}

// 归并各自有序的子向量[lo,mi)和[mi,hi)
template<typename T>
void Vector<T>::merge(Rank lo,Rank mi,Rank hi){
    // 合并后的向量A=elem_[lo,hi)
    T* A = elem_ + lo;
    // 记录向量的长度
    int lengthB = mi - lo;
    // 用于存储中间结果 [lo,mi)
    T* B = new T[lengthB];
    // 将A[lo,mi)整体复制到B中
    for(int i=0;i<lengthB;++i){
        B[i] = A[i];
    }
    T* C = elem_ + mi; // [mi,hi)
    int lengthC = hi - mi;
    // B[j] 和 C[k]中的最小者加到A的后面
    for(int i=0,j=0,k=0;(j<lengthB)||(k<lengthC);){
        // 当B较小  或者 C元素用完时
        if( (j<lengthB) && (!(k<lengthC) || B[j]<=C[k]) ){
            A[i++] = B[j++];
        }
        // 当C较小  或者 B元素用完时
        if( (k<lengthC) && (!(j<lengthB) || C[k]<=B[k]) ){
            A[i++] = C[k++];
        }
    }
    delete[] B;   
}

}

#endif // _DSA_INCLUDE_SRC_VECTOR_H__