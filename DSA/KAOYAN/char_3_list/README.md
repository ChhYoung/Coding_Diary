# List

[TOC]

## 1. list node的设计与实现

**链表节点的实现** 

*list_node.h*

```c++
#pragma once

#ifndef _DSA_INCLUDE_SRC_LIST_NODE_H__
#define _DSA_INCLUDE_SRC_LIST_NODE_H__

namespace  DSA
{
// 秩    
using Rank = int;
// 链表节点
template<typename T>
struct ListNode{
    // 定义节点及节点指针的简洁命名
    using Node = ListNode<T>;
    using Ptr = Node*;
// members
    // 数据
    T data;
    // 前驱
    Ptr pred;
    // 后继
    Ptr succ;
// 构造函数
    ListNode():data(),pred(nullptr),succ(nullptr){}
    ListNode(T e,Ptr p=nullptr,Ptr s=nullptr)
            :data(e),pred(p),succ(s)
            {}
// 操作接口            
    // 插入一个节点作为当前节点的前驱
    // 返回该插入的节点
    Ptr insert_as_pred(T const& e){
        auto node = new Node(e,pred,this);
        if(pred){
            pred->succ = node;
        }
        pred = node;
        return node;
    }         
    // 插入一个节点作为当前节点的后继
    // 返回该插入的节点
    Ptr insert_as_succ(T const& e){
        auto node = new Node(e,this,succ);
        if(succ){
            succ->pred = node;
        }
        succ = node;
        return node;
    }      
}; // ListNode
} // namespace  DSA
#endif // _DSA_INCLUDE_SRC_LIST_NODE_H__
```

## 2. List 设计与实现

```c++
template<typename T>
class List{
    using Node =  ListNode<T>; 
    using NodePtr = Node*;
private: 
// 数据成员 
    // 规模
    int size_ = 0;
    // 头部哨兵
    NodePtr header = nullptr;
    // 尾部哨兵
    NodePtr trailer = nullptr;
protected:
    // 列表创建时的初始化
    void init();
    // 清除所有节点
    int clear();
    // 复制list中起始位置为p，开始的n项        
    void copy_nodes(NodePtr p,int n);
    /* 
    * @brief   有序列表的归并
    * @param p 本列表内节点p的引用，归并完成时指示区间的新起点
	* @param n 本列表内从p开始节点数量
	* @param L 要归并的列表
	* @param q L的节点q
	* @param m L内从节点q开始节点数量
    */
    void merge(NodePtr& p, int n, List<T>& L, NodePtr q, int m);
    // 归并排序
    void merge_sort(NodePtr& p,int n);
    // 选择排序
    void selection_sort(NodePtr p,int n);
    // 插入排序
    void insertion_Sort(NodePtr p,int n);

public: 
// 构造函数
    List(){ init();}  
    // 整体复制list  L
    List(List<T> const& L){
        copy_nodes(L.first(),L.size_);
    }
    // 复制list L自第r项起的n项
    List(List<T> const& L,Rank r,int n){
        copy_nodes(L[r],n);
    }
    // 复制自位置p起的n项
    List(NodePtr p,int n){
        copy_nodes(p,n);
    }
// 析构函数
    ~List(){
        clear();
    }
// 可写访问接口    
/****辅助操作接口*************/
	//********4个插入
    // 作为第一个元素插入
	NodePtr insert_as_first(T const& e){
        ++size_;
		return head->insert_as_pred(e);
    }
    // 作为最后一个元素插入
    NodePtr insert_as_last(T const& e){
        ++size_;
		return trailer->insert_as_pred(e);
    }
    // 插入作为p节点的下一个节点
    NodePtr insert_after(NodePtr p, T const& e){
        ++size_;
        return p->insert_as_succ(e);
    }
    // 插入作为p节点的上一个节点
    NodePtr insert_before(NodePtr p, T const& e){
        ++size_;
        return p->insert_as_pred(e);
    }
    // 删除指定节点，返回删除后节点的值
    T remove(NodePtr p);
    // 清空list，返回list的规模
    int clear();
    // 全列表归并排序
    void merge(List<T>);
    // 区间排序
    void sort(NodePtr p, int n){
		switch(rand()%3){
        	case 0: insertion_sort(p,n); break;
       		case 1: selection_sort(p,n); break;
            default: merge_sort(p,n); break;
    	}        
    }
    // 无序去重
    int deduplicate();
    // 有序去重
    int uniquify();
    // 前后倒置
    void reverse();
// 只读访问接口
    // 返回规模
    Rank size() const {return size_;}
    // 判断是否为空
    bool empty() const {return size_ <= 0;}
    // 首节点(可能为空)
    NodePtr first() const { return header->succ;}
    // 末节点(可能为空)
    NodePtr last() const { return trailer->pred;}
    // 检查节点是否合法
    bool valid(NodePtr p) const {return p && p != header && p != trailer;}
    // 重载操作符 ， 按秩访问
    T& operator[](Rank r) const;
    // 相邻逆序对的数量
    int disordered() const;
    // 无序列表查找
    NodePtr find(T const& e) const;
    // 无序列表区间查找
    NodePtr find(T const& e,int n,NodePtr p) const;
    // 有序列表查找
    NodePtr search(T const& e) const;
    // 有序列表区间查找 , 在当前节点的前n 个节点中查找，不包括 p
    NodePtr search(T const& e,int n, NodePtr p) const;
    // 整体最大者
    NodePtr select_max();
    // 在p及其n-1个后继中选出最大者
    NodePtr select_max(NodePtr p, int n);
};
```

### void init()

初始化列表，即只生成头尾哨兵节点

```c++
template<typename T>
void List<T>::init(){
    if(!header){
        header = new Node();
    }
    if(!trailer){
        trailer = new Node();
    }
    header->pred = nullptr;
    header->succ = trailer;
    trailer->pred = header;
    trailer->succ = nullptr;
    size_ = 0;
}
```

### void copy_nodes(NodePtr p,int n)

复制list中起始位置为p，开始的n项

不断的作为最后一个节点插入

```c++
template<typename T>
void List<T>::copy_nodes(NodePtr p,int n){
	init();
    while(n--){
        insert_as_last(p->data);
        p = p->succ;
	}
}
```

###  T remove(NodePtr p)

删除节点p，返回p的数值

```c++
template<typename T>
T List<T>::remove(NodePtr p){
    T data = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    --size_;
    return data;
}
```

### int clear()

清空list， 返回list的规模

```c++
template<typename T>
int List<T>::clear(){
    int old_size = size_;
    while(size_ > 0){
        remove(header->succ);
    }
    return old_size;
}
```

### T& operator\[](Rank r) const;

重载操作符，按秩访问

```c++
template<typename T>
T& List<T>::operator[](Rank r) const{
    assrt(0 <= r && r < size_);
    auto ptr = header->succ;
    while(r--){
        ptr = ptr->succ;
    }
    return ptr->data;
}
```

### int disordered() const;

相邻逆序对的数量

```c++
template<typename T>
int List<T>::disordered() const{
    if(0 == size_) return 0;
    auto ptr = header->succ;
    int cnt = 0;
    for(int i = 0; i <= size_-2 ; ptr = ptr->succ,++i){
        if(ptr->data > ptr->succ->data)
            ++cnt;
    }
    return cnt;
}
```

### NodePtr find(T const& e,int n,NodePtr p) const;

在无序列表中节点p(可为trailer)的 n个前驱 中，找到值为e的秩最大者

```c++
template<typename T>
typename List<T>::NodePtr List<T>::find(T const& e,int n,NodePtr p) const{
    while(0 < n--){
        if(e == (p=p->pred)->data)
            return p;
    }
    return nullptr;
}

template<typename T>
NodePtr List<T>::find(T const& e) const{
    return find(e,size_,trailer);
}

```

### NodePtr search(T const& e,int n, NodePtr p) const;

在有序区间查找, 节点p的前n个节点(不包括p)

```c++
template<typename T>
typename List<T>::NodePtr List<T>::search(T const& e,int n, NodePtr p) const{
    assert(0<=n && n <= size_);
    if(size_ == 0) {return nullptr;}
    while(n-- && p != header->succ){
        if((p=p->pred)->data <= e){
            break;
        }
    }
    return p;
}

template<typename T>
typename List<T>::NodePtr List<T>::search(T const& e) const{
    return search(e, size_, trailer);
}
```

### NodePtr select_max(NodePtr p, int n);

在p及其n-1个后继中选出最大者

```c++
template<typename T>
typename List<T>::NodePtr List<T>::select_max(NodePtr p, int n){
	auto max_p = p;
    for(NodePtr cur = p;1 < n; --n){
        if((cur = cur->succ)->data >= max_p->data){
            max_p = cur;
        }
    }
    return max_p;
}

/*template<typename T>
typename List<T>::NodePtr List<T>::select_max(NodePtr p, int n){
	auto ptr = p;
    while((n--)>1){
		if(ptr->data < p->data)
            ptr = p;
        p = p->succ;
    }
    return ptr;
}
*/

// 整体找最大值
template<typename T>
typename List<T>::NodePtr List<T>::select_max(){
    return select_max(header->succ,size_);
}
```

### int deduplicate();

无序去重,   返回被删除元素的数量

不停在子区间中找重复元素

```c++
template<typename T>
int List<T>::deduplicate(){
    // 平凡列，无重复
    if(size_<2) return 0;
    int old_size = size_;
    auto p = header;
    Rank r = 0;
    while( (p=p->succ) != trailer){
        auto q = find(p->data,r,p);
        q ? remove(p) : ++r;
	}
    return old_size - size_;
}
```

###  int uniquify();

有序去重，  返回被删除元素的数量

比较相邻元素

```c++
template<typename T>
int List<T>::uniquify(){
    if(size_ < 2) return 0;
    int old_size = size_;
    auto p = first();
    NodePtr q;
    while((q = p->succ) != trailer){
        if(p->data != q->data) p = q;
        // 雷同则删除后者
        else remove(q);
    }
    return old_size - size_;
}
```

### void reverse();

前后倒置

```c++
// 实现方式 ：交换元素
template<typename T>
void List<T>::reverse(){
    auto p = header;
    auto q = trailer;
    for(int i=1; i < size_; i+=2){
        swap((p=p->succ)->data, (q=q->pred)->data);
    }
}   

```



### void selection_sort(NodePtr p,int n);

选择排序： 设后面的有序，每次在前面的无序元素中选一个最大的放到后面

- 在vector中是交换元素，所以不稳定
- 在list中时插入，稳定

```c++
// 实现一：
// 对起始p的n个元素排序
template<typename T>
void selection_sort(NodePtr p,int n){
    NodePtr head = p->pred;
    NodePtr tail = p->succ;
    // 确定待排序区间 (head, tail)
    for(int i = 0;i < n;++i){ tail = tail->succ;}
    while(1 < n){
        // 在(n--)个元素的区间内找到最大元素
        NodePtr max_p = select_max(head->succ, n--);
        // 插入到后面
        insert_before(tail, remove(max_p));
        // 缩小下界
        tail = tail->pred;
    }
}


// 改进版一：减少 remove  insert中的 new delete 操作带来的运行时间
template<typename T>
void selection_sort(NodePtr p,int n){
    NodePtr head = p->pred;
    NodePtr tail = p->succ;
    // 确定待排序区间 (head, tail)
    for(int i = 0;i < n;++i){ tail = tail->succ;}
    while(1 < n){
        // 在(n--)个元素的区间内找到最大元素
        NodePtr max_p = select_max(head->succ, n--);
        /************************************/
        // 改为交换数值
        swap(tail->pred->data, max_p->data);
        // 缩小下界
        tail = tail->pred;
    }
}
//  版本二：若max_p 刚好是tail->pred 则不用交换
template<typename T>
void selection_sort(NodePtr p,int n){
    NodePtr head = p->pred;
    NodePtr tail = p->succ;
    // 确定待排序区间 (head, tail)
    for(int i = 0;i < n;++i){ tail = tail->succ;}
    while(1 < n){
        // 在(n--)个元素的区间内找到最大元素
        NodePtr max_p = select_max(head->succ, n--);
        /************************************/
        // 改为交换数值
        if(tail->pred != max_p) swap(tail->pred->data, max_p->data);
        // 缩小下界
        tail = tail->pred;
    }
}
```



### void insertion_sort(NodePtr p,int n);

时间复杂度 $O(n^2)$

插入排序：前面有序，将后面每个元素插入到前面的适当位置

**插入排序分析：**

- 插入排序是输入敏感的算法，其运行时间取决与输入元素中`逆序对`的个数，
  - 对于每个逆序的元素，其比较次数，为其所有逆序对的个数    $I_i$
  - 对于算法整体而言，总比较次数为 $ I = \sum I_i$    
  - 算法中的 最后一次失败比较的总次数为 $n$， $n$为逆序元素的个数, 
  - 算法执行的总时间为 $O(I + n)$ 

- 例：

> { 61, 60,  … ,3,2 0, 1 ,2}的逆序前驱的个数为 { 0, 1 ,2,…,59,60, 60 , 59 }
>
> 总的比较次数为 I + n =( 0 + 1 + 2+…+ 59+60+60+59）+ 63



```c++
template<typename T>
void List<T>::insertion_sort(NodePtr p,int n){
    for(int sorted = 0; sorted < n; ++sorted){
        insert_after(search(p->data,sorted,p),p->data);
        p = p->succ;
        remove(p->pred);
    }
}
// 全局情况则： p = first(), n = size_ 

```



