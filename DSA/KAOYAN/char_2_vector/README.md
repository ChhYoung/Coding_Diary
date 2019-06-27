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
/**************************构造************************/
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
/****************** 获取状态  *****************************/
    Rank size() const { reutrn size_; }
    bool empty() const { return !size_; }
}

```

#### 3.1  copy_from(T const* A,Rank lo,Rank hi)

复制A[lo,hi)的元素，并设置好向量的规模与容量

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
    delete[] odl_elem_;
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

