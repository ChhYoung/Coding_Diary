// ./DSA/include/src/BinNode.h
#ifndef _DSA_INCLUDE_SRC_BINNODE_H__
#define _DSA_INCLUDE_SRC_BINNODE_H__ 

namespace DSA {

enum class RBColor {
	RB_RED,
	RB_BLACK,
};

// ���������
template<typename T>
struct BinNode {
// ��Ա
	// Ϊ���㶨��һ��ָ��ڵ��ָ��
	typedef BinNode<T>* Ptr;
	// ��ֵ
	T data_;
	// ���ڵ�
	Ptr parent_;
	// ����
	Ptr lChild_;
	// �Һ���
	Ptr rChild_;
	// �߶�
	int height_;
	// ��Ϊ�������������ɫ����
	RBColor color_;

// ���캯��
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
// �����ӿ�
	// ͳ�Ƶ�ǰ�ڵ�ĺ������
	int size() const {
		int s = 1;
		if (lChild_) { s += lChild_->size(); }
		if (rChild_) { s += rChild_->size(); }
		return s;
	}

	// ���ز�����
	bool operator<(const BinNode& rhs) const { return this->data_ < rhs.data_; }
	bool operator>(const BinNode& rhs) const { return this->data_ > rhs.data_; }
	bool operator==(const BinNode& rhs) const { return this->data_ == rhs.data_; }
	bool operator!=(const BinNode& rhs) const { return this->data_ != rhs.data_; }

	// һЩ���õĽӿ�
	inline bool isRoot() const { return !parent_; }
	inline bool isLChild() const { return parent_ && parent_->lChild_ == this; }
	inline bool isRChild() const { return parent_ && parent_->rChild_ == this; }
	inline bool hasParent() const { return parent_; }
	inline bool hasLChild() const { return lChild_; }
	inline bool hasRChild() const { return rChild_; }
	inline bool hasChild() const { return lChild_ || rChild_; }
	inline bool hasBothChild() const { return lChild_ && rChild_; }
	inline bool isLeaf() const { return lChild_ && rChild_; }
	// �õ��ֵܽڵ�
	inline Ptr sibling() const { return isLChild() ? parent_->rChild_ : parent_->lChild_; }
	// �õ�����ڵ�
	inline Ptr uncle() const { return parent_->isLChild() ? parent_->parent_->rChild_ : parent_->parent_->lChild_; }
	// -----------------------------------------------------------------------------------------
	// ����
	Ptr insertAsLeftChild(const T& data) { return lChild_ = new BinNode(data, this); }
	Ptr insertAsRightChild(const T& data) { return rChild_ = new BinNode(data, this); }

};// end of BinNode


 /**********************************************************************************************************/
//  һЩ��������

// �ڵ�߶�
template<typename T>
int stature(BinNode<T>* node) {
	return node ? node->height_ : -1;
}




}
#endif //  _DSA_INCLUDE_SRC_BINNODE_H__