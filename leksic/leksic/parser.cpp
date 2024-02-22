#include "parser.h"
#include <iostream>

Parser::Parser(string st)
{
  analyzer = Analyser(st);
}

Tree Parser::HEADER()
{
	Token currToken = analyzer.nextToken();
	Tree res("HEADER");
	if (currToken == BASE_TYPE || currToken == VOID)
	{
		//TYPE
		if (currToken == BASE_TYPE) res.addChild(Tree("BASE_TYPE"));
		else res.addChild(Tree("VOID"));
		std::pair<Tree, Token> pointers = POINTERS();
		res.addChild(pointers.first);
		//NAME
		currToken = pointers.second;
		if (currToken == NAME)
		{
			Tree FN("NAME");
			res.addChild(FN);
			//LPAREN
			currToken = analyzer.nextToken();
			if (currToken == LPAREN)
			{
				Tree LPN("LPAREN");
				res.addChild(LPN);
				//PARAMS
				Tree params = PARAMS();
				res.addChild(params);
				currToken = analyzer.nextToken();
				//RPAREN
				if (currToken == RPAREN)
				{
					Tree RPN("RPAREN");
					res.addChild(RPN);
					currToken = analyzer.nextToken();
					if (currToken == END)
					{
						return res;
					}
					throw runtime_error("Error: Expected end token");
				}
				throw runtime_error("Error: Expected RPAREN token");
			}
			throw runtime_error("Error: Expected LPAREN token");
		}
		throw runtime_error("Error: Expected function name token");
	}
	throw runtime_error("Error: Expected return type token");
}

Tree Parser::PARAMS()
{
	Token currToken = analyzer.nextToken();
	Tree res("PARAMS");
	if (currToken == CUSTOM_TYPE || currToken == BASE_TYPE)
	{
		Tree param1 = PARAM1(currToken);
		res.addChild(param1);
		Tree paramOthers = PARAMS2();
		res.addChild(paramOthers);
		return res;
	}
	else if (currToken == RPAREN)
	{
    analyzer.setToken(PARAM_FIRST);
    analyzer.decreaseIndex();
    return res;
	}
	throw runtime_error("Error: Param or RPAREN expected");
}

Tree Parser::PARAM1(Token varType)
{
	string stT = "";
	if (varType == CUSTOM_TYPE) stT = "CUSTOM_TYPE";
	else stT = "BASE_TYPE";
	Tree res("VAR");
	res.addChild(Tree(stT));
	
  std::pair<Tree, Token> pointers = POINTERS();
  res.addChild(pointers.first);
	Token currToken = pointers.second;
	if (currToken == NAME)
	{
		res.addChild(Tree("NAME"));
		Token nextToken = analyzer.nextToken();
		if (nextToken == EQUALS)
		{
			Tree eq("EQUALS");
			eq.addChild(Tree("="));
			res.addChild(eq);
			nextToken = analyzer.nextToken();
			if (nextToken == DEFAULT_VALUE)
			{
				res.addChild(Tree("DEFAULT_VALUE"));
			}
			else
			{
				runtime_error("Error: Expected default value");
			}
		}
		else
		{
			analyzer.decreaseIndex();
			analyzer.setToken(currToken);
		}
    Tree empty("VAR");
    empty.addChild(Tree());
    res.addChild(empty);
		return res;
	}
	throw runtime_error("Error: Failed to parse variable");
}


std::pair <Tree, Token> Parser::POINTERS()
{
	Tree res("POINTER");
	Token currToken = analyzer.nextToken();
	if (currToken == POINTER)
	{
		res.addChild(Tree("*"));
		std::pair<Tree, Token> nextPointers = POINTERS();
		res.addChild(nextPointers.first);
		return { res, nextPointers.second };
	}
	res.addChild(Tree("Eps"));
	return { res, currToken };
}


Tree Parser::PARAMS2()
{
	Token currToken = analyzer.nextToken();
	if (currToken == RPAREN)
	{
		analyzer.decreaseIndex();
		Tree aps("Eps");
		Tree res("VAR");
		res.addChild(aps);
		return res;
	}
	else if (currToken == COMMA) {
		Tree res("VAR");
		currToken = analyzer.nextToken();
		if (currToken == BASE_TYPE || currToken == CUSTOM_TYPE)
		{
			if (currToken == BASE_TYPE)	res.addChild(Tree("BASE_TYPE"));
			else	res.addChild(Tree("CUSTOM_TYPE"));
      std::pair<Tree, Token> pointers = POINTERS();
      res.addChild(pointers.first);
      Token currToken = pointers.second;

			if (currToken == NAME) res.addChild(Tree("NAME"));
			else throw runtime_error("Expected variable name");
			
      Token nextToken = analyzer.nextToken();
      if (nextToken == EQUALS)
      {
        Tree eq("EQUALS");
        eq.addChild(Tree("="));
        res.addChild(eq);
        nextToken = analyzer.nextToken();
        if (nextToken == DEFAULT_VALUE)
        {
          res.addChild(Tree("DEFAULT_VALUE"));
        }
        else
        {
          runtime_error("Error: Expected default value");
        }
      }
      else
      {
        analyzer.decreaseIndex();
        analyzer.setToken(currToken);
      }

			Tree nextVar = PARAMS2();
			res.addChild(nextVar);
			return res;
		}
		throw runtime_error("Expected variable type after comma");
	}
	else
	{
		throw runtime_error("Error: Failed to parse variable2");
	}
}

Tree Parser::parse()
{
  return HEADER();
}
