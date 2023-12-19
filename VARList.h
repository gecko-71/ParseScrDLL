#pragma once
#include "TToken.h"  
#include <list> 
#include "record.h"

class VARList
{
public:
    list <TToken*>* varList = NULL;
    TVariable* variableList;
    VARList();
    VARList(TVariable* variable);
    ~VARList();
    int AddVar(string varName, string value); 
    int AddVar(string varName, double value);
    int AddVarB(string varName, bool value);
    int AddVar(string varName, int value);
    int AddVar(TVariable* variable);
    void SetOutVariables(TVariable* variable);
    TToken* GetVarValue(string varName);
    TTokenType GetVarType(string varName); 
    string GetVarList();
};

