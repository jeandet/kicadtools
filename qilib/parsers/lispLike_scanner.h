#ifndef LISPLIKE_SCANNER_H
#define LISPLIKE_SCANNER_H
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include <iostream>
#include <cstdlib>
#include <fstream>

#undef  YY_DECL
#define YY_DECL int  QIlib::lispLike_Scanner::yylex()

#include <lispLike/lispLike.hpp>

namespace QIlib{

class lispLike_Scanner : public yyFlexLexer
{
public:
    lispLike_Scanner(std::istream *in);
    int yylex(QIlib::lispLike_Parser::semantic_type *lval);

private:
   /* hide this one from public view */
   int yylex();
   /* yyval ptr */
   QIlib::lispLike_Parser::semantic_type *yylval;
};
}

#endif // LISPLIKE_SCANNER_H
