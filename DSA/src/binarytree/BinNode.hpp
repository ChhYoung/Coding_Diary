#ifndef CODE_DIARY_DSA_SRC_BINNODE_H__
#define CODE_DIARY_DSA_SRC_BINNODE_H__

#include<iostream>
#include<cstdlib>
// 节点颜色
#define BinNodePosi(T) BinNode<T>* 
// 节点高度,空树为-1
#define stature(p) ((p)? (p)->height : -1) 

/************* 节点状态性质的判断  *************/
// x : BinNode object
// 当前节点是不是根节点
#define IsRoot(x) (!((x).parent))
// 当前节点是左子节点还是右子节点
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc) )
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc) )
#define HasParent(x) ( !IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x)  (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasBothChild(x)) 

/************* 与节点有特点关系的节点与指针  *************/
// 兄弟，返回兄弟节点的指针
#define sibling(p)  \
    (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc);
// 叔叔,父节点的父节点的兄弟
#define uncle(x) \
    (IsLChild(*(x->parent)) ? (x)->parent->parent->rc :(x)->parent->parent->lc )    
// 来自父亲的引用,通过父节点来引用当前节点
#define FromParentTo(x) \
    (IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc))



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
    // 子树后序遍历
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

// 插入子节点,用第二个构造函数, this指向当前节点，以当前节点为父节点，
//  e为插入的值，给lc赋值，这里假设插入前当前左（右)节点为空
//  try catch 检查是否不是空
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e){
    /*
    try{
        if(HasLChild(*this))
            throw "left  child is not null";
    }
    catch(const char* msg) {
     std::cerr << msg << std::endl;
    }*/
    return lc = new BinNode(e,this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e){
    /*
    try{
        if(HasRChild(*this))
            throw "right  child is not null";
    }
    catch(const char* msg) {
     std::cerr << msg << std::endl;
    }*/
    return rc = new BinNode(e,this);
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST& visit){
    switch(std::rand() % 5){
        case 1: travIn_1(this,visit);break;
        case 2: travIn_2(this,visit);break;
        case 3: travIn_3(this,visit);break;
        case 4: travIn_4(this,visit);break;
        default: travIn_R(this,visit);break;
    }
}



#endif  // CODE_DIARY_DSA_SRC_BINNODE_H__