// ./DSA/include/src/BinNode.h
#pragma once

#ifndef _DSA_INCLUDE_SRC_BINNODE_H__
#define _DSA_INCLUDE_SRC_BINNODE_H__ 
#include"stack.h"

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
	// 中序遍历下找到直接后继
	Ptr succ(){
		// 记录后继的临时变量
		Ptr s = this;
		// 若有右孩子,则为右子树的最左节点
		if (rChild_) {
			s = rChild_;
			while (s->lChild_) {
				s = s->lChild_;
			}
		}
		// 否则为将当前节点包含在右子树的最低祖先
		else {
			// 逆向沿右上方移动
			while (s->isRChild) {
				s = s->parent_;
			}
			// 再移动一步到达直接后继
			s = s->parent_;
		}
		return s;
	}


/*********************************************************************************************/
protected:
//  二叉树的遍历
	//  先序遍历算法（递归版）辅助递归函数
	// VST 为操作器
	template<typename VST>
	static void visitTravPre(Ptr node, VST& visit) {
		if (!node) { return; }
		visit(node->data_);
		visitTravPre(node->lChild_, visit);
		visitTravPre(node->rChild_, visit);
	}

	// 中序遍历算法（递归版）辅助递归函数
	// VST 为操作器
	template<typename VST>
	static void visitTravIn(Ptr node, VST& visit) {
		if (!node) { return; }
		visitTravPre(node->lChild_, visit);
		visit(node->data_);
		visitTravPre(node->rChild_, visit);
	}
	// 后续遍历算法辅助函数
	template <typename VST>
	static void visitTravPost(Ptr node, VST& visit) {
		if (!node) { return; }
		visitTravPost(node->lChild_, visit);
		visitTravPost(node->rChild_, visit);
		visit(node->data_);
	}
	//  从当前节点出发，沿左分支不断深入，直至没有左分支节点,
	//  沿途节点遇到就访问,并将遇到的节点的右节点压入栈中

	template<typename VST>
	static void visitAlongLeftBranch(Ptr node, VST& visit, Stack<Ptr>& stack) {
		while (node) {
			visit(node->data_);
			stack.push(node->rChild_);
			node = node->lChild_;
		}
	}


// 迭代实现遍历
public:
	// 先序遍历迭代版 v1
	// 通过改写尾递归实现
	template<typename VST>
	void travPre_I1(VST& visit) {
		// 构造辅助栈
		Stack<Ptr> s;
		//根结点入栈
		s.push(this);
		while (!s.empty()) {
			auto x = s.pop();
			visit(x->data_);
			// 由栈的特性，右孩子先于左孩子入栈
			if (x->rChild_) { s.push(x->rChild_); }
			if (x->lChild_) { s.push(x->lChild_); }
		}
	}
	// 先序遍历迭代版 v2
	//  1. 辅助函数
	//  从当前节点出发，沿左分支不断深入，直至没有左分支节点,
	//  沿途节点遇到就访问,并将遇到的节点的右节点压入栈中
	template<typename VST>
	static void visitAlongLeftBranch(Ptr node, VST& visit, Stack<Ptr>& stack) {
		while (node) {
			visit(node->data_);
			stack.push(node->rChild_);
			node = node->lChild_;
		}
	}

	//  2. 先序遍历的实现
	template <typename VST>
	static void travPre_I2(Ptr node, VST& visit) {
		// 构造辅助栈
		Stack<Ptr> s;
		auto x = this;
		while (true) {
			// 遍历左
			visitAlongLeftBranch(node, visit, s);
			if (s.empty()) { break; }
			// 自底向上进入右
			x = s.pop();
		}
	}

	// 迭代实现中序遍历 v1
	template<typename VST>
	void travIn_I1(VST& visit) {
		// 辅助函数，从当前节点出发，沿左分支不断深入，直至没有左分支的节点
		static auto goAloneLetBranch = [](Ptr node, Stack<Ptyr> & stack) {
			while (node) {
				// 将左节点压入栈
				stack.push(node);
				node = node->lChild_;
			}
		}

		Stack<Ptr> s;
		auto x = this;
		while (true) {
			// 访问最左
			goAloneLetBranch(x, s);
			if (s.empty()) { break; }
			// 弹出上一个存入节点
			x = s.pop();
			// 访问数据
			visit(x->data_);
			// 进入其右支
			x = x->rChild_;
		}
	}

	// 迭代实现中序遍历 v2
	// 只是将辅助函数改入其中
	template<typename VST>
	void travIn_I2(VST& visit) {
		Stack<Ptr> s;
		auto x = this;
		while (true) {
			// 辅助函数的功能，走到最左边
			if (x) {
				s.push(x);
				x = x->lChild_;
			}
			// 访问数据，并进入当前节点的右支
			else if (!s.empty()) {
				x = s.pop();
				visit(x->data_);
				x = x->rChild_;
			}
			else {
				break;
			}
		}
	}

	// 迭代实现中序遍历 v3
	template<typename VST>
	void travIn_I3(VST& visit) {
		// 前一步是否刚从右子树回溯
		bool backtrack = false;
		auto x = this;
		while (true) {
			// 若有左子树 且 不是刚刚回溯
			// 则深入遍历左子树
			if (!backtrack && x->lChild_) {
				x = x->lChild_;
			}
			//  若无左子树或刚刚回溯
			//  存在右子树则进入右子树，
			//  不存在则 调用succ找到直接后继(回溯)
			//   回溯即左访问完，开始访问右边
			else {
				visit(x->data_);
				// 若右子树非空,进入右子树继续遍历
				if (x->rChild_) {
					x = x->rChild_;
					backtrack = false;
				}
				else {
					// 回溯
					if (!(x = x->succ())) {
						break;
					}
					backtrack = true;
				}
			}
		}
	}



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