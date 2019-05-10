# 数据结构 c++
## 预备知识：

>**g++**:
编译   g++ -std=c++11 -c countOnes.cpp 生成对象文件countOnes.o
链接   g++ -std=c++11 -o countOnes countOnes.o 链接生成可执行文件countOnes
简便操作   g++ -std=c++11 -o countOnes countOnes.cpp
多个文件 g++ -o simple main.cpp simple.cpp

>**gdb**:
首先生成debug文件 g++ countOnes.cpp -o bugging -g
进入gdb调试: gdb bugging
退出gdb调试: quit
运行待调试程序: run
运行shell:   !shell ls

常见命令
| 命令|简写|说明|
| :-------- | --------:| :--: |
| list  | l |  查看源码  |
| next     |   n |  执行下一行，不进入函数  |
| step      |    s | 一次执行以后，遇到函数进入  |
| finish  |  |  运行到函数结束  |
| continue  | c |  继续运行  |
| delete  | d |  删除断点  |
>**makefile**:
>基本结构
>终极目标：依赖A  依赖B 依赖C
    终极目标命令
依赖A：子依赖A1 子依赖A2 
    依赖A命令
依赖B：子依赖B1 子依赖B2 
    依赖B命令
依赖C：子依赖C1 子依赖C2 
    依赖C命令

包含如下模块：
规则，注释，指示符，内嵌函数，变量定义

**变量定义**: 

```makefile
#变量定义
objects = program.o foo.o utils.o

program: $(objects)  #依赖中引用变量
    gcc -o program $(objects) #命令中引用变量

$(objects): defs.h    #在目标中引用
```

特殊变量：
> \$@ 代表规则中的目标文件名
> \$<  代表规则的第一个依赖的文件名
> $^  规则中所有依赖的文件列表，文件名用空格分割 

/预备知识/complicated/auto_vat.mk的执行结果

echo "\$@ = all"

\$@ = all

echo "\$< = first"

\$< = first

echo "\$^ = first second third"

$^ = first second third

**CMakeLists.txt**:的写法[详情见](https://blog.csdn.net/wfei101/article/details/77150234)：
```makefile
#lept json中的CMakeLists.txt

#cmake的版本要求，最低2.6
cmake_minimum_required (VERSION 2.6)
#定义工程名
project (leptjson_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    #指定编译类
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()
#生成静态链接库leptjson
add_library(leptjson leptjson.c)
#指定生成的执行文件名
add_executable(leptjson_test test.c)
#指定执行文件所依赖的静态库
target_link_libraries(leptjson_test leptjson)
```

**正则表达式**
元字符 `\b`,`\w`,`.`,`*`
`0\d{2}-\d{8}`

**辗转相除法：** 求出两个数的最大公约数

两个正整数a,b   它们的最大公约数为 a 除以b的余数c 和 b之间的最大公约数

> 10 和 25 ， 25 除以 10 余 5 ，10于25的最大公约数为   5与10的最大公约数

a与b，a%b=c ， b与c，b%c = d，c与d  ......

- 问题：a b 都较大时 a%b 运算性能低

- 改进：

**更相减损术:**

两个正整数a,b,   最大公约数a-b的差值c 与 较小的数b的最大公约数

> 10与25 ，  25-10=15   10与15 ，15-10=5  5与10， 得5

- 问题：大小相差太大时次数多，不稳定

- 改进为避免大整数取模，减少运算次数

**移位 + 更相减损术：**

gcb(a,b)​表示ab最大公约数

 - a ，b 都是偶数 ， gcb(a,b) = 2\*gcb(a/2,b/2) = 2\*gcb(a>>1,b>>1) ​
 - a 为偶数， b 为奇数 ， gcb(a,b) = gcb(a/2,b) = gcb(a>>1,b) 
 - a 为奇数， b 为偶数 ， gcb(a,b) = gcb(a,b/2) = gcb(a,b>>1) 
 - a,     b都是奇数 ，  gcb(a,b) = gcb(a,a-b), 利用一次更相减损术，此时a-b为偶数

例:

> 25 & 10   -->25 & 5  --> 25 & 20  --> 25 & 10 --> 25 & 5 --> 25--> 20  wrong

>25 & 10 --> 5 & 25 --> 5 & 20 --> 5 & 10 -->5 & 5 --> 5 & 0  ------>5 











## 第一章绪论：

> **1.1 统计十进制数n的二进制展开中1的个数，时间复杂度分别如下**
> (1)：O(logn)
> (2)：O(countOnes(n)) 与其中1的个数成正比
> (3) : O(logw),w=O(logn)，w为整数的位宽
```cpp
// O(logn)
// 直接移位再与1相与
int countOnes_1(unsigned int n){
    int ones = 0;
    while(n > 0){
        ones += (n & 1);
        n>>=1;
    }
    return ones;
}

// O(countOnes(n))
// 有countOnes(n)个1，则逐个检查这些1，利用二进制的特点
//     n 与 n-1 相于则消去了最后面的1，总共执行countOnes(n)次
int countOnes_2(unsigned int n){
    int ones = 0;
    while(n > 0){
        ones ++ ;
        n &= n-1;
    }
    return ones;
}

//O(log2w),w=O(log2n)
// 将1相加，得到多少就有多少个1，
//相加时采用分组相加，先2个一组，再4个一组，再8，16,32个一组，即每组相加的结果保存在该组中

#define POW(c) (1 << (c))  // 2^c
//生成分组相加用的掩码
#define MASK(c) (((unsigned long)-1) / (POW(POW(c)) + 1))
//移位相加
#define ROUND(n,c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))

int countOnes_3(unsigned int n){
    n = ROUND(n,0);
    n = ROUND(n,1);
    n = ROUND(n,2);
    n = ROUND(n,3);
    n = ROUND(n,4);
    return n;
}
```

> **1.2 用O(1)的辅助空间，将数组A[0,n)中的元素左移位**
> (1)：暴力版 时间复杂度O(nk)
> (2)：迭代版
> (3)：倒置版 时间复杂度 O(3n)

```cpp
void shift0(int* A, int n,int k){
    while(k--){
        shift(A,n,0,1);
    }
}

void shift2(int* A, int n, int k){
    reverse(A,k);
    reverse(A+k,n-k);
    reverse(A,n); 
}
```