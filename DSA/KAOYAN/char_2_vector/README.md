# char 2 vector

[TOC]

## 1. 基本知识

- 向量在内存中连续分配的量



## 2.向量类的设计

| 操作接口      | 功能                                    | 适合对象 |
| :------------ | --------------------------------------- | -------- |
| size()        | 当前向量的元素总数                      | 向量     |
| get(r)        | 获得秩为r的元素                         |          |
| put(r,e)      | 用e替代秩为r的元素                      |          |
| insert(r,e)   | e为秩为r的元素插入，原后继元素后移      |          |
| remove(r)     | 删除秩为r的元素，返回该元素中存放的对象 |          |
| disordered()  | 判断所有元素是否按非降序排列            |          |
| sort()        | 排序，按照非降序                        |          |
| find(e)       | 找到为e且秩最大的元素                   | 无序     |
| search(e)     |                                         | 有序     |
| deduplicate() | 除重复元素                              | 无序     |
| uniquify()    | 除重复元素                              | 有序     |
| traverse()    |                                         |          |

### 3.实现

```c++
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
    Vector(int c = DEFAULT_CAPACITY,int s=0,T v={});
    // 从数组整体构造，n为A的规模
    Vector(T const* A,Rank n);
    // 从数组区间构造
    Vector(T const* A,Rank lo,Rank hi);
    // 向量整体复制
    Vector(Vector<T> const& V);
    // 向量区间复制
    Vecotr(Vector<T> const& V,Rank lo,Rank hi);
    // 基于重载操作符的向量整体复制
    Vector<T>& operator=(Vector<T> const& V);
    // 析构函数
    ~Vector();
/**************************** 只读接口  *****************************/
    Rank size() const { reutrn size_; }
    bool empty() const { return !size_; }
    // 相邻逆序对的总数
    int disorderd() const;
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
    
    static Rank binary_search_A(T* A,T const& e,Rank lo,Rank hi);
	static Rank binary_search_B(T* A,T const& e,Rank lo,Rank hi);
	static Rank binary_search_C(T* A,T const& e,Rank lo,Rank hi);
	static Rank binary_search(T* A,T const& e,Rank lo,Rank hi);
	static Rank fibonacci_search_A(T* A,T const& e,Rank lo,Rank hi);
	static Rank fibonacci_search_B(T* A,T const& e,Rank lo,Rank hi);
	static Rank fibonacci_search(T* A,T const& e,Rank lo,Rank hi);
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
}

```

#### 3.1  copy_from(T const* A,Rank lo,Rank hi)

复制A[lo,hi)的元素，并设置好向量的规模与容量,

```c++
template<typename T>
void Vector<T>::copy_from(T const* A,Rank lo,Rank hi){
    // 申请空间，并确定容量
    elem_ = new T[capacity_ = 2*(hi - lo)];
    size_ = 0;
    // 复制元素
    while(lo<hi)
        elem_[size_++] = A[lo++];
}
```

#### 3.2  expand()

扩容，使容量与规模关系满足  `size_ < capacity`,始终有`size_ < capacity < 2*size_ ` 当容量不足时以两倍的大小扩展容量

分摊意义O(1)时间:  每次扩容花费O(n)的时间，但至少经过n次操作才再次扩容，所以分摊时间为O(1)

实现： 检查当前容量与规模的大小关系, 保存当前元素，申请一个新的空间，拷贝过去，删除旧空间

- 若是每次加固定的空间，则分摊复杂度为O(n)  *习题2-3*

```c++
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
```

#### 3.3  shrink()

缩容，过小下溢，以25%为界，容量减半，分摊复杂度O(1)；不适合于对单次操作执行速度敏感的场合

```c++
template<typename T>
void Vector<int>::shrink(){
    // 不缩减到小于最小容量
    if(capacity_ < DEFAULT_CAPACITY<<1) return ;
    // 以25%为界,容量大于25%
    if(size_<<2 > capacity_) return;
    // 容量小于25%
    T* old_elem_ = elem_;
    elem_ = new T[capacity>>1];
    for(int i=0;i<size_;++i){
        elem_[i] = old_elem_[i];
    }
    delete[] old_elem_;
}
```

#### 3.4  Vector(int c = DEFAULT_CAPACITY,int s=0,T v={});

容量为c， 规模为n,  所有元素初始为v

```c++
Vector(int c = DEFAULT_CAPACITY,int s=0,T v={}){
    capacity_ = c;
    size_ = s;
    elem = new T[c];
    for(int i = 0;i < s;++i)
        elem[i] = v; 
}

// 书本实现
Vector(int c = DEFAULT_CAPACITY,int s = 0,T v = {}){
    assert(s<=c);
    elem_ = new T[capacity_ = c];
    size_ = 0;
    while(size_ < s){
        elem_[size_++] = v;
    }
}
```

#### 3.5   Vector(T const* A,Rank n)

n 为A的规模

从数组整体构造

```c++
Vector(T const* A,Rank n){
    copy_from(A,0,n); 
}
```

#### 3.6  Vector(T const* A,Rank lo,Rank hi);

从区间拷贝

```c++
Vector(T const* A,Rank lo,Rank hi){
    copy_from(A,lo,hi);
}
```

#### 3.7  Vector(Vector\<T> const& V);

向量整体拷贝

```c++
Vector(Vector<T> const& V){
    copy_from(V.elem_,0,V.size_);
}
```

#### 3.8  Vecotr(Vector\<T> const& V,Rank lo,Rank hi);

向量区间复制

```c++
Vecotr(Vector<T> const& V,Rank lo,Rank hi){
    copy_from(V.elem_,lo,hi);
}
```

#### 3.9   Vector\<T>& operator=(Vector\<T> const& V)

基于重载操作符的向量整体复制

```c++
template <typename T>
Vector<T>&  Vector<T>::operator=(Vector<T> const& V){
	if(elem_){
         delete[] elem_;
	}
	copy_from(V.elem_,0,V.size_);
    return *this;
}
```

#### 3.10 ~Vector()

```c++
~Vector(){
    delete[] elem_;
    size_ = 0;
    capacity_ = 0;
}
```

#### 3.11   int disorderd() const

返回向量中逆序相邻元素个数

```c++
template<typename T>
int Vector<T>::disordered() const{
	int cnt=0;
	for(int i=1;i<size_;++i){
		if(elem_[i-1] > elem_[i]) { ++cnt;}
	}
	return cnt;
}
```

#### 3.12  Rank find(T const& e,Rank lo, Rank hi) const;

在无序的向量中查找 e元素，并返回其最大位置的秩，失败时返回 `lo-1`

为找到最大的秩，可以从后向前搜索

```c++
template<typename T>
Rank Vector<T>::find(T const& e,Rank lo,Rank hi) const{
    while((lo<hi--)&&(e != elem_[hi]));
    return hi;
}
```

####  3.13   Rank find(T const& e) const;

```c++
template<typename T>
Rank Vector<T>::find(T const& e) const{
    return find(e,0,size_);
}
```

#### 3.14   Rank search(T const& e,Rank lo,Rank hi) const;

```c++
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
```

####  3.15 Rank insert(Rank r,T const& e)

在秩r的位置插入元素，后面元素整体后移, 平均时间复杂度O(n)

```c++
template<typename T>
Rank Vector<T>::insert(Rank r,T const& e){
    assert(0<=r && r<=size_);
    ++size_;
    expand();
    for(int i=size_-1;i>r;--i)
        elem_[i] = elem[i-1];
    elem_[r] = e;
    return r;
}

// 书本实现
//! 插入元素 
Rank insert(Rank r, T const& e) { // input sensitive 输入敏感，平均O(n)
	assert(0 <= r && r <= size_);
	expand();
	for (int i = size_; i > r; i--) { // r之后的元素整体右移
		elem_[i] = elem_[i - 1];
	}
	elem_[r] = e;
	size_++;
	return r;
}
```

#### 3.16  Rank insert(T const& e)

在最后插入元素

```c++
template<typename T>
Rank Vector<T>::insert(T const& e){
    return insert(size_,e);
}
```

#### 3.17  int remove(Rank lo,Rank hi）

未减小操作的复杂度， 先实现区间上去除元素，再依据区间实现去除单个元素

删除区间 [lo,hi) 上的元素 ,  返回被删除元素的个数

```c++
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi){
    assert(0<=lo && lo<=hi && hi<=size_);
    if(lo == hi) return 0;
    while(hi < size_ ){
        elem[lo++] = elem[hi++];
    }
    // 更新规模，直接丢弃[lo,size_ = hi)区间
    size_ = lo;
    // shrink();
    return hi-lo;
}
```

#### 3.18  T remove(Rank r)  

返回去除的秩为r的元素的值

```c++
template<typename T>
T Vector<T>::remove(Rank r){
    assert(0<=r && r<size_);
    T e = elem_[r];
    remove(r,r+1);
    return e;
}
```

####  3.19   void sort(Rank lo,Rank hi)

####  3.20 int deduplicate()

无序去重，不断在前缀中查找雷同元素

时间复杂度$O(n^2)$的实现

返回删除元素的规模

```c++
template<typename T>
int Vector<T>::deduplicate(){
    int old_size = size_;
    while(i<size_){
    	find(elem_[i],0,i)<0?++i:remove(i);
    }
    return old_size - size_;
}
```

#### 3.21 int uniquify()

有序向量的去重

对于重复的元素，找到最后一个重复元素的位置进行移动

返回删除元素大的规模

```c++
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
```







对于有序向量的查找，可以采用多种方法实现

- 二分查找，递归版
- 二分查找，迭代版
- 基于fibnacci数列版

## 有序向量查找算法的分析

在**A [ lo， hi ) 上查找元素**

### 1. 二分查找版本A，减而治之

每次分成三个区间` [lo, mi) [mi] [mi+1,hi)`

有多个元素命中时，不保证返回秩的最大者，

查找失败时简单返回-1，

平均查找长度：找左子树O(1)   右子树则在比较左边的基础上再来一次所以O(2) ,即平均查找长度为$O(1.5*log_2n)$      为使查找失败的比较次数最小可以采用不是二分的查找，如`Fibonacci数列`

```c++
template<typename T>
static Rank Vecotr<T>::binary_search_A(T* A,T const& e,Rank lo,Rank hi){
    while(lo<hi){
        Rank mi = (lo + hi)>>1;
        if(e < A[mi]) { hi = mi;}
        else if(e > A[mi]) { lo = mi+1;}
   		else return mi;
    }
    // 查找失败
    return -1;
}
```



### 2. 二分查找版本B，两分支，一次比较,A的改进版

改进版本变成两个分支`[lo,mi) [mi,hi)`, 只需比较一次就能进入下一个分支

平均查找长度 $O(log(n))$

```c++
template<typename T>
static Rank Vector<T>::binary_search_B(T* A,T const& e,Rank lo,Rank hi){
	Rank mi = (hi + lo)>>1;
	while(1 < hi - lo){
		(e<A[mi])?hi = mi: lo=mi;
	}
    return (e==A[lo])?lo:-1;
}
```

- 有时算法需要根据优先级返回其中最大优先级(秩最大的元素)。则若有重复元素则要找到其中秩最大的，无该元素则要找到最不大于e的最后一个元素，不小于e最前的元素。

### 3. 二分查找版本C，查找失败时返回查找失败位置

- 当命中多个元素时，总能保证返回最大秩

- 失败时，能够返回失败位置
-  查找成功后不能提前终止

```c++
template<typename T>
static Rank Vector<T>::binary_search_C(T* A,T const& e,Rank lo, Rank hi){
    while(lo<hi){
        Rank mi = (lo+hi)>>1;
        (e<A[mi])?hi = mi: lo = mi+1;
    }
    return lo--;
}
```

- 算法的正确性： 由数学归纳法可得

### 4.   基于fibonacci数列的查找

 二分查找划分时，左半部比较一次，右半部比较两次，所以可以基于黄金分割进行划分

平均查找长度 $ O(1.44 log_2(n))$

用`hi-lo`作为FIB数列的长度,   利用fib数列改进二分查找版本A

```c++
template<typename T>
static Rank Vector<T>::fibonacci_search_A(T* A,T const& e,Rank lo,Rank hi){
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
```

**版本B,    改良版本**

```c++
template<typename T>
static Rank Vector<T>::fibonacci_search_B(T* A,T const& e,Rank lo,Rank hi){
    Fibonacci<itn> fib(hi-lo);
    while(lo < hi){
        while(hi - lo < fib.get()){fib.prev();}
        Rank mi = lo + fib.get() - 1;
        (e<A[mi])? hi=mi: lo=mi+1;    
    }
    return --lo;
}
```

###   5.  插值搜索，类似于图像处理中插值法

```c++
template<typename T>
static Rank Vector<T>::interploation_search(T* A ,T const& e,Rank lo,Rank hi){
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
```

**整合**

```c++
template<typename T>
static Rank Vecotr<T>::fibonacci_search(T* A,T const& e,Rank lo,Rank hi){
#if TEST_BUILD
    switch(rand()%2){
        case 0 :return fibonacci_search_A(A,e,lo,hi);
        default:return fibonacci_search_B(A,e,lo,hi);
    }
#else
    return fibonacci_search_B(A,e,lo,hi);
#endif    
}
  

template<typename T>
static Rank Vector<T>::binary_search(T* A,T const& e,Rank lo,Rank hi){
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


template<typename T>
Rank Vecotr<T>::search(T* A,T const& e,Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= A->size_);
#if TEST_BUILD
    return (rand()%2)?binary_search_C(A,e,lo,hi):fibonacci_search_B(A,e,lo,hi);
#else
    return fibonacci_search_B(A,e,lo,hi);
#endif    
}
```



##  排序算法的分析

###  1. 冒泡排序

每一趟检查相邻元素是否是顺序，不是则交换元素，经过多趟直到排好顺序位置

- 稳定算法  ： 排序后重复元素的相对次序可能发生变化 , 在冒泡排序的过程中重复元素只是相互靠拢，但不会交换位置

首先实现单趟交换,  利用一个标志位来判断排序是否完成

```c++
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
```

### 2.冒泡排序 版本a

不断单趟扫描， 直到次序正确,  每次扫描至少将一个最大元素放到正确次序，

每次交换扫描后， 问题的规模 - 1   ，复杂度为O(n^2)

```c++
template<typename T>
void Vector<T>::bubble_sort(Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= size_);
    while(!bubble(lo,hi--)){};
}
```

###  3.冒泡排序加速版 A， 对[lo,hi）左侧 部分乱序时

返回最右侧的逆序对的位置，先对原始版本在第一次时有更大的问题缩减空间,  仅`A[0,n^(1/2))`乱序时

- 时间复杂度  $O( n + (\sqrt n)^2 ) = O(n)$

```c++
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
```

```c++
template<typename T>
void Vector<T>::bubble_sort_fast(Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= size_);
    while(lo < (hi = bubble_fast(lo,hi)) ){}
}
```

### 4.冒泡排序加速版 B， 对[lo,hi）右侧 部分乱序时

对于区间$[n-\sqrt n,n)$ , 

- 记录最左侧乱序对的位置

```c++
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
```

- 左右同时加速

```c++
template<typename T>
void Vector<T>::bubble_sort_fast_2(Rank lo,Rank hi){
    assert(0 <= lo && lo <= hi && hi <= size_);
    while( (lo=bubble_fast_2(lo,hi)) < (hi = bubble_fast(lo,hi)) ){}
}
```

### 5. 归并排序

**思想： **将两路元素逐一比较， 合并成一个新的有序向量

该算法始终严格的按顺序处理，适用于磁带等顺序存储器

**实现:** 采用分治策略将 

自顶向下：一个向量不断划分为小的向量，

自底向上：对每个小向量归并的到一个稍大的向量，稍大的向量继续归并成大向量

**时间复杂度：** O(nlogn)    划分深度log层，每次比较n次，最坏情况nlogn

将区间`[lo,hi)`划分成`[lo,mi)`和`[mi,hi)`

```c++
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
```

**二路归并实现**

由于归并的元素在原向量中都是相邻的，所以采用三个位置`lo`,`mi`,`hi`

```c++
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
```





 