#include "ParserSCR.h"
#include "lex.yy.c"
//ParserSCR* parserSCR;
ParserSCR::ParserSCR()
{
	tokenList = new list <TToken*>(); 
}

ParserSCR::~ParserSCR()
{
	for (size_t i = 0; i < tokenList->size(); i++)
	{
		std::list< TToken*>::iterator element = tokenList->begin(); 
		advance(element, i);
		TToken* t;
		t = *element; 
		delete t;
	}
	delete tokenList; 
}

int ParserSCR::AddToken(TTokenType _tokenType, string value)
{
	TToken* _token = new TToken();
	_token->AddToken(_tokenType, value, nullptr, nullptr);
	tokenList->push_back(_token);
	int count = tokenList->size();
	return count - 1;
}

int ParserSCR::AddTokenB(TTokenType _tokenType, bool value)
{
	TToken* _token = new TToken();
	int count = 1;
	count = tokenList->size();
	_token->AddTokenB(_tokenType, value, nullptr, nullptr);
	tokenList->push_back(_token);
	count = tokenList->size();
	return count - 1;
}

int ParserSCR::AddVar(string varName, string value)
{
	if (varList == nullptr)
		return -1;
	return varList->AddVar(varName, value); 
}

int ParserSCR::AddVar(string varName, double value)
{
	if (varList == nullptr)
		return -1;
	return varList->AddVar(varName, value);
}

 

int ParserSCR::AddVar(string varName, bool value)
{
	if (varList == nullptr)
		return -1;
	return varList->AddVar(varName, value);
}

TToken* ParserSCR::GetVarValue(string varName)
{
	if (varList == nullptr)
		return nullptr;
	return varList->GetVarValue(varName);  
}

TTokenType ParserSCR::GetVarType(string varName)
{
	if (varList == nullptr)
		return TTokenType::TNone;
	return varList->GetVarType(varName);
}

int ParserSCR::AddToken(TTokenType _tokenType, double value)
{ 
	TToken *_token = new TToken();
	int count = 1;
    count = tokenList->size();
	_token->AddToken(_tokenType, value, nullptr, nullptr);
	tokenList->push_back(_token); 
    count = tokenList->size();
	return count -1;
}

int ParserSCR::AddToken(TTokenType _tokenType)
{
	TToken* _token = new TToken();
	_token->AddToken(_tokenType, nullptr, nullptr);
	tokenList->push_back(_token);
	int count = tokenList->size();
	return count - 1;
}

string ParserSCR::GetTokenList()
{
	string liststr = "";
	for (size_t i = 0; i < tokenList->size(); i++)
	{
		std::list< TToken*>::iterator element = tokenList->begin();
		// Advance the iterator by 2 positions,
		advance(element, i);
		TToken  *t;
		t =  *element;
		liststr = liststr + t->GetTokenStr();
	}
	return liststr;
}

void ParserSCR::SetError(char* text)
{
	error = true;
	string tmp = text;
	error_str = "Syntax error: " + tmp + '\0';
}

void ParserSCR::LexLex(const char* extext, ParserSCR* mparserSCR)
{
	int token;
	yy_first_ever_run = 1;
	setLexerBuffer(extext, mparserSCR);
	//setLexerBuffer("3+3");
	do
	{
		token = yylex();
		if (token == -10)
			break;
	} while (token != 0);
	yylex_destroy();
	 
}

bool ParserSCR::TreeCalculation()
{
	if (error)
		return false;
	try {
		if (root_token == nullptr)
		{
			error = true;
			error_str = "Expression is null";
			return false;
		}
		if (TreeCalculationRe(root_token) == false)
		{
			error = true;
			error_str = "syntax error";
			return false;
		} 
		else {
			error = false;
			error_str = "";
			return true;
		}
	}
	catch (...)
	{
		return false;
	};
	return false;
}

 

bool ParserSCR::TreeCalculationRe(TToken* mroot_token)
{
	if (mroot_token == nullptr) 
		return true; 
	switch (mroot_token->tokenType)
	{
	  case TTokenType::TNumeric : {
		  return true;
	  };
	  case TTokenType::TBoolean: {
		  return true;
	  };
	  case TTokenType::TString: {
		  return true;
	  };
      case TTokenType::TVar: { 
		  if (varList == nullptr)
			  return false;
		  TToken* var = varList->GetVarValue(mroot_token->GetVarName());
		  if (var == nullptr)
			  return false; 
		  mroot_token->CopyVarValue(var);
		  return true;
	  };
  	  case TTokenType::TPlus: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric))
			  {
				  mroot_token->SetValue(mroot_token->left->GetValueNumeric() + mroot_token->right->GetValueNumeric());
				  return true;
			  }
			  else if ((mroot_token->right->tokenType == TTokenType::TString) &&
				  (mroot_token->left->tokenType == TTokenType::TString))
			  {
				  mroot_token->SetValue(mroot_token->left->GetValueStr () + mroot_token->right->GetValueStr());
				  return true;
			  }
			  else
			  {
				  return false;
			  };
		  }
		  else
		  {
			  return false;
		  }
	  };
	  case TTokenType::TMinus: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->left->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->right->tokenType == TTokenType::TNumeric))
			  {
				  mroot_token->SetValue(mroot_token->left->GetValueNumeric() - mroot_token->right->GetValueNumeric());
				  return true;
			  }
			  else
			  {
				  return false;
			  };
		  }
		  else
		  {
			  if ((mroot_token->left == nullptr) && (mroot_token->right != nullptr))
			  {
				  if (TreeCalculationRe(mroot_token->right) == false)
					  return false;
				  mroot_token->SetValue(mroot_token->right->GetValueNumeric() * -1);
				  return true;
			  }
			  else
			  {
				  return false;
			  }
		  }
	  };
	  case TTokenType::TMultiplying: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric))
			  {
				  mroot_token->SetValue(mroot_token->left->GetValueNumeric() * mroot_token->right->GetValueNumeric());
				  return true;
			  }
			  else
			  {
				  return false;
			  };
		  }
		  else
		  {
			  return false;
		  }
	  };
	  case TTokenType::TDividing: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric))
			  {
				  if (mroot_token->right->GetValueNumeric() == 0)
					  return false;
				  mroot_token->SetValue(mroot_token->left->GetValueNumeric() / mroot_token->right->GetValueNumeric());
				  return true;
			  }
			  else { return false; };
		  }
		  else {  return false; }
	  };
	  case TTokenType::TBracketOpen: {
		  if (mroot_token->left->left == nullptr)
				  return false;
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  mroot_token->CopyValueNumeric(mroot_token->left);
			  return true;
		  };
	  case TTokenType::TAND: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if ((mroot_token->left->GetValueBool() == false) ||
					  (mroot_token->right->GetValueBool() == false))
					  mroot_token->SetValue(false);
				  else if ((mroot_token->left->GetValueBool() == true) &&
					  (mroot_token->right->GetValueBool() == true))
					  mroot_token->SetValue(true);
				  else mroot_token->SetValue(false);
				  return true;
			  }
			  else { return false; };
		  };
	  };
	  case TTokenType::TOR: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;
			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if ((mroot_token->left->GetValueBool() == true) ||
					  (mroot_token->right->GetValueBool() == true))
					  mroot_token->SetValue(true);
				  else mroot_token->SetValue(false);
				  return true;
			  }
			  else { return false; };
		  }
		  else { return false; }
	  };
	  case TTokenType::TEqualTo: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;
			  if (
				  ((mroot_token->right->tokenType == TTokenType::TBoolean) ||
					  (mroot_token->right->tokenType == TTokenType::TString) ||
					  (mroot_token->right->tokenType == TTokenType::TNumeric)) &&
				  (mroot_token->left->tokenType == TTokenType::TVar))
			  {
				  if (varList == nullptr)
					  return false;
				  TToken* var = varList->GetVarValue(mroot_token->left->GetVarName());
				  if (var == nullptr)
					  return false;
				  var->CopyValueToVar(mroot_token->right);
				  mroot_token->left->CopyValueToVar(mroot_token->right);
				  if (var == nullptr)
					  return false;
				  mroot_token->CopyVarValue(mroot_token->left);
				  return true;
			  }
			  else return false;
		  }
		  else { return false; }
	  };
	  case TTokenType::TEqual: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if (mroot_token->left->GetValueBool() == mroot_token->right->GetValueBool())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else if ((mroot_token->right->tokenType == TTokenType::TString) &&
				  (mroot_token->left->tokenType == TTokenType::TString)) {
				  if (mroot_token->left->GetValueStr() == mroot_token->right->GetValueStr())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric)) {
				  if (mroot_token->left->GetValueNumeric() == mroot_token->right->GetValueNumeric())
				    mroot_token->SetValueB(true);
				  else 
					mroot_token->SetValueB(false); 
				  return true;
			  }
			  else { return false; };
		  };
	  }; /* = */
      case TTokenType::TLEQ: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if (mroot_token->left->GetValueBool() <= mroot_token->right->GetValueBool())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric)) {
				  if (mroot_token->left->GetValueNumeric() <= mroot_token->right->GetValueNumeric())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else { return false; };
		  };
	  };/* <= */
      case TTokenType::TGEQ: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if (mroot_token->left->GetValueBool() >= mroot_token->right->GetValueBool())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric)) {
				  if (mroot_token->left->GetValueNumeric() >= mroot_token->right->GetValueNumeric())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else { return false; };
		  };
	  };/* >= */
      case TTokenType::TNEQ: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if (mroot_token->left->GetValueBool() != mroot_token->right->GetValueBool())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else if ((mroot_token->right->tokenType != TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric)) {
				  if (mroot_token->left->GetValueNumeric() >= mroot_token->right->GetValueNumeric())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else { return false; };
		  };
	  };/* <> */
	  case TTokenType::TLQ: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if (mroot_token->left->GetValueBool() < mroot_token->right->GetValueBool())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  } 
			  else if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric)) {
				  if (mroot_token->left->GetValueNumeric() < mroot_token->right->GetValueNumeric())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else { return false; };
		  };
	  };/* < */
	  case TTokenType::TGQ: {
		  if ((mroot_token->left != nullptr) && (mroot_token->right != nullptr))
		  {
			  if (TreeCalculationRe(mroot_token->left) == false)
				  return false;
			  if (TreeCalculationRe(mroot_token->right) == false)
				  return false;

			  if ((mroot_token->right->tokenType == TTokenType::TBoolean) &&
				  (mroot_token->left->tokenType == TTokenType::TBoolean))
			  {
				  if (mroot_token->left->GetValueBool() > mroot_token->right->GetValueBool())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else if ((mroot_token->right->tokenType == TTokenType::TNumeric) &&
				  (mroot_token->left->tokenType == TTokenType::TNumeric)) {
				  if (mroot_token->left->GetValueNumeric() > mroot_token->right->GetValueNumeric())
					  mroot_token->SetValueB(true);
				  else
					  mroot_token->SetValueB(false);
				  return true;
			  }
			  else { return false; };
		  }; 
	  };/* > */
	  default: {
	 
		  return false;
	  }
	}

	return false;
}

void ParserSCR::SetVarList(VARList* mvarList)
{
	varList = mvarList;
}


