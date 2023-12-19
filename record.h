#pragma once
 

struct TVariable {
    int error;
    char* errorStr;
    char* varName;
    int typevar;
    char* varStr;
    int varBoolean;
    double  varNumeric;
    TVariable* nextRecored;
};
