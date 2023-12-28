//#include <iostream> 
//#include <string> 
#include "ParserLib.h"
#include <Windows.h>
#include "VARList.h"
#include "ParserSCR.h"
#include "e.tab.c"

using namespace std;
#include "LeakWatcher.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Code to run when the DLL is loaded into the process
        break;
    case DLL_PROCESS_DETACH:
        // Code to run when the DLL is unloaded from the process
        break;
    case DLL_THREAD_ATTACH:
        // Code to run when a new thread is created in the process
        break;
    case DLL_THREAD_DETACH:
        // Code to run when a thread is about to be terminated
        break;
    }

    return TRUE; // Return value depends on the specific requirements of your DLL
}

//extern "C" __declspec(dllexport) int Add(int a, int b) {
//    return a + b;
//}

bool ParseExp(string str, TToken* result, VARList* varList)
{
    bool ok = true;
    try
    {
        ParserSCR* parserSCR = new ParserSCR();
        parserSCR->SetVarList(varList);
        parserSCR->LexLex(str.c_str(), parserSCR);

        if (parserSCR->error)
            ok = false;
        else
        {
            parserSCR->AddToken(TTokenType::TEnd);
            yyIni(parserSCR);
            if (yyparse() != 0)
                ok = false;
            if (ok)
            {
                if (parserSCR->TreeCalculation())
                    result->CopyValueNumeric(parserSCR->root_token);
                else ok = false;
            }
        }
        result->error_str = parserSCR->error_str;
        delete parserSCR;
        return ok;
    }
    catch (...)
    {
        result->error_str = "syntax error !!";
        return false;
    };
    return false;
}

extern "C" __declspec(dllexport) int ParseExpression(char* input, TVariable *output,
                                                  TVariable * variable) {
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
    try
    { 
        string strexp(input);
        VARList* varList = new VARList(variable); 
        TToken* result = new TToken();
        if (ParseExp(strexp, result, varList))
        {
            
            if (result != NULL)
            {
                if (result->tokenType == TTokenType::TString)
                {
                    if (result->valueString.size() < 1000)
                    {
                        result->valueString.copy(output->varStr, result->valueString.size());
                        output->varStr[result->valueString.size()] = '\0';
                    }
                    else
                    {
                        memcpy(output->varStr, result->valueString.c_str(), 1000);
                        output->varStr[1000] = '\0';
                    }
                    output->typevar = 2;
                }
                else if (result->tokenType == TTokenType::TNumeric)
                {
                    output->typevar = 0;
                    output->varNumeric = result->valueNumeric;
                }
                else if (result->tokenType == TTokenType::TBoolean)
                {
                    output->typevar = 1;
                    output->varBoolean = result->valueBool;
                }
            };
            output->error = 0;
            string str = "\n";
            memcpy(output->errorStr, str.c_str(), str.size());
            output->errorStr[str.size()] = '\0';
        }
        else
        {
            output->error = 1; 
            memcpy(output->errorStr, result->error_str.c_str(), result->error_str.size());
            output->errorStr[result->error_str.size()] = '\0';
        };
        varList->SetOutVariables(variable);
        delete result;
        delete varList;
    }
    catch (...)
    {
        output->error = 1;
        string str = "Error\n";
        memcpy(output->errorStr, str.c_str(), str.size());
        output->errorStr[str.size()] = '\0';
        return 1;
    }; 
    _CrtDumpMemoryLeaks();
    return 0;
}
