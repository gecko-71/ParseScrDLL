#pragma once
using namespace std;
//#include <iostream> 
#include <string>

enum class TTokenType {
	TNone,
	TNumeric, 
	TPlus,
	TMinus,
	TDividing,
	TMultiplying,
	TString, 
	TBoolean,
	TVarOrFun,
	TVar,
	TFun,
	TBracketOpen,
	TBracketClose,
	TBracketCurlyOpen,
	TBracketCurlyClose,
	TEqualTo, /* := */
	TEqual, /* = */
	TComma,
	TLEQ,    /* <= */ 
	TGEQ,     /* >= */
	TNEQ,  /* <> */
	TAND,  /* AND */
	TOR, /* OR */
	TLQ, /* < */ 
    TGQ, /* > */
	TEnd
};

class TToken
{
public:
	TToken* left  = nullptr;
	TToken* right = nullptr;
	string _name = "";
	TTokenType tokenType = TTokenType::TNone;
	TTokenType  varTokenType = TTokenType::TNone;
	string valueString;
	string error_str = "";
	//bool notFindVar = false;
	double valueNumeric = 0;
	bool valueBool = false;
	void AddToken(TTokenType _tokenType, string value, TToken* mleft, TToken* mright);
	void AddToken(TTokenType _tokenType, double value, TToken* mleft, TToken* mright);
	void AddTokenB(TTokenType _tokenType, bool value, TToken* mleft, TToken* mright);
	void AddToken(TTokenType _tokenType, TToken* mleft, TToken* mright);
	double GetValueNumeric(); 
	string GetValueStr();
	bool GetValueBool();
	void AddVar(string varName, double value);
	void AddVar(string varName, int value);
	void AddVar(string varName, string value); 
	void AddVarB(string varName, bool value);
	void SetVar(double value);
	void SetVar(string value);
	void SetVarB(bool value);
	TTokenType GetVarType();
	string GetVarName();
	void SetValue(double value);
	void SetValue(string value);
	void SetValueB(bool value);
	string GetTokenStr();
	string TokenTypeToStr(); 
	string TokenTypeToStrParam(TTokenType _tokenType);
	string GetVarStr();
	string GetVariableStr();
	void SetName(string value);
	void CopyValueNumeric(TToken* cop);
	void CopyVarValue(TToken* cop);
	void CopyValueToVar(TToken* cop);
	TToken();
	TToken(TTokenType _tokenType, string value, TToken* _left, TToken* _right);
	TToken(TTokenType _tokenType, double value, TToken* _left, TToken* _right);
	TToken(TTokenType _tokenType, TToken* _left, TToken* _right);
};

//namespace {
//	TToken* root = nullptr;
//}

TToken* createNode(TTokenType TokenType, string value, TToken* left, TToken* right);
TToken* createNode(TTokenType TokenType, TToken* left, TToken* right);   
TToken* createNode(TTokenType TokenType, double value, TToken* left, TToken* right);

