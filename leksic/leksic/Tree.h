#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Tree
{
public:
  Tree();
  Tree(string st);
  Tree(string st, vector <Tree> children);
  void addChild(Tree other);
  string getNode();
  vector <Tree> getChildren();
private:
  string node;
  vector <Tree> chilren;
};

