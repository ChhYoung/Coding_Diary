#ifndef STACK_ALLOC_H__
#define STACK_ALLOC_H__

#include<memory> 

template<typename T>
// 用链式结构来实现栈
struct StackNode_{
    // 数据
    T data;
    // 指向前一个节点
    StackNode_* prev;
};

template <typename T, typename Alloc = std::allocator<T>>
class StackAlloc{
public: 
    typedef StackNode_<T> Node;
    // 得到 std::allocator<StackNode_<T>>
    // typedef typename std::allocator<T>::template rebind<Node>::other allocator;
    // 该作用为 对一个给定类型T1的分配器，想根据相同策略得到类型T2的分配器
    // 用 typename 来指明 other是一个类型
    typedef typename Alloc::template rebind<Node>::other allocator;

    StackAlloc(){head_ = 0;}
    ~StackAlloc(){ clear();}

    // 当栈中元素为空时返回 true
    bool empty(){return (head_ == 0);}
    // 释放栈中元素的所有内存
    void clear(){
        Node* curr = head_;
        // 依次出栈
        while(curr != 0){
            Node* tmp = curr->prev;
            // 先析构再回收内存
            allocator_.destroy(curr);
            allocator_.deallocate(curr,1);
            curr = tmp;
        }
        head_ = 0;
    }
    // 压栈
    void push(T element){
        // 为一个节点分配内存
        Node* newNode = allocator_.allocate(1);
        // 调节节点构造函数
        allocator_.construct(newNode,Node());
        // 入栈
        newNode->data = element;
        newNode->prev = head_;
        head_ = newNode;
    }
    // 出栈
    T pop(){
        T result = head_->data;
        Node* tmp = head_->prev;
        allocator_.destroy(head_);
        allocator_.deallocate(head_,1);
        head_ = tmp;
        return result;
    }
    // 返回栈顶元素
    T top(){
        return head_->data;
    }
private:
    allocator allocator_;
    // 栈顶
    Node* head_;
};

#endif // STACK_ALLOC_H__














