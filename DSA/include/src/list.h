//#pragma once

#ifndef _DSA_INCLUDE_SRC_LIST_H__
#define _DSA_INCLUDE_SRC_LIST_H__

#include<assert.h>
#include"swap.h"
#include"list_node.h"
#include<stdlib.h> // rand()
#include<iostream>
#include<vector>

namespace  DSA
{

template<typename T>
class List{
     
    using Node =  ListNode<T>; 
    using NodePtr = Node*;/*
    typedef ListNode<T> Node ;
    typedef Node* NodePtr;*/

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
    // 用vector的元素来构造
    List(std::vector<T> vec){
        init();
        for(auto& i:vec)
            insert_as_last(i);
    }
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
		return header->insert_as_succ(e);
    }
    // 作为最后一个元素插入
    // push_back
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
    void sort(){ sort(first(),size_); }
    // 无序去重
    int deduplicate();
    // 有序去重
    int uniquify();
    // 前后倒置
    void reverse(); // 改变值

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

/************************* my test functions ************************** */    
public:
    void print();

};// end of class List

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

template<typename T>
void List<T>::copy_nodes(NodePtr p,int n){
	init();
    while(n--){
        insert_as_last(p->data);
        p = p->succ;
	}
}

template<typename T>
T List<T>::remove(NodePtr p){
    T data = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    --size_;
    return data;
}

template<typename T>
int List<T>::clear(){
    int old_size = size_;
    while(size_ > 0){
        remove(header->succ);
    }
    return old_size;
}

template<typename T>
T& List<T>::operator[](Rank r) const{
    assert(0 <= r && r < size_);
    auto ptr = header->succ;
    while(r--){
        ptr = ptr->succ;
    }
    return ptr->data;
}

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

template<typename T>
typename List<T>::NodePtr List<T>::find(T const& e,int n,NodePtr p) const{
    while(0 < n--){
        if(e == (p=p->pred)->data)
            return p;
    }
    return nullptr;
}

template<typename T>
typename List<T>::NodePtr List<T>::find(T const& e) const{
    return find(e,size_,trailer);
}

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

// p开始向右找，存在多个相同最大值时，返回最右边的节点
// 这样能够保证排序的稳定性
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


// 整体找最大值
template<typename T>
typename List<T>::NodePtr List<T>::select_max(){
    return select_max(header->succ,size_);
}

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

template<typename T>
int List<T>::uniquify(){
    if(size_ < 2) return 0;
    int old_size = size_;
    auto p = first();
    NodePtr  q;
    while((q = p->succ) != trailer){
        if(p->data != q->data) p = q;
        // 雷同则删除后者
        else remove(q);
    }
    return old_size - size_;
}

// 实现 : 交换元素
template<typename T>
void List<T>::reverse(){
    auto p = header;
    auto q = trailer;
    for(int i=1; i < size_; i+=2){
        swap((p=p->succ)->data, (q=q->pred)->data);
    }
}   

// 有序list的合并
// 时间复杂度 O(M+N)
template<typename T> 
void List<T>::merge(NodePtr& p, int n, List<T>& L, NodePtr q, int m){
    // 用来记录归并后参数入口位置
    auto pp = p->pred;
    while(0 < m){
        // p在区间内  &&  q >= p
        if( (0<n) && p->data <= q->data){
            if( q ==(p = p->succ)){
                break;
            }
            --n;
        }
        // p超出右界，或者 q < p
        else{
            insert_before(p,L.remove((q = q->succ)->pred));
            --m;
        }
    }
    p = pp->succ;
}

// 时间复杂度 O(nlogn)
template<typename T> 
void List<T>::merge_sort(NodePtr& p,int n){
    if(n<2) return;
    int m=n>>1;
    NodePtr q = p;
    for(int i=0;i<m;++i){
        q = q->succ;
    }
    merge_sort(p,m);
    merge_sort(q,n-m);
    merge(p,m,*this,q,n-m);
}


/****************************************************/
// function for test 
template<typename T>
void List<T>::print(){
    std::cout<<"size : "<<size_<<std::endl;
    if(size_<1) return ;
    else{
        auto ptr = header;
        while((ptr=ptr->succ)!=trailer){
            std::cout<<ptr->data<<" ";
        }
        std::cout<<std::endl;
        return;
    }
    
}

} // namespace  DSA
#endif // _DSA_INCLUDE_SRC_LIST_H__