#pragma once

#include "analyser.h"
#include "Tree.h"

class Parser
{
public:
  Parser(string st);
  Tree parse();

private:
  Analyser analyzer;
  Tree HEADER();
  Tree PARAMS();
  Tree PARAM1(Token varType);
  Tree PARAMS2();
  std::pair <Tree, Token> POINTERS();
};

