// ./DSA/include/src/BinTree.h
#ifndef _DSA_INCLUDE_SRC_BINTREE_H__
#define _DSA_INCLUDE_SRC_BINTREE_H__
#include"BinNode.h" 
#include"release.h"

namespace DSA {

	// 二叉树
template<typename T>
class BinTree {
public:
	typedef BinNode<T> Node;
	typedef Node* NodePtr;
	typedef BinTree<T> BinTreeType;
	typedef BinTreeType* BinTreePtr;

protected:
		// 规模
	int size_;
		// 树根
	NodePtr root_;

		// 更新节点node的高度
		// 高度为子节点最大高度加一，每当节点有所增减时其高度都需要更新，但是实际过程中节点很难发现子节点的变化，所以
		//		采取当有节点加入或者离开树时 更新其祖先的高度
		// 实现： v节点只需取左右孩子的最大高度 + 1 即可,v出发沿parent指针逆行向上,依次更新高度
		// 优化版本: 
		// 1. 若在1更新的过程中发现某一祖先的高度没有更新则可停止， 即若改变节点C，若A的最深路径不经过C，
		//     则A的高度自然不会会改变
		// 2. 改进后复杂度不变，但减少了不必要的更新

	// 原始版本
	virtual int updateHeight(NodePtr node) {
		auto lh = stature(node);
		auto rh = stature(node);
		return node->height_ = 1 + (lh < rh ? rh : lh);
	}
	// 优化版本
	virtual int  updateHeightAbove(NodePtr node) {
		while (node) {
			int old_height = node->height_;
			if (old_height == updateHeight(node)) {
				break;
			}
			node = node->parent_;
		}
	}

public:
	// 来自父亲的引用
	NodePtr& fromParentTo(NodePtr node) {
		return node->isRoot() ? root_ : (node->isLChild() ? node->parent_->lChild_ : node->parent_->rChild_);
	}

	// 三种插入节点的方式 ,在原先无节点的情况下
	// 作为根节点，左子节点，右子节点
	NodePtr insertAsRootNode(T const& data) {
		size_ = 1;
		return (root_ = new Node(data));
	}

	NodePtr insertAsLeftChild(NodePtr node,T const& data) {
		size_++;
		node->insertAsLeftChild(data);
		updateHeightAbove(node);
		return node->lChild_;
	}

	NodePtr insertAsRightChild(NodePtr node, T const& data) {
		size_++;
		node->insertAsRightChild(data);
		updateHeightAbove(node);
		return node->rChild_;
	}
	// 子树接入
	// lc作为节点x的左子树接入，lc本身置空
	NodePtr attachAsLChild(NodePtr x, BinTreePtr& lc) {
		if (x->lChild_ = lc->root_) {
			x->lChild_->parent_ = x;
		}
		size_ += lc->size_;
		updateHeightAbove(x);
		lc->root_ = nullptr;
		lc->size_ = 0;
		release(lc);
		lc = nullptr;
		return x;
	}

	// rc作为节点x的右子树接入，rc本身置空
	NodePtr attachAsRChild(NodePtr x, BinTreePtr& rc) {
		if (x->rChild_ = rc->root_) {
			x->rChild_->parent_ = x;
		}
		size_ += rc->size_;
		updateHeightAbove(x);
		rc->root_ = nullptr;
		rc->size_ = 0;
		release(rc);
		rc = nullptr;
		return x;
	}






};// end of BinTree

} // end of namespace

#endif // _DSA_INCLUDE_SRC_BINTREE_H__