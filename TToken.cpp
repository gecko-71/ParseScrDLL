#include "TToken.h"

void TToken::AddToken(TTokenType _tokenType, string value, TToken* mleft, TToken* mright)
{
	left = mleft;
	right = mright;
	tokenType = _tokenType; 
	valueString = value;
	if (tokenType == TTokenType::TString) {
		valueString.erase(0, 1);
		valueString.erase(valueString.size() - 1);
	} else if (tokenType == TTokenType::TVarOrFun) {
		_name = value;
		valueString = "";
	}
	valueNumeric = 0;
}

void TToken::AddToken(TTokenType _tokenType, double value, TToken* mleft, TToken* mright)
{
	left = mleft;
	right = mright;
	tokenType = _tokenType;
	valueNumeric = value;
	valueString = to_string(value); 
}

void TToken::AddTokenB(TTokenType _tokenType, bool value, TToken* mleft, TToken* mright) 
{
	left = mleft;
	right = mright;
	tokenType = _tokenType;
	valueBool = value; 
	valueNumeric = value;
	valueString = to_string(value);
}
void TToken::AddToken(TTokenType _tokenType, TToken* mleft, TToken* mright)
{
	left = mleft;
	right = mright;
	tokenType = _tokenType; 
}

double TToken::GetValueNumeric()
{
	return valueNumeric;
}

string TToken::GetValueStr()
{
	return valueString;
}

bool TToken::GetValueBool()
{
	return valueBool;
}

void TToken::AddVar(string varName, double value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TVar;
	_name = varName;
	varTokenType = TTokenType::TNumeric;
	valueNumeric = value;
	valueString = to_string(value);
}

void TToken::AddVar(string varName, int value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TVar;
	_name = varName;
	varTokenType = TTokenType::TNumeric;
	valueNumeric = value;
	valueString = to_string(value);
}

void TToken::AddVar(string varName, string value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TVar;
	_name = varName;
	varTokenType = TTokenType::TString;
	valueNumeric = NULL;
	valueString = value;
}

 

void TToken::AddVarB(string varName, bool value)
{
	left = nullptr;
	right = nullptr;
	varTokenType = TTokenType::TBoolean;
	_name = varName;
	tokenType = TTokenType::TVar; 
	valueNumeric = value;
	valueString = to_string(value);
	valueBool = value;
}

void TToken::SetVar(double value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TVar;
	varTokenType = TTokenType::TNumeric;
	valueNumeric = value;
	valueString = to_string(value);
	if (value == 0)
		valueBool = false;
	else valueBool = true;
}

void TToken::SetVar(string value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TVar;
	varTokenType = TTokenType::TString; 
	valueString = value;  
	valueNumeric = NULL;
}

void TToken::SetVarB(bool value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TVar;
	varTokenType = TTokenType::TNumeric;
	valueNumeric = value;
	valueString = to_string(value); 
	valueBool = value; 
}

TTokenType TToken::GetVarType()
{
	return tokenType;
}

string TToken::GetVarName()
{
	return _name;
}

 

void TToken::SetValue(double value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TNumeric;
	valueNumeric = value;
	valueString = to_string(value);
	if (value == 0)
		valueBool = false;
	else valueBool = true; 
}

void TToken::SetValue(string value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TString;
	valueNumeric = NULL;
	valueString = value; 

}

void TToken::SetValueB(bool value)
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TBoolean;
	valueNumeric = value;
	valueString = to_string(value);
	valueBool = value;
}

string TToken::GetTokenStr()
{
	string str;
	str = TokenTypeToStr() + " " + valueString + "\n";
	return str ;
}

string TToken::TokenTypeToStr()
{
	return TokenTypeToStrParam(tokenType);
}

string TToken::GetVariableStr()
{
	string str;
	str = GetVarName() + " " + TokenTypeToStrParam(varTokenType ) + " := " + valueString + "\n";
	return str;
}

string TToken::GetVarStr()
{
	string str;
	str = TokenTypeToStr() + " " + valueString + "\n";
	return str;
}

string TToken::TokenTypeToStrParam(TTokenType _tokenType)
{ 
		switch (_tokenType)
		{
		case TTokenType::TNumeric:          return "TNumeric";
		case TTokenType::TString:            return "TString";
		case TTokenType::TPlus:              return "TPlus";
		case TTokenType::TVarOrFun:          return "TVarOrFun";
		case TTokenType::TMinus:             return "TMinus";
		case TTokenType::TDividing:          return "TDividing";
		case TTokenType::TMultiplying:       return "TMultiplying";
		case TTokenType::TBracketOpen:       return "TBracketOpen";
		case TTokenType::TBracketClose:      return "TBracketClose";
		case TTokenType::TBracketCurlyOpen:  return "TBracketCurlyOpen:";
		case TTokenType::TBracketCurlyClose: return "TBracketCurlyClose";
		case TTokenType::TEqualTo:           return "TEqualTo";
		case TTokenType::TEqual:             return "TEqual";
		case TTokenType::TComma:             return "TComma";
		case TTokenType::TVar:               return "TVar";
		case TTokenType::TFun:               return "TFun";
		case TTokenType::TLEQ:               return "TLEQ";    /* <= */ 
		case TTokenType::TGEQ:               return "TGEQ";/* >= */
		case TTokenType::TNEQ:               return "TNEQ";/* <> */
		case TTokenType::TAND:               return "TAND";/* AND */
		case TTokenType::TOR:                return "TOR";/* OR */
		case TTokenType::TBoolean:           return "TBoolean";
        case TTokenType::TLQ:                return "TLQ"; /* < */
        case TTokenType::TGQ:                return "TGQ"; /* > */
		case TTokenType::TEnd:               return "TEnd";
		}
		return "<none>";  
}

void TToken::CopyValueNumeric(TToken* cop)
{
	varTokenType = cop->varTokenType;
	tokenType = cop->tokenType;
	valueString = cop->valueString;
	valueNumeric = cop->valueNumeric;
	valueBool = cop->valueBool;
}

TToken::TToken()
{
	left = nullptr;
	right = nullptr;
	tokenType = TTokenType::TNone;
}

TToken::TToken(TTokenType _tokenType, string value, TToken* _left, TToken* _right)
{
	AddToken(_tokenType, value, _left, _right);
}

TToken::TToken(TTokenType _tokenType, double value, TToken* _left, TToken* _right)
{
	AddToken(_tokenType, value, _left, _right);
}

void TToken::SetName(string value)
{
	_name = value;
}

TToken::TToken(TTokenType _tokenType, TToken* _left, TToken* _right)
{
	AddToken(_tokenType,_left, _right);
}

void TToken::CopyVarValue(TToken* cop)
{  
	tokenType = cop->varTokenType;
	valueString = cop->valueString;
	valueNumeric = cop->valueNumeric;
	valueBool = cop->valueBool;
}

void TToken::CopyValueToVar(TToken* cop)
{
	varTokenType = cop->tokenType;
	valueString = cop->valueString;
	valueNumeric = cop->valueNumeric;
	valueBool = cop->valueBool;
}


TToken* createNode(TTokenType TokenType, string value, TToken* left, TToken* right) {
	return  new TToken(TokenType, value, left, right);
}

TToken* createNode(TTokenType TokenType, TToken* left, TToken* right) {
	return  new TToken(TokenType, left, right);
}

TToken* createNode(TTokenType TokenType, double value, TToken* left, TToken* right) {
	return  new TToken(TokenType, value, left, right);
}
 
