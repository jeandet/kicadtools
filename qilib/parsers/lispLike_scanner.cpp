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
