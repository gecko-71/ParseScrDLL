#pragma once
#include <iostream> 
//using namespace std;
#include "TToken.h"  
//#include <list> 
#include "VARList.h"
 
class ParserSCR
{
public:
    bool error = false;
    TToken* root_token = nullptr;
    string error_str = "";
    list <TToken*> *tokenList = nullptr;
    VARList *varList = nullptr;
    size_t index = -1;
    ParserSCR(); 
    ~ParserSCR();
    int AddToken(TTokenType _tokenType, string value);
    int AddToken(TTokenType _tokenType, double value);
    int AddTokenB(TTokenType _tokenType, bool value);
    int AddToken(TTokenType _tokenType);
    int AddVar(string varName, string value);
    int AddVar(string varName, double value);
    int AddVar(string varName, bool value);
    TToken* GetVarValue(string varName);
    TTokenType GetVarType(string varName);
    string GetTokenList();
    void SetError(char* text);
    void LexLex(const char* extext, ParserSCR* mparserSCR);
    bool TreeCalculation();
    bool TreeCalculationRe(TToken* mroot_token);
    void SetVarList(VARList* mvarList);
};

//namespace {
// extern  
//ParserSCR* parserSCR ;
// }

 

