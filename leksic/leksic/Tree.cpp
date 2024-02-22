#include "Tree.h"

Tree::Tree(string st)
{
  this->node = st;
}

Tree::Tree(string st, vector <Tree> children)
{
  this->node = st;
  this->chilren = children;
}

Tree::Tree()
{

}

void Tree::addChild(Tree other)
{
  this->chilren.push_back(other);
}

string Tree::getNode()
{
  return node;
}

vector <Tree> Tree::getChildren()
{
  return chilren;
}
