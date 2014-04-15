#include "lispLike_scanner.h"

QIlib::lispLike_Scanner::lispLike_Scanner(std::istream *in)
    : yyFlexLexer(in), yylval( NULL )
{

}


int QIlib::lispLike_Scanner::yylex(QIlib::lispLike_Parser::semantic_type *lval)
{
    yylval = lval;
    return( yylex() );
}
