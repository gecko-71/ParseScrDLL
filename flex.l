%{
#include "ParserSCR.h"
int no_of_lines = 0;
int no_of_chars = 0;
ParserSCR* parserSCRl;

 
extern YY_BUFFER_STATE yy_buffer_state;
%}
%option noyywrap
/***rule 1 counts the number of lines,
rule 2 counts the number of characters
and rule 3 specifies when to stop
taking input***/
%%
[0-9]+                parserSCRl->AddToken(TTokenType::TNumeric, atof(yytext));
"+"                   parserSCRl->AddToken(TTokenType::TPlus); 
"("                   parserSCRl->AddToken(TTokenType::TBracketOpen); 
")"                   parserSCRl->AddToken(TTokenType::TBracketClose); 
"-"                   parserSCRl->AddToken(TTokenType::TMinus); 
"*"                   parserSCRl->AddToken(TTokenType::TMultiplying ); 
"/"                   parserSCRl->AddToken(TTokenType::TDividing); 
"{"                   parserSCRl->AddToken(TTokenType::TBracketCurlyOpen); 
"}"                   parserSCRl->AddToken(TTokenType::TBracketCurlyClose); 
":="                  parserSCRl->AddToken(TTokenType::TEqualTo); 
"="                   parserSCRl->AddToken(TTokenType::TEqual); 
","                   parserSCRl->AddToken(TTokenType::TComma);
"<="                  parserSCRl->AddToken(TTokenType::TLEQ);
">="                  parserSCRl->AddToken(TTokenType::TGEQ); 
"<"                   parserSCRl->AddToken(TTokenType::TLQ);
">"                   parserSCRl->AddToken(TTokenType::TGQ); 
"<>"                  parserSCRl->AddToken(TTokenType::TNEQ);  
"AND"                 parserSCRl->AddToken(TTokenType::TAND);	 
"OR"                  parserSCRl->AddToken(TTokenType::TOR);	  
"F."               parserSCRl->AddTokenB(TTokenType::TBoolean, false);	 
"T."                parserSCRl->AddTokenB(TTokenType::TBoolean, true);
[0-9]+\.[0-9]+        parserSCRl->AddToken(TTokenType::TNumeric, atof(yytext));
" "                   ;
<<EOF>>               { return 0; };
[ \t\r\n]             ;
.                     { parserSCRl->SetError(yytext);  return -10;};
'[^']*'               {
                         string str = yytext;
                         parserSCRl->AddToken(TTokenType::TString, str);
                       }
[A-Za-z][A-Za-z0-9]*  {
                         string str = yytext;parserSCRl->AddToken(TTokenType::TVarOrFun, str);
                      }
%%

/*** User code section***/
//int yywrap(){
//  return 0;
//  };

// NOT THREAD SAFE, DON'T USE FROM MULTIPLE THREADS

/*
"-"                   parserSCR->AddToken(TTokenType::TMinus); 
"*"                   parserSCR->AddToken(TTokenType::TMultiplying ); 
"/"                   parserSCR->AddToken(TTokenType::TDividing); 
"("                   parserSCR->AddToken(TTokenType::TBracketOpen); 
")"                   parserSCR->AddToken(TTokenType::TBracketClose); 
"{"                   parserSCR->AddToken(TTokenType::TBracketCurlyOpen); 
"}"                   parserSCR->AddToken(TTokenType::TBracketCurlyClose); 
":="                  parserSCR->AddToken(TTokenType::TEqualTo); 
"="                   parserSCR->AddToken(TTokenType::TEqual); 
","                   parserSCR->AddToken(TTokenType::TComma);
*/



 
int yy_first_ever_run = 1;
char LexEmptyBuffer[3] = { '\n', '\0', '\0' };
YY_BUFFER_STATE yy_buffer_state;

/*
 * Point flex at a new string to process, resetting
 * any old results from a previous parse.
 */
void setLexerBuffer( const char *expression_string , ParserSCR *mparserSCR )
{ 
    parserSCRl = mparserSCR ;
    /* out with the old (If any? How does flex know?) */
    if ( !yy_first_ever_run )
    {
        // This doesn't cause any issues (according to valgrind)
        // but I also don't see any reason to call it before the
        // first lex-run.
        yy_delete_buffer( yy_buffer_state );
    }
    else
    {
        yy_first_ever_run = 0;
    }

    /* just make sure we're pointing at something */
    if ( expression_string == NULL )
    {
        expression_string = LexEmptyBuffer;
    }

    /* reset the scan */    
    yy_buffer_state = yy_scan_string( expression_string );  /* auto-resets lexer state */
}
 
