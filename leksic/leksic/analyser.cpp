#include "analyser.h"

Token Analyser::nextToken()
{
  skipBlank();
  if (_index >= _input.size()) return END;
  if (_input[_index] == ',')
  {
    _index++;
    isPrevType = false;
    return COMMA;
  }
  if (_input[_index] == '(')
  {
    _index++;
    isPrevType = false;
    return LPAREN;
  }
  if (_input[_index] == ')')
  {
    _index++;
    isPrevType = false;
    return RPAREN;
  }
  string st = "";
  while (_index < _input.size() && _input[_index] != ' ' && _input[_index] != '\t' && _input[_index] != '(' &&
    _input[_index] != ')' && _input[_index] != ',')
  {
    st += _input[_index++];
  }
  if (st == "int" || st == "double" || st == "float" || st == "char")
  {
    isPrevType = true;
    return BASE_TYPE;
  }
  if (st == "void")
  {
    isPrevType = true;
    return VOID;
  }
  if (st == "struct")
  {
    isPrevType = true;
    skipBlank();
    st = "";
    while (_index < _input.size() && _input[_index] != ' ' && _input[_index] != '\t')
    {
      st += _input[_index++];
    }
    if (isAllowedName(st)) return CUSTOM_TYPE;
    throw runtime_error("Syntax error: Invalid struct name");
  }
  if (isPrevType && isAllowedName(st))
  {
    isPrevType = false;
    return NAME;
  }
  else if (isAllowedName(st))
  {
    isPrevType = true;
    return CUSTOM_TYPE;
  }
  else
  {
    throw runtime_error("Syntax error: Invalid type or var name");
  }
}

bool Analyser::isAllowedName(string st)
{
  if (reservedWords.count(st) == 1) return false;
  std::regex pattern("[a-zA-Z_][a-zA-Z0-9_]*");
  return std::regex_match(st, pattern);
}

void Analyser::setToken(Token other)
{
  currToken = other;
}

void Analyser::decreaseIndex()
{
  _index--;
}

void Analyser::skipBlank()
{
  while (_index < _input.size() && (_input[_index] == ' ' || _input[_index] == '\t'))
  {
    ++_index;
  }
}

bool Analyser::isFirstLetter()
{
  return _index < _input.size() && (_input[_index] <= 'z' && _input[_index] >= 'a' ||
         _input[_index] <= 'Z' && _input[_index] >= 'A' ||
         _input[_index] == '_');
}

bool Analyser::isNameLetter()
{
  return _index < _input.size() && (_input[_index] <= 'z' && _input[_index] >= 'a' ||
         _input[_index] <= 'Z' && _input[_index] >= 'A' ||
         _input[_index] <= '9' && _input[_index] >= '0' ||
         _input[_index] == '_');
}
