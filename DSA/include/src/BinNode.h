// ./DSA/include/src/BinNode.h
//#pragma once

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
	// ʱ�临�Ӷȣ�O(n = |size|)
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
	// ����������ҵ�ֱ�Ӻ��
	Ptr succ(){
		// ��¼��̵���ʱ����
		Ptr s = this;
		// �����Һ���,��Ϊ������������ڵ�
		if (rChild_) {
			s = rChild_;
			while (s->lChild_) {
				s = s->lChild_;
			}
		}
		// ����Ϊ����ǰ�ڵ���������������������
		else {
			// ���������Ϸ��ƶ�
			while (s->isRChild) {
				s = s->parent_;
			}
			// ���ƶ�һ������ֱ�Ӻ��
			s = s->parent_;
		}
		return s;
	}


/*********************************************************************************************/
protected:
//  �������ı���
	//  ��������㷨���ݹ�棩�����ݹ麯��
	// VST Ϊ������
	template<typename VST>
	static void visitTravPre(Ptr node, VST& visit) {
		if (!node) { return; }
		visit(node->data_);
		visitTravPre(node->lChild_, visit);
		visitTravPre(node->rChild_, visit);
	}

	// ��������㷨���ݹ�棩�����ݹ麯��
	// VST Ϊ������
	template<typename VST>
	static void visitTravIn(Ptr node, VST& visit) {
		if (!node) { return; }
		visitTravPre(node->lChild_, visit);
		visit(node->data_);
		visitTravPre(node->rChild_, visit);
	}
	// ���������㷨��������
	template <typename VST>
	static void visitTravPost(Ptr node, VST& visit) {
		if (!node) { return; }
		visitTravPost(node->lChild_, visit);
		visitTravPost(node->rChild_, visit);
		visit(node->data_);
	}
	//  �ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�ڵ�,
	//  ��;�ڵ������ͷ���,���������Ľڵ���ҽڵ�ѹ��ջ��

	template<typename VST>
	static void visitAlongLeftBranch(Ptr node, VST& visit, Stack<Ptr>& stack) {
		while (node) {
			visit(node->data_);
			stack.push(node->rChild_);
			node = node->lChild_;
		}
	}


// ����ʵ�ֱ���
public:
	// ������������� v1
	// ͨ����дβ�ݹ�ʵ��
	template<typename VST>
	void travPre_I1(VST& visit) {
		// ���츨��ջ
		Stack<Ptr> s;
		//�������ջ
		s.push(this);
		while (!s.empty()) {
			auto x = s.pop();
			visit(x->data_);
			// ��ջ�����ԣ��Һ�������������ջ
			if (x->rChild_) { s.push(x->rChild_); }
			if (x->lChild_) { s.push(x->lChild_); }
		}
	}
	// ������������� v2
	//  1. ��������
//  �ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�ڵ�,
//  ��;�ڵ������ͷ���,���������Ľڵ���ҽڵ�ѹ��ջ��
	template<typename VST>
	static void visitAlongLeftBranch(Ptr node, VST& visit, Stack<Ptr>& stack) {
		while (node) {
			visit(node->data_);
			stack.push(node->rChild_);
			node = node->lChild_;
		}
	}

	//  2. ���������ʵ��
	template <typename VST>
	static void travPre_I2(Ptr node, VST& visit) {
		// ���츨��ջ
		Stack<Ptr> s;
		auto x = this;
		while (true) {
			// ������
			visitAlongLeftBranch(x, visit, s);
			if (s.empty()) { break; }
			// �Ե����Ͻ�����
			x = s.pop();
		}
	}

	// ����ʵ��������� v1
	template<typename VST>
	void travIn_I1(VST& visit) {
		// �����������ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
		static auto goAloneLetBranch = [](Ptr node, Stack<Ptyr> & stack) {
			while (node) {
				// ����ڵ�ѹ��ջ
				stack.push(node);
				node = node->lChild_;
			}
		}

		Stack<Ptr> s;
		auto x = this;
		while (true) {
			// ��������
			goAloneLetBranch(x, s);
			if (s.empty()) { break; }
			// ������һ������ڵ�
			x = s.pop();
			// ��������
			visit(x->data_);
			// ��������֧
			x = x->rChild_;
		}
	}

	// ����ʵ��������� v2
	// ֻ�ǽ�����������������
	template<typename VST>
	void travIn_I2(VST& visit) {
		Stack<Ptr> s;
		auto x = this;
		while (true) {
			// ���������Ĺ��ܣ��ߵ������
			if (x) {
				s.push(x);
				x = x->lChild_;
			}
			// �������ݣ������뵱ǰ�ڵ����֧
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
	// ����ʵ��������� v3
	// ʹ�� succ ,��ʹ�ø���ջ�����ٶ���ռ俪����
	// ��������ʱ�俪��
	// ͨ��һ�� ��־λ backtrack ���ж�һ���ڵ��Ƿ��Ѿ�����(���ֱ����������succ�ҵ�ֱ�ӱ���)
	// 
	template<typename VST>
	void travIn_I3(VST& visit) {
		// ��ʼ�����ݱ�׼�÷�
		bool backtrack = false;
		auto x = this;
		while (true) {
			// ��������  ��   �ո�û�л���(�����ظ�����)
			// �� �����������---> ������������ķ�ʽ���������
			if (!backtrack && x->lChild_) {
				x = x->lChild;
			}
			// ��������  ����   �ոջ��ݹ�
			// �� 
			// ���������������������������
			// �����������ҵ�ֱ�Ӻ�̣��ٽ�������������
			else {
				visit(x->data_);
				if (x->rChild_) {
					x = x->rChild_;
					backtrack = false;
				}
				else {
					// ����������������л����ҵ����
					// �˳������� ���һ��Ԫ�صĺ��Ϊ��
					if (!(x = x->succ())) { break; }
					// ������ݱ�־λ
					backtrack = true;
				}
			}
		}
	}
	
	// ����ʵ��������� v4
	// ��ʹ�ñ�־λ��ջ
	// ��Ҫ��ε��� succ
	template <typename VST>
	void travIn_I4(VST& visit) {
		auto x = this;
		while (true) {
			// ���������
			if (x->lChild_) {
				x = x->lChild_;
			}
			else {
				visit(x->data_);
				// ������֧�����
				// ��һֱ����֧�򲻶ϵĻ���
				// -
				// -------����������֧��������ֱ�Ӻ��
				while (!x->rChild_) {
					// �˳������� ���һ��Ԫ�صĺ��Ϊ��
					if (!(x = x->succ())) { return; }
					else {
						// ����ֱ�Ӻ�̵�����
						visit(x->data_);
					}
				}
				// ��������֧
				// �����ǿ���֧
				x = x->rChild_;
			}
		}
	}

	// ����ʵ�ֺ�������
	// ����һ������������ go to highest leaf visible from left
	template<typename VST>
	void travPost_I(VST& visit) {
		// ��������
		// go to highest leaf visible from left
		// ѹ��ջ�Ľڵ�Ϊ��ͨ·�Ͻڵ�����ҽڵ�
		static auto goToHLVFL = [](Stack<Ptr> & stack) {
			// �Ӹ��ڵ㿪ʼ����˳��ѹջ��ʹ�ó�ջ�Ķ�����ڵ�
			while (auto node = stack.top()) {
				// ��������
				if (node->lChild_) {
					if (node->rChild_) { stack.push(node->rChild_); }
					stack.push(node->lChild_);
				}
				// ʵ�ڲ���������
				else {
					stack.push(node->rChild_);
				}
			}
			//����ջ���սڵ�
			stack.pop();
		}
		
		Stack<Ptr> 2s;
		auto x = this;
		s.push(x);
		while (!s.empty()) {
			// ����ͨ·����
			if (s.top() != x->parent_) {
				// goToHLVFL��֤��λ��ÿ��������HLVFL�ڵ㣬
				// ���ø���ջ�洢�ҽڵ���ʵ�ֺ����ƾ��ÿ�����������Ľ��
				goToHLVFL(s);
			}
			x = s.pop();
			visit(x->data_);
		}
	}

	// ��α���
	// ���ö��� �Ƚ��ȳ�
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
//  һЩ��������

// �ڵ�߶�
template<typename T>
int stature(BinNode<T>* node) {
	return node ? node->height_ : -1;
}




}
#endif //  _DSA_INCLUDE_SRC_BINNODE_H__