 

#ifndef PARSERLIB_H
#define PARSERLIB_H

#include <string>
#include "record.h"

//extern "C" __declspec(dllexport) int Add(int a, int b);
 


extern "C" __declspec(dllexport) int ParseExpression(char* input, TVariable *output, TVariable *variable);
 
 
//extern "C" __declspec(dllexport) void  GetString(wchar_t* buffer, int bufferSize);

//extern "C" __declspec(dllexport) void __stdcall ConvertToStdString(const wchar_t* input, std::string & output);
 
 


#endif  

