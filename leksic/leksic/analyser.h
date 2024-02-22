#pragma once

#include <regex>
#include <stdexcept>
#include <string>
#include <set>
#include "token.h"

using std::string;
using std::set;
using std::runtime_error;

class Analyser
{
public:
  Token nextToken();
  void setToken(Token other);
  void decreaseIndex();
  Analyser(string st) : _input(st), _index(0) {}
  Analyser() : _input(""), _index(0) {}

private:
  string _input;
  size_t _index;
  Token currToken = HEADER;
  bool isPrevType = false;
  bool isDefault = false;

  set<string> reservedWords = { 
    "auto",       "double",     "int",        "struct",
    "break",      "else",       "long",       "switch",
    "case",       "enum",       "register",   "typedef",
    "char",       "extern",     "return",     "union",
    "const",      "float",      "short",      "unsigned",
    "continue",   "for",        "signed",     "void",
    "default",    "goto",       "sizeof",     "volatile",
    "do",         "if",         "static",     "while"
  };

  void skipBlank();
  bool isAllowedName(string st);
  bool isFirstLetter();
  bool isNameLetter();
};

