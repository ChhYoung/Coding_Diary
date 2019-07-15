#ifndef _DSA_INCLUDE_UTIL_RAND_H__
#define _DSA_INCLUDE_UTIL_RAND_H__
#include<stdlib.h>
#include<time.h>

namespace utils{

// 当前时间戳生成随机种子
static void srand_time(){
    srand(static_cast<unsigned int>(time(nullptr)));
}

// [0,range) 中得随机数
static int dice(int range){
    return rand() % range;
}

// [lo,hi)中得随机数
static int dice(int lo,int hi){
    return lo + rand()%(hi - lo);
}

// ASCII值[32,128)  即可打印字符
static char dice(char range){
    return static_cast<char>(32 + rand()%96);
}
}

#endif // _DSA_INCLUDE_UTIL_RAND_H__