#include "tests.h"

using namespace std;

void printTree(Tree x, int tabs)
{
  for (int i = 0; i < tabs; ++i) cout << " ";
  cout << x.getNode() << endl;
  vector <Tree> children = x.getChildren();
  for (int i = 0; i < tabs; ++i) cout << " ";
  cout << "Children: ";
  for (int i = 0; i < children.size(); ++i) cout << children[i].getNode() << " ";
  cout << endl;
  for (int i = 0; i < children.size(); ++i) printTree(children[i], tabs + 2);
}

void test(string st)
{
  cout << "Test string: " + st << endl;
  Parser parser(st);
  try
  {
    Tree res = parser.parse();
    printTree(res, 0);
  }
  catch (runtime_error err)
  {
    cout << err.what() << endl;
  }
  cout << endl << endl;
}

void test1()
{
  string st = "int main(int var1, char var2, customStruct var3)";
  test(st);
}

void test2()
{
  string st = "int smth(int var, double var2, struct custom var3)";
  test(st);
}

void test3()
{
  string st = "void main(char var, float var2, 0badcustom var3)";
  test(st);
}

void test4()
{
  string st = "custom notsupported()";
  test(st);
}

void test5()
{
  string st = "char noargs()";
  test(st);
}

void test6()
{
  string st = "notype(double var2, custom var3)";
  test(st);
}

void test7()
{
  string st = "void noVarType(var2, custom var3)";
  test(st);
}

void test8()
{
  string st = "vOid badType(char var, float var2, custom var3)";
  test(st);
}

void test9()
{
  string st = "void reservedStructType(struct int var)";
  test(st);
}