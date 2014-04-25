%{
/* C++ string header, for string ops below */
#include <string>
#include <QString>
/* Implementation of yyFlexScanner */
#include "lispLike_scanner.h"
#include "lispLike.hpp"

/* typedef to make the returns for the tokens shorter */
typedef QIlib::lispLike_Parser::token token;

/* define to keep from re-typing the same code over and over */
#define STOKEN( x ) ( new QString( x ) )

/* define yyterminate as this instead of NULL */
//#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H
%}

%option debug
%option nodefault
%option yyclass="lispLike_Scanner"
%option noyywrap
%option c++


/* .                                 { return yytext[0]; }*/

%%

[ \t\n]+                        { }


\"[a-zA-Z0-9\-\/\(\)\. \:]+\"   {
                                    yylval->sval = STOKEN( yytext );
                                    return( token::VALUE );
                                }

\([a-zA-Z0-9\_]+                  {
                                    yylval->sval = STOKEN( yytext );
                                    return( token::NODE );
                                }


\)                              {
                                    return( token::CLOSENODE );
                                }


[a-zA-Z0-9\-\/\.\_\~\?\*]+      {
                                    yylval->sval = STOKEN( yytext );
                                    return( token::VALUE );
                                }



\"\"                             {
                                    yylval->sval = STOKEN( yytext );
                                    return( token::VALUE );
                                 }


.|\n                             {}


%%







