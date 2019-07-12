// ./DSA/include/src/BinTree.h
//#pragma once 

#ifndef _DSA_INCLUDE_SRC_BINTREE_H__
#define _DSA_INCLUDE_SRC_BINTREE_H__

#include"BinNode.h" 
#include"release.h"

#if TEST_BUILD
#include <stdlib.h>  // rand
#endif

namespace DSA {

	// ������
template<typename T>
class BinTree {
public:
	typedef BinNode<T> Node;
	typedef Node* NodePtr;
	typedef BinTree<T> BinTreeType;
	typedef BinTreeType* BinTreePtr;

protected:
	// �������ԣ� �����������ľ���ṹ��Ϊ�ڵ�������� BinNode ��
	// ��ģ
	int size_;
	// ����
	NodePtr root_;

		// ���½ڵ�node�ĸ߶�
		// �߶�Ϊ�ӽڵ����߶ȼ�һ��ÿ���ڵ���������ʱ��߶ȶ���Ҫ���£�����ʵ�ʹ����нڵ���ѷ����ӽڵ�ı仯������
		//		��ȡ���нڵ��������뿪��ʱ ���������ȵĸ߶�
		// ʵ�֣� v�ڵ�ֻ��ȡ���Һ��ӵ����߶� + 1 ����,v������parentָ����������,���θ��¸߶�
		// �Ż��汾: 
		// 1. ����1���µĹ����з���ĳһ���ȵĸ߶�û�и������ֹͣ�� �����ı�ڵ�C����A������·��������C��
		//     ��A�ĸ߶���Ȼ�����ı�
		// 2. �Ľ����ӶȲ��䣬�������˲���Ҫ�ĸ���

	// ԭʼ�汾,�������
	// O(1)
	virtual int updateHeight(NodePtr node) {
		auto lh = stature(node);
		auto rh = stature(node);
		return node->height_ = 1 + (lh < rh ? rh : lh);
	}
	// �Ż��汾
	// O(n = depth(x))
	// ������-->��Ҫ����
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
	// ���Ը��׵�����
	// ���ڵ�ָ��ǰ�ڵ��ָ��
	NodePtr& fromParentTo(NodePtr node) {
		return node->isRoot() ? root_ : (node->isLChild() ? node->parent_->lChild_ : node->parent_->rChild_);
	}

	// ���ֲ���ڵ�ķ�ʽ ,��ԭ���޽ڵ�������
	// ��Ϊ���ڵ㣬���ӽڵ㣬���ӽڵ�
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
	// ��������
	// lc��Ϊ�ڵ�x�����������룬lc�����ÿ�
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

	// rc��Ϊ�ڵ�x�����������룬rc�����ÿ�
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

	// ɾ����������x�ڵ㼰���������ر�ɾ���Ľڵ�ĸ���
	static int removeAt(NodePtr x) {
		if (!x) { return 0; }
		int n = 1 + removeAt(x->lChild_) + removeAt(x->rChild_);
		release(x->data_);
		release(x);
		return n;
	}

	// ɾ����λ��x���ڵ�Ϊ����ֻ�������ظ�����ԭ�ȵĹ�ģ
	int remove(NodePtr x) {
		// �ж����Ը��ڵ������
		fromParentTo(x) = nullptr;
		// ���¸߶�
		updateHeightAbove(x->parent_);
		int n = removeAt(x);
		size_ -= n;
		return n;
	}

	// ������x�ӵ�ǰ����ժ������ת��Ϊһ�Ŷ�������
	BinTreePtr secede(NodePtr x) {
		fromParentTo(x) = nullptr;
		updateHeightAbove(x->parent_);
		auto tree = new BinTreeType();
		x->parent_ = nullptr;
		tree->root_ = x;
		tree->size_ = x->size();
		size_ -= tree->size;
		return tree;
	}

	/*********************************************************************************************/
	//  �������ı���
	// �������
	template<typename VST>
	void travPreOrder(VST& visit) {
		if (root_) {
#if TEST_BUILD
		}
	}
#endif	

};// end of BinTree

} // end of namespace

#endif // _DSA_INCLUDE_SRC_BINTREE_H__