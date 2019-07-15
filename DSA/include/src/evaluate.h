#ifndef _DSA_INCLUDE_SRC_EVALUATE_H__
#define _DSA_INCLUDE_SRC_EVALUATE_H__

#include"stack.h"
#include"vector.h"

// 定义运算符的数量
static constexpr auto MAX_OPRATOR = 9;


// 定义操作符的枚举类型
enum class Operator : int{
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /
    POW, // ^
    FAC, // ! factorial
    L_P, // ( left parenthesis
    R_P, // ) right parenthesis
    EOE, // \0 END OF EXPRESSION
    EOO, // g, sential, end of operator
};

// 定义操作优先级








#endif // _DSA_INCLUDE_SRC_EVALUATE_H__
