// b-tree
#ifndef _DSA_INCLUDE_SRC_BTREE_H__
#define _DSA_INCLUDE_SRC_BTREE_H__

#include"btnode.h"
#include"release.h"

namespace DSA{

/*
- B 树： 对于外部存储器如磁盘之类，其读取数据是按批读取，
        所以读一组数据与单个数据没有区别，采用矮宽的多路搜索树
        减少I/O 操作数
- N个节点， m阶
- 高度：  h = θ(logm N); 是BST高度的 1/ [ (log2 M) -1 ]
- 每个节点的分支数：树根>=2, 其他则 [ ceil(m/2) , m ]
- 每个节点的关键码数：分支数-1，  [ ceil(m/2)-1 , m-1 ]
 */
template<typename T> 
class BTree{
public:
    typedef BTNode<T> Node;
    typedef Node* NodePtr;


protected:
    // 关键码总数
    int N_;
    // B-树阶数，至少为3， 创建时指定，一般不了修改
    int m_;
    // 根节点
    NodePtr root_;
    // search 最后访问非空节点的位置
    NodePtr hot_;    

protected:
    // 因插入而上溢之后的分裂处理
    void solveOverflow(NodePtr node){

    }


    // 因删除而下溢后的旋转合并
    void solveUnderflow(NodePtr node){

    }

public: 
    BTree(int order = 3) : m_(order),N_(0) { root_ = new Node();}
    ~BTree() {if(root_){ release(root_);} } 

    // 阶数
    int order() const {return m_ ;}
    // 规模
    int size() const { return N_ ;}
    // 树根
    NodePtr& root(){ return root_;}
    // 判空
    bool empty() const { return !root_;}

    // 
};



}


#endif //  _DSA_INCLUDE_SRC_BTREE_H__
