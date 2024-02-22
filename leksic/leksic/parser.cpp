#include "parser.h"

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
		if (currToken == BASE_TYPE) res.addChild(Tree("BASE_TYPE"));
		else res.addChild(Tree("VOID"));
		currToken = analyzer.nextToken();
		if (currToken == NAME)
		{
			Tree FN("NAME");
			res.addChild(FN);
			currToken = analyzer.nextToken();
			if (currToken == LPAREN)
			{
				Tree LPN("LPAREN");
				res.addChild(LPN);
				Tree params = PARAMS();
				res.addChild(params);
				currToken = analyzer.nextToken();
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
		if (paramOthers.getNode() != "")
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
	Token currToken = analyzer.nextToken();
	if (currToken == NAME)
	{
		res.addChild(Tree("NAME"));
		return res;
	}
	throw runtime_error("Error: Failed to parse variable");
}

Tree Parser::PARAMS2()
{
	Token currToken = analyzer.nextToken();
	if (currToken == RPAREN)
	{
		analyzer.decreaseIndex();
		return Tree();
	}
	else if (currToken == COMMA) {
		Tree res("VAR");
		currToken = analyzer.nextToken();
		if (currToken == BASE_TYPE || currToken == CUSTOM_TYPE)
		{
			if (currToken == BASE_TYPE)	res.addChild(Tree("BASE_TYPE"));
			else	res.addChild(Tree("CUSTOM_TYPE"));
			currToken = analyzer.nextToken();

			if (currToken == NAME) res.addChild(Tree("NAME"));
			else throw runtime_error("Expected variable name");
			
			Tree nextVar = PARAMS2();
			if (nextVar.getNode() != "") res.addChild(nextVar);
			return res;
		}
		throw runtime_error("Expected variable type after comma");
	}
	else
	{
		throw runtime_error("Error: Failed to parse variable");
	}
}

Tree Parser::parse()
{
  return HEADER();
}
