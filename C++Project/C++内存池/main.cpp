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


#include "MemoryPool.h"
#include <iostream>
#include <vector>
#include <ctime>

const int elems = 1000000;
const int reps = 100;

int main() {
	std::vector<int, std::allocator<int>> v1;
	std::vector<int, MemoryPool<int>> v2;

	clock_t start;
	start = clock();
	for (int i = 0; i < reps; ++i) {
		for (int j = 0; j < elems; ++j) v1.push_back(j);
		for (int j = 0; j < elems; ++j) v1.pop_back();
	}
	std::cout << "default allocator time :";
	std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

	start = clock();
	for (int i = 0; i < reps; ++i) {
		for (int j = 0; j < elems; ++j) v2.push_back(j);
		for (int j = 0; j < elems; ++j) v2.pop_back();
	}
	std::cout << "memory pool allocator time :";
	std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

	return 0;
}
