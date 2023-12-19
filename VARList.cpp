#include "VARList.h"

VARList::VARList()
{
	variableList = nullptr;
	varList = new list <TToken*>(); 
}

VARList::VARList(TVariable* variable)
{
	varList = new list <TToken*>();
	variableList = variable;
	AddVar(variable);
}

VARList::~VARList()
{

	//SetOutVariables(variableList);
	for (size_t i = 0; i < varList->size(); i++)
	{
		std::list< TToken*>::iterator element = varList->begin();
		advance(element, i);
		TToken* t;
		t = *element;
		delete t;
	}
	 
	delete varList;
}

int VARList::AddVar(string varName, string value)
{
	TToken* _token = new TToken();
	int count = 1;
	count = varList->size();
	_token->AddVar(varName, value);
	varList->push_back(_token);
	count = varList->size();
	return count - 1;
}


int VARList::AddVar(string varName, double value)
{
	TToken* _token = new TToken();
	int count = 1;
	count = varList->size();
	_token->AddVar(varName, value);
	varList->push_back(_token);
	count = varList->size();
	return count - 1;
}



int VARList::AddVarB(string varName, bool value)
{
	TToken* _token = new TToken();
	int count = 1;
	count = varList->size();
	_token->AddVarB(varName, value);
	varList->push_back(_token);
	count = varList->size();
	return count - 1;
}

int VARList::AddVar(string varName, int value)
{
	TToken* _token = new TToken();
	int count = 1;
	count = varList->size();
	_token->AddVar(varName, value);
	varList->push_back(_token);
	count = varList->size();
	return count - 1;
}

void VARList::SetOutVariables(TVariable* variable)
{
	if (variable == NULL) return ;
	string varName(variable->varName);
	TToken* var = GetVarValue(varName);
	if (var->varTokenType == TTokenType::TString)
	{
		if (var->valueString.size() <= 1000)
		{
			memcpy(variable->varStr, var->valueString.c_str(), var->valueString.size());
			variable->varStr[var->valueString.size()] = '\0';
		}
		else
		{
			memcpy(variable->varStr, var->valueString.c_str(), 1000);
			variable->varStr[1000] = '\0';
		}
		variable->typevar = 2;
	}
	else if (var->varTokenType == TTokenType::TNumeric)
	{
		variable->typevar = 0;
		variable->varNumeric = var->valueNumeric;
	}
	else if (var->varTokenType == TTokenType::TBoolean)
	{
		variable->typevar = 1;
		variable->varBoolean = var->valueBool;
	}
	if (variable->nextRecored != NULL)
		SetOutVariables(variable->nextRecored);
}

int VARList::AddVar(TVariable* variable)
{
	if (variable == NULL) return 0;
	string varName(variable->varName);
	if (variable->typevar == 0)
		AddVar(varName, variable->varNumeric);
	else if (variable->typevar == 1)
		AddVarB(varName, variable->varBoolean);
	else if (variable->typevar == 2)
	{
		string varStr(variable->varStr);
		AddVar(varName, varStr);
	}

	if (variable->nextRecored != NULL)
		AddVar(variable->nextRecored);

	return 0;
}



TToken* VARList::GetVarValue(string varName)
{
	for (size_t i = 0; i < varList->size(); i++)
	{
		std::list< TToken*>::iterator element = varList->begin();
		advance(element, i);
		TToken* t;
		t = *element;
		if (t->GetVarName() == varName)
		{
			return t;
		};
	}
	return nullptr;
}

TTokenType VARList::GetVarType(string varName)
{
	for (size_t i = 0; i < varList->size(); i++)
	{
		std::list< TToken*>::iterator element = varList->begin();
		advance(element, i);
		TToken* t;
		t = *element;
		if (t->GetVarName() == varName)
		{
			return t->GetVarType();
		};
	}
	return TTokenType::TNone;
}

string VARList::GetVarList()
{
	string liststr = "";
	for (size_t i = 0; i < varList->size(); i++)
	{
		std::list< TToken*>::iterator element = varList->begin();
		advance(element, i);
		TToken* t;
		t = *element;
		liststr = liststr + t->GetVariableStr();
	}
	return liststr;
}
