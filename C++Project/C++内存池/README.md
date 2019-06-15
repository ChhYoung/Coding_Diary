# C++ 实现内存池

[TOC]

## 1.基本描述

当内存不足时管理优化自身已经使用的内存。

- 使用`new delete `时每次申请释放都要系统调用，从堆中分配内存，操作过于频繁则会产生大量的内存碎片
- 每次申请都要经过复杂的系统调用，n次则需要时间为nT
- 可以最初接分配好内存区域，当需要内存时，直接在分配好的内存中使用



## 2. 主函数的设计

设计一个高性能的内存池就要对比已有的内存，而比较已有的内存分配结构，就要一个动态分配结构。**主函数则测试 内存池的动态结构与默认分配器释放相同数量的元素所用的时间 **.

>  其中 `std::allocator`是C++标准库默认的分配器，它的特点是 在new对象时，必然要调用构造函数，它将构造与内存分配两部分分离开来，使得分配的内存是原始的为构造的。

```c++
#include<iostream>
#include<cassert>
#include<ctime>
#include<vector>

#include"MemoryPool.hpp"
#include"StackAlloc.hpp"

// 插入元素个数
#define ELEMS 1000000

// 重复次数
#define REPS 100

int main(){

    clock_t start;
    // 使用默认分配器 std::allocator
    StackAlloc<int,std::allocator<int>> stackDefalut;
    start = clock();
    for(int j = 0;j < REPS;++j){
        assert(stackDefalut.empty());
        for(int i = 0; i < ELEMS; ++i){
            stackDefalut.push(i);
        }
        for(int i = 0; i < ELEMS; ++i){
            stackDefalut.pop();
        }
    }
    std::cout<<"Default Allocator Time: ";
    std::cout<<(((double)clock() - start) / CLOCKS_PER_SEC)<<"\n\n";

    // 使用内存池
    StackAlloc<int, MemoryPool<int>> stackPool;
    start = clock();
    for (int j = 0; j < REPS; j++) {
        assert(stackPool.empty());
        for (int i = 0; i < ELEMS; i++)
          stackPool.push(i);
        for (int i = 0; i < ELEMS; i++)
          stackPool.pop();
    }
    std::cout << "MemoryPool Allocator Time: ";
    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

    
    return 1;
}
```

## 3. 栈的构造



