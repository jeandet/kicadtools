/*------------------------------------------------------------------------------
--  This file is a part of the Kicad Tools Software
--  Copyright (C) 2014, Plasma Physics Laboratory - CNRS
--
--  This program is free software; you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation; either version 2 of the License, or
--  (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
--  You should have received a copy of the GNU General Public License
--  along with this program; if not, write to the Free Software
--  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
-------------------------------------------------------------------------------*/
/*--                  Author : Alexis Jeandet
--                     Mail : alexis.jeandet@member.fsf.org
----------------------------------------------------------------------------*/
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
