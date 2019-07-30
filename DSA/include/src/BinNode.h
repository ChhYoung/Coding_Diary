// ./DSA/include/src/BinNode.h
//#pragma once
//  GB18030
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
	// 时间复杂度：O(n = |size|)
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
		// 根结点入栈
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
			visitAlongLeftBranch(x, visit, s);
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
	// 使用 succ ,不使用辅助栈，减少额外空间开销，
	// 但增加了时间开销
	// 通过一个 标志位 backtrack 来判断一个节点是否已经回溯(部分遍历完后利用succ找到直接遍历)
	// 
	template<typename VST>
	void travIn_I3(VST& visit) {
		// 初始将回溯标准置否
		bool backtrack = false;
		auto x = this;
		while (true) {
			// 若有左树  且   刚刚没有回溯(避免重复访问)
			// 则 深入遍历左树---> 按照中序遍历的方式到达最左端
			if (!backtrack && x->lChild_) {
				x = x->lChild;
			}
			// 若无左树  或者   刚刚回溯过
			// 则 
			// 若存在右树则进入右树继续遍历
			// 若不存在则找到直接后继，再进入其右树遍历
			else {
				visit(x->data_);
				if (x->rChild_) {
					x = x->rChild_;
					backtrack = false;
				}
				else {
					// 无右子树情况，进行回溯找到后继
					// 退出条件： 最后一个元素的后继为空
					if (!(x = x->succ())) { break; }
					// 重设回溯标志位
					backtrack = true;
				}
			}
		}
	}
	
	// 迭代实现中序遍历 v4
	// 不使用标志位与栈
	// 但要多次调用 succ
	template <typename VST>
	void travIn_I4(VST& visit) {
		auto x = this;
		while (true) {
			// 到达最左端
			if (x->lChild_) {
				x = x->lChild_;
			}
			else {
				visit(x->data_);
				// 若无右支则回溯
				// 若一直无右支则不断的回溯
				// -
				// -------不断在无右支处回溯至直接后继
				while (!x->rChild_) {
					// 退出条件： 最后一个元素的后继为空
					if (!(x = x->succ())) { return; }
					else {
						// 访问直接后继的数据
						visit(x->data_);
					}
				}
				// 若存在右支
				// 则进入非空右支
				x = x->rChild_;
			}
		}
	}

	// 迭代实现后续遍历
	// 利用一个辅助函数： go to highest leaf visible from left
	template<typename VST>
	void travPost_I(VST& visit) {
		// 辅助函数
		// go to highest leaf visible from left
		// 压入栈的节点为主通路上节点的左右节点
		static auto goToHLVFL = [](Stack<Ptr> & stack) {
			// 从根节点开始按照顺序压栈，使得出栈的都是左节点
			while (auto node = stack.top()) {
				// 尽量向左
				if (node->lChild_) {
					if (node->rChild_) { stack.push(node->rChild_); }
					stack.push(node->lChild_);
				}
				// 实在不行则向右
				else {
					stack.push(node->rChild_);
				}
			}
			//弹出栈顶空节点
			stack.pop();
		}
		
		Stack<Ptr> 2s;
		auto x = this;
		s.push(x);
		while (!s.empty()) {
			// 沿主通路访问
			if (s.top() != x->parent_) {
				// goToHLVFL保证定位到每个子树的HLVFL节点，
				// 利用辅助栈存储右节点来实现宏观上凭借每个子树遍历的结果
				goToHLVFL(s);
			}
			x = s.pop();
			visit(x->data_);
		}
	}

	// 层次遍历
	// 利用队列 先进先出
	template <typename VST>
	void travLevel(VST& visit) {
		Queue<Ptr> q;
		q.enqueue(this);
		while (!q.empty()) {
			auto x = q.dequeue();
			visit(x->data_);
			if (x->lChild_) { q.enqueue(x->lChild_);}
			if (x->rChild_) { q.enqueue(x->rChild_); }
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

// 理想平衡
template<typename T>
bool balanced(BinNode<T>* node){
	return stature(node->lChild_) == stature(node->rChild_);
}

// 平衡因子
template<typename T>
int balanceFactor(BinNode<T>* node){
	return stature(node->lChild_) - stature(node->rChild_);
}

// AVL 平衡
template<typename T>
bool avlBalanced(BinNode<T>* node){
	auto factor = balanceFactor(node);
	return (-2 < factor) && (factor < 2);
}

// 在左右孩子中取更高者
// AVL 平衡调整前，借此确定重构方案
template<typename T>
BinNode<T>* tallerChild(BinNode<T>* node){
	return 
		stature(node->lChild_) > stature(node->rChild_) ? node->lChild_ : (
		stature(node->lChild_) < stature(node->rChild_) ? node->rChild_ : (
		node->isLChild() ? node->lChild_ : node->rChild_));
}

}
#endif //  _DSA_INCLUDE_SRC_BINNODE_H__