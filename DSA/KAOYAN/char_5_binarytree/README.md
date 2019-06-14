# 二叉树

[TOC]

## 1  基本概念

### 1.1 常见名词:

- 祖先\后代:包括节点本身， 真祖先\ 真后代:不包括节点本身

- 度数\度 degree  ： 节点孩子的总数,

- K-ary tree:  k叉树，每个节点孩子数不超过K

## 2  二叉树的实现

### 2.1 二叉树节点 BinNode 模板类



**version 0.1**

```c++
#ifndef CODE_DIARY_DSA_BINNODE_H__
#define CODE_DIARY_DSA_BINNODE_H__

// 节点颜色
#define BinNodePosi(T) BinNode<T>* 
// 节点高度
#define stature(p) ((p)->height : -1) 

namespace DSA{

// 红黑树 节点颜色
typedef enum{ RB_RED,RB_BLACK} RBColor;

// 二叉树节点模板类
template <typename T>
struct BinNode{
// 数据成员
    // 数值
    T data;
    // 父节点，左子节点，右子节点
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    // 高度
    int height;
    // Null path length 左式堆采用的空节点通路长度
    int npl;
    // 颜色，红黑树
    RBColor color;

// 构造函数
    BinNode():
        parent(nullptr),lc(nullptr),rc(nullptr),
        height(0),
        npl(1),
        color(RB_RED){}
    // 重载构造函数
    BinNode(T e,
        BinNodePosi(T) p=nullptr,BinNodePosi(T) lc=nullptr,BinNodePosi(T) rc=nullptr,
        int h = 0,
        int l = 1,
        RBColor c = RB_RED ) :
        data(e),parent(p),lc(lc),rc(rc),height(h),npl(l),color(c){}

// 操作接口
    // 当前节点的所有后代数
    int size();
    // 在当前节点的左孩子处插入节点
    BinNodePosi(T) insertAsLC(T const &);
    // 在当前节点的右孩子处插入节点
    BinNodePosi(T) insertAsRC(T const &);
    // 取得当前节点的直接后继
    BinNodePosi(T) succ();
    // 子树层次遍历
    template<typename VST> void travLevel(VST&);
    // 子树先序遍历
    template<typename VST> void travPre(VST&);
    // 子树中序遍历
    template<typename VST> void travIn(VST&);
    // 子树后次遍历
    template<typename VST> void travPost(VST&);

// 比较器，判决器
    // 小于
    bool operator<(BinNode const& bn){return data < bn.data;}
    // 大于
    bool operator>(BinNode const& bn){return data > bn.data;}
    // 等于
    bool operator==(BinNode const& bn){return data == bn.data;}
    // 大于等于
    bool operator>=(BinNode const& bn){return data >= bn.data;}
    // 小于等于
    bool operator<=(BinNode const& bn){return data <= bn.data;}
};
}

#endif  // CODE_DIARY_DSA_BINNODE_H__
```

