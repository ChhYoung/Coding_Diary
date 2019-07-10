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
    // 有序列表区间查找
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
template<typrname T>
void List<T>::init(){
    if(!head){
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

在无序列表中节点p(可为trailer)的n个前驱中，找到值为e的秩最大者

```c++
template<typename T>
NodePtr List<T>::find(T const& e,int n,NodePtr p) const{
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
NodePtr List<T>::search(T const& e,int n, NodePtr p) const{
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
NodePtr List<T>::search(T const& e) const{
    return search(e, size_, trailer);
}
```

### NodePtr select_max(NodePtr p, int n);

在p及其n-1个后继中选出最大者

```c++
template<typename 		T>
NodePtr List<select_max(NodePtr p, int n);


```

