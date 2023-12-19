
 
%{
 
       #define yylex SCRlex 
       #include <math.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <ctype.h>
       #include <conio.h>
	   #include "TToken.h"  
	   int SCRlex(void);
       void yyerror (char const *);
       void yyIni(ParserSCR* mparserSCR); 
       ParserSCR* parserSCR;
 
%}
 
%start input     
 
%union { 
    TToken *_token = nullptr;
}

%token <_token> NUMBER
%token <_token> IDENTIFIER
%token <_token> STRINGT 
%token <_token> BOOLEANT
%token <_token> ASSIGN  /* := */
%token <_token> LQ     /* < */ 
%token <_token> GQ     /* > */ 
%token <_token> LEQ     /* <= */
%token <_token> EQ      /* = */
%token <_token> GEQ     /* >= */
%token <_token> NEQ     /* <> */
%token <_token> AND     /* AND */
%token <_token> OR      /* OR */
%token <_token> PLUS MINUS TIMES DIVIDE
%token <_token> BRACKETOPEN BRACKETCLOSE
%token <_token> COMMA
%token <_token> BRACKETCURLYOPEN BRACKETCURLYCLOSE 
%token <_token> END
%type <_token> input line expression_list exp

%left BRACKETOPEN BRACKETCLOSE 
%left PLUS MINUS
%left TIMES DIVIDE
 
%right UMINUS 
%left AND
%left OR 
%left LEQ     /* <= */
%left EQ      /* = */
%left LQ     /* < */ 
%left GQ     /* > */ 
%left GEQ     /* >= */
%left NEQ     /* <> */ 
%right ASSIGN


    
%% /* Grammar rules and actions follow.  */

     input:    /* empty */ {    }  
              | input line { parserSCR->root_token = $2; YYACCEPT ;}   
     ;
     
     line:     exp END      { $$ = $1 ; }
             | error END    { YYABORT	;   } 
             | IDENTIFIER  ASSIGN exp END {
                                                 $2->left = $1;
                                                 $1->tokenType=TTokenType::TVar;
                                                $2->right = $3;
                                                $$ = $2; 
                                        }
     ;

     expression_list:
    /* empty */  { }
    | expression_list COMMA exp {
        $2->left = $1;
        $2->right = $3;
        $$ = $2; 
    }
    | exp  { $$ = $1; }
    ;
      
     exp:      NUMBER              { $$ = $1;         }
             | STRINGT              { $$ = $1;         }
             | BOOLEANT             { $$ = $1;         }
             | IDENTIFIER { 
                             $1->tokenType=TTokenType::TVar;
                             $$ = $1;   
                          }
             | exp PLUS exp        { 
			                         $2->left = $1;
                                     $2->right = $3;
									 $$ = $2;    
									}
             | exp MINUS exp        { 
			                         $2->left = $1;
                                     $2->right = $3;
									 $$ = $2;     
									}
             | exp TIMES exp        { 
			                         $2->left = $1;
                                     $2->right = $3;
									 $$ = $2;    
									}
             | exp DIVIDE exp       { 
			                          $2->left = $1;
                                      $2->right = $3;
									  $$ = $2; 
									 }
             | MINUS exp  %prec UMINUS { 
			                             $1->left = nullptr;
			                             $1->right = $2;
			                             $$ = $1;        
									    }
             | BRACKETOPEN exp BRACKETCLOSE   { 
			                                    $1->left = $2;
											    $1->right = nullptr;
												$$ = $1;         
											   }
             | IDENTIFIER BRACKETCURLYOPEN expression_list BRACKETCURLYCLOSE {
                           $1->left = $3;
                           $1->tokenType=TTokenType::TFun;
                           $$ = $1; 
                           }
            | exp  EQ exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            }
            | exp  LEQ exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            } /* <= */ 
            | exp  GEQ exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            } /* >= */
            | exp  LQ exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            }     /* < */ 
            | exp  GQ exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            }     /* > */ 
            | exp  NEQ exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            } /* <> */ 
            | exp  OR exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            } 
            | exp  AND exp   { 
                                $2->left = $1;
                                $2->right = $3;
								 $$ = $2;  
                            }     
     ;
%%

     /* The lexical analyzer returns a double floating point
        number on the stack and the token NUM, or the numeric code
        of the character read if not a number.  It skips all blanks
        and tabs, and returns 0 for end-of-input.  */
     
     #include <ctype.h>
     #include "ParserSCR.h"
	 
	 //size_t index = -1;
	 
 //   int SCRlex(void)
//    {
// 
//	  index++;
//      if (index == 0)
 //     {
//         yylval._token = createNode(TTokenType::TMinus, nullptr, nullptr); 
//		 return MINUS;
//      };
//	  if (index == 1)
//      {
//         yylval._token = createNode(TTokenType::TMinus, nullptr, nullptr); 
//		 return MINUS;
//      };
//      if (index == 2)
//      {
//         yylval._token = createNode(TTokenType::TNumeric, 3, nullptr, nullptr); 
//		 return NUMBER;
//      };
//	  if (index == 3)
//      {
 //        yylval._token = createNode(TTokenType::TPlus, nullptr, nullptr); 
//		 return PLUS;
//      }
//	  if (index == 4)
//      {
//         yylval._token  = createNode(TTokenType::TNumeric, 5, nullptr, nullptr); 
//		 return NUMBER;
//      }; 
//      if (index == 5)
//      {
//         yylval._token = createNode(TTokenType::TMultiplying, nullptr, nullptr); 
//		 return TIMES;
 //     }
 //     if (index == 6)
//      {
//         yylval._token  = createNode(TTokenType::TNumeric, 2, nullptr, nullptr); 
//		 return NUMBER;
//      }; 
//	  if (index == 7)
 //     {
//         yylval._token  = createNode(TTokenType::TEnd,nullptr, nullptr); 
//		 return END;
 //     };
//	  return 0;
 //   }	 
   
   int SCRlex(void)
    {
        parserSCR->index++;
        if (parserSCR->index < parserSCR->tokenList->size())
        {
            std::list< TToken*>::iterator element = parserSCR->tokenList->begin(); 
		    advance(element, parserSCR->index);
		    TToken* t;
		    t = *element; 
            yylval._token = t;
            switch (t->tokenType)
		    {
		      case TTokenType::TNumeric:       return NUMBER;
              case TTokenType::TPlus:          return PLUS;
              case TTokenType::TMinus:             return MINUS;
              case TTokenType::TMultiplying:       return TIMES;
              case TTokenType::TDividing:          return DIVIDE;
              case TTokenType::TBracketOpen:       return BRACKETOPEN;
              case TTokenType::TBracketClose:      return BRACKETCLOSE;
              case TTokenType::TVarOrFun:          return IDENTIFIER;
              case TTokenType::TComma:             return COMMA;
              case TTokenType::TBracketCurlyOpen:  return BRACKETCURLYOPEN;
              case TTokenType::TBracketCurlyClose: return BRACKETCURLYCLOSE; 
              case TTokenType::TEqualTo:           return ASSIGN ; /* := */
              case TTokenType::TLEQ:               return  LEQ ;    /* <= */
              case TTokenType::TEqual:             return EQ ;     /* = */
              case TTokenType::TGEQ:               return GEQ;     /* >= */
              case TTokenType::TNEQ:               return NEQ ;    /* <> */
              case TTokenType::TAND:               return AND;     /* AND */
              case TTokenType::TOR:               return OR ;     /* OR */
              case TTokenType::TString:           return STRINGT ; 
	          case TTokenType::TBoolean:          return BOOLEANT ; 
              case TTokenType::TLQ:               return LQ ;    /* < */ 
              case TTokenType::TGQ:               return GQ;     /* > */ 
              case TTokenType::TEnd:              return END;  
              default: return 1;
                
            }
        }; 
        return 0	;
    }	     

     #include <stdio.h>
     
     /* Called by SCRparse on error.  */
     void
     yyerror (char const *s)
     {
       //fprintf (stderr, "%s\n", s );
	  parserSCR->error = true;
      string str = s;
      parserSCR->error_str = str ; 
     };

     void yyIni(ParserSCR* mparserSCR)
     {
       parserSCR = mparserSCR;
     }; 