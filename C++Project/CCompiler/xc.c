#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <string.h>

// memory
int *text;  // text segment
int *old_text; // for dump text segment
int *stack; // stack
char* data; // data segment

// virtual machine registers
int* pc;  // 程序寄存器
int* bp;  // 基址寄存器
int* sp;  // 指针寄存器
int ax;   // 通用寄存器
int cycle;

// instructions 指令集
enum {
	LEA, IMM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
	OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, MOD,
	OPEN, READ, CLOS, PRTF, MALC, MSET, MCMP, EXIT
};



int token;  // current token
char* src, * old_src; // pointer to source code string
int poolsize; // default size of text/data/stack
int line; // line number

// 获取下一个标记 token
void next() { 
	token = *src++;
	return;
}

// 解析下一个1表达式
void expression(int level) {
}

// 语法分析的入口，分析整个C语言程序
void program() {
	next(); // get next token
	while (token > 0) {
		printf("token is: %c\n", token);
		next();
	}
}

// 虚拟机入口，用于解释目标代码
int eval() {
	int op, * tmp;
	while (1) {
		if (op == IMM) { ax = *pc++; }
		else if (op == LC) { ax = *(char*)ax; }
		else if (op == LI) { ax = *(int*)ax; }
		else if (op == SC) { ax = *(char*)*sp++ = ax; }
		else if (op == SI) { *(int*)*sp++ = ax; }
	}

	return 0;
}

int main(int argc, char** argv) {
	int i, fd;
	argc--;
	argv++;

	poolsize = 256 * 1024; // arbitrary size
	line = 1;

	if ((fd = open(*argv, 0)) < 0) {
		printf("could not open(%s)\n", *argv);
		return -1;
	}

	if (!(src = old_src = malloc(poolsize))) {
		printf("could not malloc(%d) for source area\n", poolsize);
		return -1;
	}

	// read the source file
	if ((i = read(fd, src, poolsize - 1)) <= 0) {
		printf("read() returned %d\n", i);
		return -1;
	}
	src[i] = 0; //add EOF character
	close(fd);

	// 初始化，为虚拟机分配内存
	if (!(text = old_text = malloc(poolsize))) {
		printf("could not malloc(%d) for text area\n", poolsize);
		return -1;
	}
	if (!(data = malloc(poolsize))) {
		printf("could not malloc(%d) for stack area\n", poolsize);
		return -1;
	}
	if (!(stack = malloc(poolsize))) {
		printf("could not malloc(%d) for stack area\n", poolsize);
	}
	memset(text, 0, poolsize);
	memset(data, 0, poolsize);
	memset(stack, 0, poolsize);

	// 初始化寄存器
	bp = sp = (int*)((int)stack + poolsize);
	ax = 0;

	program();
	return eval();
}