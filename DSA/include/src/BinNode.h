#ifndef _DSA_INCLUDE_SRC_BINNODE_H__
#define _DSA_INCLUDE_SRC_BINNODE_H__ 

namespace DSA {

// 红黑树节点颜色
enum class RBColor {
	RB_RED,
	RB_BALCK,
};

// 二叉树节点
template<typename T>
struct BinNode {
	typedef BinNode<T>* Ptr;
// 数据
	T data;
	// 父节点
	Ptr parent;
	// 左孩子
	Ptr LChild;
	// 右孩子
	Ptr RChild;
	// 高度
	int height;
	// 红黑树节点颜色
	RBColor color;

// 构造函数
	BinNode()
		: data()
		, parent(nullptr)
		, LChild(nullptr)
		, RChild(nullptr)
		, height(-1)
		, color(RBColor::RB_RED)
	{}

	BinNode(const T& data,Ptr parent = nullptr,Ptr LChild=nullptr,Ptr RChild=nullptr,int height=0,RBColor color=RBColor::RB_RED)
		: data(data)
		, parent(parent)
		, LChild(LChild)
		, RChild(RChild)
		, height(height)
		, color(color)
	{}

// 操作接口
	// 统计当前节点的后代总数
	int size() const{
		int s = 1;
		if (LChild) { s += LChild->size(); }
		if (RChild) { s += RChild->size(); }
		return s;
	}

	bool operator<(const BinNode& rhs) const { return this->data < rhs.data; }
	bool operator>(const BinNode& rhs) const { return this->data > rhs.data; }
	bool operator==(const BinNode& rhs) const { return this->data == rhs.data; }
	bool operator!=(const BinNode& rhs) const { return this->data != rhs.data; }

	// BinNode 状态性质判断
	inline bool isRoot() const { return !parent };
	inline bool isLChild() const { return parent && parent->LChild == this; }
	inline bool isRChild() const { return parent && parent->RChild == this; }
	inline bool hasParent() const { return parent; }
	inline bool hasLChild() const { return LChild; }
	inline bool hasRChild() const { return RChild; }
	inline bool hasChild() const { return LChild || RChild; }
	inline bool hasBothChild() const{ return LChild && RChild; }
	inline bool isLeaf() const { return !LChild && !RChild; }
	// 兄弟
	inline Ptr sibling() const { 
		return isLChild() ? parent->RChild : LChild;
	}
	inline Ptr uncle() const {
		return parent->isLChild() ? parent->parent->RChild : parent->parent->LChild;
	}

	//  插入节点
	Ptr insertAsLeftChild(const T& data) {
		// 返回插入的节点，之前的节点变为父节点
		return (LChild = new BinNode(data, this));
	}
	Ptr insertAsRightChild(const T& data) {
		// 返回插入的节点，之前的节点变为父节点
		return (RChild = new BinNode(data, this));
	}

};

/****************************     辅助函数   ************************************/

// 节点高度
template<typename T>
int stature(BinNode<T>* node) {
	return node ? node->height : -1;
}

}





#endif //  _DSA_INCLUDE_SRC_BINNODE_H__