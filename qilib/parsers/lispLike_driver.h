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
#ifndef LISPLIKE_DRIVER_H
#define LISPLIKE_DRIVER_H
#include <string>
#include "lispLike_scanner.h"
#include <lispLike/lispLike.hpp>
#include <QString>
#include <QList>
#include <QStringList>
#include <iostream>
#include <cstdlib>
#include <fstream>

namespace QIlib{

class AbstractNode
{
public:
    AbstractNode( QIlib::AbstractNode* parent=NULL);
    AbstractNode(const QString& Name, QIlib::AbstractNode* parent=NULL);
    AbstractNode(const QString& Name,const QString& Value, QIlib::AbstractNode* parent=NULL);
    QString print();
    QList<QIlib::AbstractNode*> nodes;
    QString name;
    QStringList Values;
    QIlib::AbstractNode* parent;
};

class lispLike_Driver
{
public:
    lispLike_Driver();

    virtual ~lispLike_Driver();
    bool parse( const char *filename );
    void add_node( const QString &node );
    void add_node( const QString &node , const QString &value);
    void add_value( const QString &value );
    void close_node();


protected:

    QIlib::lispLike_Parser *parser;
    QIlib::lispLike_Scanner *scanner;
    QIlib::AbstractNode rootNode;
    QIlib::AbstractNode* currentNode;
};
}
#endif // LISPLIKE_DRIVER_H
