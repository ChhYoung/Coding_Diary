# 二叉树

[TOC]

## 1  基本概念

### 1.1 常见名词:

- 祖先\后代:包括节点本身， 真祖先\ 真后代:不包括节点本身

- 度数\度 degree  ： 节点孩子的总数,

- K-ary tree:  k叉树，每个节点孩子数不超过K

## 2  二叉树的实现

### 2.1 二叉树节点模板类 BinNode 

```c++
// ./DSA/include/src/BinNode.h
#pragma once

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
```



### 2.2 二叉树模板类 BinTree

```c++
// ./DSA/include/src/BinTree.h
#pragma once 

#ifndef _DSA_INCLUDE_SRC_BINTREE_H__
#define _DSA_INCLUDE_SRC_BINTREE_H__
#include"BinNode.h" 
#include"release.h"

#if TEST_BUILD
#include <stdlib.h>  // rand
#endif

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
	// 树的属性， 其他的如树的具体结构等为节点的属性在 BinNode 中
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
	// 父节点指向当前节点的指针
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

	// 删除二叉树中x节点及其后代，返回被删除的节点的个数
	static int removeAt(NodePtr x) {
		if (!x) { return 0; }
		int n = 1 + removeAt(x->lChild_) + removeAt(x->rChild_);
		release(x->data_);
		release(x);
		return n;
	}

	// 删除以位置x处节点为根的只数，返回该子树原先的规模
	int remove(NodePtr x) {
		// 切断来自父节点的引用
		fromParentTo(x) = nullptr;
		// 更新高度
		updateHeightAbove(x->parent_);
		int n = removeAt(x);
		size_ -= n;
		return n;
	}

	// 将子树x从当前树中摘除，并转换为一颗独立的树
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
	//  二叉树的遍历



};// end of BinTree

} // end of namespace

#endif // _DSA_INCLUDE_SRC_BINTREE_H__
```

## 3.二叉树的遍历

- 分为三种 :  **先序遍历，后序遍历，中序遍历**

### 3.1 先序遍历：

先访问根节点，再深入左子树，再深入右子树, 根左右

**递归实现,其中 VST为操作器**

```c++
template<typename VST>
static void visitTravPre(Ptr node, VST& visit) {
	if (!node) { return; }
	visit(node->data_);
	visitTravPre(node->lChild_, visit);
	visitTravPre(node->rChild_, visit);
}
```
**迭代实现**:

**版本1：**观察上述递归实现，从右子树入手可知这是一个[**尾递归**](https://www.zhihu.com/question/20761771)，利用栈的结构，将访问到的根先入栈，[尾递归参考网站](http://www.ruanyifeng.com/blog/2015/04/tail-call.html)

尾递归：递归实例调用发生在算法的最后一步，任何实例都终止在这一递归调用**if (!node) { return; }**，实例出现在最后一步,  尾递归的特点： 操作的最后一步是调用自身的递归，不需要用大量的栈来保存之前的环境，**尾递归只会占用恒量的内存**

```c++
template <typename VST>
void travPre_I1(VST& visit){
	// 构造辅助栈来存储节点
	Stack<Ptr> s;
	// 将根节点压入栈中
	s.push(this);
	// 只要栈非空
	while(!s.empty()){
		// 访问栈顶的元素
		auto x = s.pop();
		visit(x->data_);
		// 由栈后进先出的特点，将左孩子后压入，右孩子先压入
		if(x->rChild_){s.push(x->rChild_);}
		if(x->lChild_){s.push(x->lChild_);}
	}
}
```

**版本2：**由于中后遍历不是尾递归，所以上面的方法不具备普遍性。

先序遍历可以分解成两个过程：

- 沿左走到头
- 自底向上遍历右子树

分解成两个函数

```c++
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
static void travPre_I2(Ptr node, VST& visit){
	// 构造辅助栈
	Stack<Ptr> s;
	auto x = this;
	while(true){
		// 遍历左
		visitAlongLeftBranch(x,visit,s);
		if(s.empty()){ break;}
		// 自底向上进入右
		x = s.pop();
	}
}
```

### 3.2 中序遍历：

先访问左子树，再访问根，再访问右子树，左根右

```c++
template<typename VST>
static void visitTravIn(Ptr node, VST& visit) {
	if (!node) { return; }
	visitTravPre(node->lChild_, visit);
	visit(node->data_);
	visitTravPre(node->rChild_, visit);
}
```
**版本一 ：迭代实现中序遍历 v1:**

对于中序遍历的左树，其递归的实例调用发生在根节点，右树还未遍历,右树的递归遍历为尾递归，调用递归实例`return`

中序遍历左子树的遍历过程可以表示为 ： 遍历到最左侧节点，自底向上按中序遍历其右支。

$$
L_d 为最左侧节点，T_d 为其左枝，
inorder(T) = visit(L_d) + inorder(T_d);
				visit(L_{d-1}) + inorder(T_{d-1});
							......
							visit(L_{0}) + inorder(T_{0});
$$

再利用栈的特点存入要访问的节点

```c++
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
```

- 在中序遍历的中 没有直接前驱(后继)的节点称为首(末)节点
- 对于二叉搜索树，找到一个节点的直接后继非常重要

相关的算法为:

> - 若节点有右孩子，则直接后继必在该节点的右子树中（书上图 5.17的dfe    fg
> - 若无有孩子，则直接后继将当前节点包含于其左子树的最低的祖先

实现

```c++
Ptr succ(){
    // 记录后继的临时变量
    Ptr s = this;
    // 存在右孩子
    if(rChild_){
        s = rChild_;
        while(s->lChild_){
            s = s->lChild_;
        }
    }
    // 否则，找到 将当前节点包含在左子树的最低祖先
    else {
        while(s->isRChild){
            s = s->parent;
        }
        s = s->parent;
    }
    return s;
}
```

**版本二：消去辅助函数版的中序遍历实现**

```c++
template<typename VST>
void travIn_I2(VST& visit){
	Stack<Ptr> s;
	auto x = this;
	while(true){
		// 辅助函数的功能，走到最左边
		if(x){
			s.push(x);
			x = x->lChild_;
		}
		else if(!s.empty()){		
			// 访问最左节点
			x = x.pop();
			visit(x->data_);
			// 进入右支
			x = x->rChild_;
		}
		else{
			break;
		}
	}
}
```

**版本三：不使用栈**: 使用 succ 来寻找直接后继

使用栈会带来额外空间开销，最差时中总节点数相当

对版本二进行改进，反复利用其`parent_`指针, 使空间复杂度将为`O(1)`，但由于反复调用`succ`时间复杂度有所增加

- 增加一个标志位来判断是否刚做过一次自下向上的回溯(部分遍历完后，利用`succ`找到直接后继)
- 若不是则按照 中序遍历的规则来访问其左子树
- 若是则访问其右子树

```c++
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
			// 若无左树  或者  刚刚回溯过
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
```

**版本四：不使用辅助栈 和 标志位**

- 不断利用succ来跳转到直接后继

```c++
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
```




### 3.3  后序遍历：

先访问左子树，再访问右子树，再访问根，  左右根

```c++
template <typename VST>
static void visitTravPost(Ptr node, VST& visit) {
	if (!node) { return; }
	visitTravPost(node->lChild_, visit);
	visitTravPost(node->rChild_, visit);
	visit(node->data_);
}
```

**后序遍历的特点**

- 将二叉树放置在平面上，设所有节点都不透明，入口为最左端的可见节点**v**    (最高左侧的可见节点) 
- 找到根到该节点的唯一通路为主通路
- 从**v**开始沿主通路自底向上 ，按左右根的顺序访问

**具体实现**

```c++
template <typename VST>
void travPost_I(VST& visit){
	// go to the highest leaf visiable from left 
	static auto goToHLVFL = [](Stack<Ptr>& stack){
		while(auto node = stack.top()){
		
		}
	}
}
```



