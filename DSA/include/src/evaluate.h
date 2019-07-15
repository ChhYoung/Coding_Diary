//  对常规形式的表达式求值
#ifndef _DSA_INCLUDE_SRC_EVALUATE_H__
#define _DSA_INCLUDE_SRC_EVALUATE_H__

#include"stack.h"
#include"vector.h"
#include<stdio.h>
#include<ctype.h>
#include<math.h>

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
    EOE, // \0 END OF EXPRESSION， 起始符和终止符
    EOO, // 9 , sentinel, end of operator, 结束标志，哨兵
};

// 字符串转为运算符
static Operator operatorFromChar(char c){
    switch(c){
        case '+' : return Operator::ADD;
        case '-' : return Operator::SUB;
        case '*' : return Operator::MUL;
        case '/' : return Operator::DIV;
        case '^' : return Operator::POW;
        case '!' : return Operator::FAC;
        case '(' : return Operator::L_P;
        case ')' : return Operator::R_P;
        case '\0' : return Operator::EOE;
        default : return Operator::EOO;
    }
}

// 将运算符转化为字符
static char operator2char(Operator op){
    static constexpr auto cc = "+-*/^!()\0";
    if(op < Operator::EOO){
        return cc[(int)op];
    }
    return '$';
}

namespace DSA{

// 打印字符
template<>
static void print(Operator& op){ printf("%c",operator2char(op));}

// 运算符优先级
enum class OperatorPriority : char {
    LESS, // <
    EQUAL, // ==
    GRATER, // >
    EOP,// sentinel， end of priority
};

// 比较两个运算符的优先级
static OperatorPriority compareOperator(Operator op1, Operator op2){
    if(op1 == Operator::EOO || op2 == Operator::EOO){
        return Operator::EOP;
    }
    // 用于对常规形式的表达式求值，
    // 比较顺序为   ’栈顶 ？ 当前运算符‘
    // 当当前运算符优先级更大时，即栈顶运算符优先级低时，将当前运算符压栈
    //          1+2*3-1  当前为*   栈顶为+  
    // 栈顶优先级更大时，计算 
    //          1+2*3-1  当前-，栈顶为*， 计算2*3 结果入栈
    // 优先级相等得情况： 
    //   1.  当前 ), 栈顶 (  :  弹出(
    //   2.   当前为 '\0'
    static constexpr char TABLE[MAX_OPRATOR][MAX_OPRATOR] = {
		/*              |-------------------- 当 前 运 算 符 --------------------| */
		/*              +      -      *      /      ^      !      (      )      \0 */
		/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
		/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
		/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
		/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
		/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
	};

    auto p = TABLE[(int)op1][(int)op2];
    if(p == '<'){
        return OperatorPriority::LESS;
    }
    else if(p == '>'){
        return OperatorPriority::GRATER;
    }
    else if(p == '='){
        return OperatorPriority::EQUAL;
    }
    else {
        return OperatorPriority::EOP;
    }
}

// 比较两个运算符得优先级
static OperatorPriority compareOperator(char op1, char op2){
    return compareOperator(operatorFromChar(op1),operatorFromChar(op2));
}

// ! fact 计算阶乘
static long long factorial(int n){
    long long f = 1;
    while(n>1){
        f *= n--;
    }
    return f;
}

// 将起始于p的子串解析为数值， 并存入操作数栈
static void readNumber(const char*& p, DSA::Stack<float>& S){
    // 转化连续得数字字符 为 数值
    S.push((*p - '0')*1.0F);
    while(isdigit(*++p)){
        S.push(S.pop()*10 + (*p - '0'));
    }
    // 如果是小数
    if('.' != *p) {return ;}
    float faction = 0.1F;
    while( isdigit(*++p)){
        S.push(S.pop() + (*p - '0')*faction);
        faction *= 0.1F;
    }
}

// 二元计算
static float calc(float a,float b,Operator op){
    switch (op){
        case Operator::ADD: return a+b; break;
        case Operator::SUB: return a-b; break;
        case Operator::MUL: return a*b; break;
        case Operator::DIV:
            if(static_cast<int>(b) == 0){
                assert(0);
                return 0;
            }
            return a/b;
            break;
        case Operator::POW：return pow(a,b);break;
        default:
            assert(0);
            return 0;
            break;
    }
}

//  一元计算符
static float calc(float a, Operator op){
    if(op == Operator::FAC) {
        return static_cast<float>(factorial(static_cast<int>(a)));
    }
    assert(0);
    return 0;
}

// 错误处理
static void errorHandler(const char* s){}

//! 显示表达式处理过程
static void displayProgress(const char* expr, const char* pch, dtl::Stack<float>& opnd, dtl::Stack<Operator>& optr, dtl::Vector<char>& rpn, int wait_ms){
	system("cls");
	for (const char* p = expr; '\0' != *p; p++) {
		printf(" %c", *p);
	}printf(" $\n");

	for (const char* p = expr; p < pch; p++) {
		printf("  ");
	}

	if ('\0' != *(pch - 1)) {
		for (const char* p = pch; '\0' != *p; p++) {
			printf(" %c", *p);
		}printf(" $");
	}printf("\n");

	for (const char* p = expr; p < pch; p++) {
		printf("--");
	}printf(" ^\n\n");

	print(opnd);
	print(optr);
	print(rpn);
	
	dtl::wait(wait_ms);
}

/*******************************************************************/
//  转换为RPN 形式的操作
// 将操作数接到RPN末尾
static void append2RPN(DSA::Vector<char>& rpn, float operand){
    char buf[64] = {0};
    if(operand != static_cast<float>(static_cast<int>(operand))){
        sprintf(buf,"%.2f",operand);
    }
    else {
        sprintf(buf,"%d",static_cast<int>(operand));
    }
    for(auto c:buf){
        if(c=='\0') {break;}
        rpn.isnert(c);
    }
}

// 将运算符接到RPN末尾
static void append2RPN(DSA::Vector<char>& rpn,Operator op){
    rpn.insert(' ');
    rpn.insert(operator2char(op));
    rpn.insert(' ');
}


// 对(无空格的)表达式S求值，并转换为 逆波兰式RPN
static bool evaluate(const char* S,DSA::Vector<char>& RPN,float& result, int wait_ms){
    auto expr = 5;
    // 存值
    DSA::Stack<float> operands;
    // 存操作符
    DSA::Stack<Operator> operators;
    // 哨兵
    operators.push(Operator::EOE);
    while(!operators.empty()){
        if(isdigit(*S)){
            readNumber(S,operands);
            append2RPN(RPN,operands.top());
        }
        else{
            auto op = operatorFromChar(*S);
            if(op == Operator::EOO) {errorHandler(S); return false;}

            // 用于对常规形式的表达式求值，
            // 比较顺序为   ’栈顶 ？ 当前运算符‘
            // 当当前运算符优先级更大时，即栈顶运算符优先级低时，将当前运算符压栈
            //          1+2*3-1  当前为*   栈顶为+  
            // 栈顶优先级更大时，计算 
            //          1+2*3-1  当前-，栈顶为*， 计算2*3 结果入栈
            // 优先级相等得情况： 
            //   1.  当前 ), 栈顶 (  :  弹出(
            //   2.   当前为 '\0'
            switch(compareOperator(op.top(), op)){
                case OperatorPriority::LESS:
                    operators.push(op);
                    ++S;
                    break;
                case OperatorPriority::EQUAL:
                    operators.pop();
                    ++S;
                    break;
                case OperatorPriority::GRATER:
                    // 栈顶操作符
                    auto opCur = operators.top();
                    append2RPN(RPN,opCur);
                    // 一元运算符
                    if(opCur == Operator::FAC){
                        auto opnd = operands.pop();
                        operands.push(opnd);
                    }
                    else{
                        auto opnd2 = operands.pop();
                        auto opnd1 = operands.pop();
                        operands.push(calc(opnd1,opnd2,opCur));
                    }
                    break;
                default:
                    assert(0);
                    break;
            }
        }
        displayProgress(expr, S, operands, operators, RPN, wait_ms);
    }
    result = operands.pop();
    return true;
}


} // namespace  DSA







#endif // _DSA_INCLUDE_SRC_EVALUATE_H__
