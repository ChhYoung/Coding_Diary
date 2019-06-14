// ./DSA/include/src/BinNode.h
#ifndef _DSA_INCLUDE_SRC_BINNODE_H__
#define _DSA_INCLUDE_SRC_BINNODE_H__ 

namespace DSA {

enum class RBColor {
	RB_RED,
	RB_BLACK,
};

// 二叉树结点
template<typename T>
struct BinNode {
// 成员
	// 为方便定义一个指向节点的指针
	typedef BinNode<T>* Ptr;
	// 数值
	T data_;
	// 父节点
	Ptr parent_;
	// 左孩子
	Ptr lChild_;
	// 右孩子
	Ptr rChild_;
	// 高度
	int height_;
	// 若为红黑树，则有颜色属性
	RBColor color_;

// 构造函数
	BinNode()
		: data_()
		, parent_(nullptr)
		, lChild_(nullptr)
		, rChild_(nullptr)
		, height_(-1)
		, color_(RBColor::RB_RED)
	{}

	BinNode(const T& data, Ptr parent = nullptr, Ptr lChild = nullptr, Ptr rChild = nullptr, int height = 0, RBColor color = RBColor::RB_RED)
		: data_(data)
		, parent_(parent)
		, lChild_(lChild)
		, rChild_(rChild)
		, height_(height)
		, color_(color)
	{}
// 操作接口
	// 统计当前节点的后代总数
	int size() const {
		int s = 1;
		if (lChild_) { s += lChild_->size(); }
		if (rChild_) { s += rChild_->size(); }
		return s;
	}

	// 重载操作符
	bool operator<(const BinNode& rhs) const { return this->data_ < rhs.data_; }
	bool operator>(const BinNode& rhs) const { return this->data_ > rhs.data_; }
	bool operator==(const BinNode& rhs) const { return this->data_ == rhs.data_; }
	bool operator!=(const BinNode& rhs) const { return this->data_ != rhs.data_; }

	// 一些常用的接口
	inline bool isRoot() const { return !parent_; }
	inline bool isLChild() const { return parent_ && parent_->lChild_ == this; }
	inline bool isRChild() const { return parent_ && parent_->rChild_ == this; }
	inline bool hasParent() const { return parent_; }
	inline bool hasLChild() const { return lChild_; }
	inline bool hasRChild() const { return rChild_; }
	inline bool hasChild() const { return lChild_ || rChild_; }
	inline bool hasBothChild() const { return lChild_ && rChild_; }
	inline bool isLeaf() const { return lChild_ && rChild_; }
	// 得到兄弟节点
	inline Ptr sibling() const { return isLChild() ? parent_->rChild_ : parent_->lChild_; }
	// 得到叔叔节点
	inline Ptr uncle() const { return parent_->isLChild() ? parent_->parent_->rChild_ : parent_->parent_->lChild_; }
	// -----------------------------------------------------------------------------------------
	// 插入
	Ptr insertAsLeftChild(const T& data) { return lChild_ = new BinNode(data, this); }
	Ptr insertAsRightChild(const T& data) { return rChild_ = new BinNode(data, this); }

};// end of BinNode


 /**********************************************************************************************************/
//  一些辅助函数

// 节点高度
template<typename T>
int stature(BinNode<T>* node) {
	return node ? node->height_ : -1;
}




}
#endif //  _DSA_INCLUDE_SRC_BINNODE_H__