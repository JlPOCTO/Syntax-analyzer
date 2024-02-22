#pragma once
#include <iostream>
#include "parser.h"
#include "tree.h"

void printTree(Tree x, int tabs);
void test(string st);

//Test with typedef struct
//"int main(int var1, char var2, customStruct var3)"
void test1();

//Test with struct
//"int smth(int var, double var2, struct custom var3)"
void test2();

//Test with wrong typedef struct
//"void main(char var, float var2, 0badcustom var3)"
void test3();

//Test with typedef struct return type (not supported in C)
//"custom notsupported()"
void test4();

//Test with no arguments in function
//"char noargs()"
void test5();

//Test without return type
//"notype(double var2, custom var3)"
void test6();

//Test without variant type
//"void noVarType(var2, custom var3)"
void test7();

//Test with custom typedef struct
//"vOid badType(char var, float var2, custom var3)"
void test8();

//Test with reserves struct name
//"void reservedStructType(struct int var)"
void test9();