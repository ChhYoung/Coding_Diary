#ifndef _DSA_INCLUDE_SRC_BINNODE_H__
#define _DSA_INCLUDE_SRC_BINNODE_H__ 

namespace DSA {

// ������ڵ���ɫ
enum class RBColor {
	RB_RED,
	RB_BALCK,
};

// �������ڵ�
template<typename T>
struct BinNode {
	typedef BinNode<T>* Ptr;
// ����
	T data;
	// ���ڵ�
	Ptr parent;
	// ����
	Ptr LChild;
	// �Һ���
	Ptr RChild;
	// �߶�
	int height;
	// ������ڵ���ɫ
	RBColor color;

// ���캯��
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

// �����ӿ�
	// ͳ�Ƶ�ǰ�ڵ�ĺ������
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

	// BinNode ״̬�����ж�
	inline bool isRoot() const { return !parent };
	inline bool isLChild() const { return parent && parent->LChild == this; }
	inline bool isRChild() const { return parent && parent->RChild == this; }
	inline bool hasParent() const { return parent; }
	inline bool hasLChild() const { return LChild; }
	inline bool hasRChild() const { return RChild; }
	inline bool hasChild() const { return LChild || RChild; }
	inline bool hasBothChild() const{ return LChild && RChild; }
	inline bool isLeaf() const { return !LChild && !RChild; }
	// �ֵ�
	inline Ptr sibling() const { 
		return isLChild() ? parent->RChild : LChild;
	}
	inline Ptr uncle() const {
		return parent->isLChild() ? parent->parent->RChild : parent->parent->LChild;
	}

	//  ����ڵ�
	Ptr insertAsLeftChild(const T& data) {
		// ���ز���Ľڵ㣬֮ǰ�Ľڵ��Ϊ���ڵ�
		return (LChild = new BinNode(data, this));
	}
	Ptr insertAsRightChild(const T& data) {
		// ���ز���Ľڵ㣬֮ǰ�Ľڵ��Ϊ���ڵ�
		return (RChild = new BinNode(data, this));
	}

};

/****************************     ��������   ************************************/

// �ڵ�߶�
template<typename T>
int stature(BinNode<T>* node) {
	return node ? node->height : -1;
}

}





#endif //  _DSA_INCLUDE_SRC_BINNODE_H__