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