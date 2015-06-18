%skeleton "lalr1.cc"
//%require  "3.0"
//%debug
%defines
%define api.namespace {QIlib}
%define parser_class_name {lispLike_Parser}

%code requires{ 
   #include <QString>
   namespace QIlib {
      class lispLike_Driver;
      class lispLike_Scanner;
   }
}

%lex-param   { QIlib::lispLike_Scanner  &scanner  }
%parse-param { QIlib::lispLike_Scanner  &scanner  }

%lex-param   { QIlib::lispLike_Driver  &driver  }
%parse-param { QIlib::lispLike_Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   /* include for all driver functions */
   #include <lispLike_driver.h>

   /* this is silly, but I can't figure out a way around */
   static int yylex(QIlib::lispLike_Parser::semantic_type *yylval,
                    QIlib::lispLike_Scanner  &scanner,
                    QIlib::lispLike_Driver   &driver);


}

/* token types */
%union {
   QString* sval;
}

//%token            END    0     "end of file"
%token   <sval>   VALUE
%token   <sval>   NODE
%token            CLOSENODE

/* destructor rule for <sval> objects */
%destructor { if ($$)  { delete ($$); ($$) = NULL; } } <sval>


%%

PartNode
  : NODE  { driver.add_node( *$1 ); }
  | PartNode NODE { driver.add_node( *$2 ); }
  | PartNode VALUE { driver.add_value( *$2 ); }
  | PartNode CLOSENODE { driver.close_node(); }


%%


void  QIlib::lispLike_Parser::error(const std::string& error)
{
   std::cerr << "Error: " << error << "\n";
}


/* include for access to scanner.yylex */
#include "lispLike_scanner.h"

static int yylex( QIlib::lispLike_Parser::semantic_type *yylval,
       QIlib::lispLike_Scanner  &scanner,
       QIlib::lispLike_Driver   &driver )
{
   return( scanner.yylex(yylval) );
}
