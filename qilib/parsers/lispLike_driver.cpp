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
/*Mainly copied from http://research.engineering.wustl.edu/~beardj/FlexBisonC++.html*/
#include "lispLike_driver.h"
#include<assert.h>


QIlib::QIcadAbstractNodeWrapper::QIcadAbstractNodeWrapper(AbstractNode *node)
{
    this->p_node = node;
}

QIlib::QIcadAbstractNodeWrapper::~QIcadAbstractNodeWrapper()
{
    /*First delete all the childs*/
    for(int i=0;i<this->childs.count();i++)
    {
        if(this->childs.at(i))
            delete this->childs.at(i);
    }
}

QString QIlib::QIcadAbstractNodeWrapper::value()
{
    if((p_node->Values.count()>0) && p_node)
        return p_node->Values.at(0);
    return QString("");
}

QString QIlib::QIcadAbstractNodeWrapper::value(int index)
{
    if((p_node->Values.count()>index) && p_node)
        return p_node->Values.at(index);
    return QString("");
}

QString QIlib::QIcadAbstractNodeWrapper::catValues()
{
    if(p_node)
    {
        QString result("");
        for(int i=0;i<p_node->Values.count();i++)
        {
            result.append(p_node->Values.at(i));
        }
        return result;
    }
}

void QIlib::QIcadAbstractNodeWrapper::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}

QIlib::lispLike_Driver::lispLike_Driver()
    :parser( NULL ),scanner( NULL )
{
    currentNode = &rootNode;
}

QIlib::lispLike_Driver::~lispLike_Driver()
{
    delete(scanner);
    scanner = NULL;
    delete(parser);
    parser = NULL;
}

bool QIlib::lispLike_Driver::parse(const char *filename)
{
    if(filename!=NULL)
    {
        std::ifstream in_file( filename );
        if( ! in_file.good() ) return false;

        delete(scanner);
        try
        {
            scanner = new QIlib::lispLike_Scanner( &in_file );
        }
        catch( std::bad_alloc &ba )
        {
            std::cerr << "Failed to allocate scanner: (" <<
                         ba.what() << ")\n";
            return false;
        }

        delete(parser);
        try
        {
            parser = new QIlib::lispLike_Parser( (*scanner) /* scanner */,
                                                 (*this) /* driver */ );
        }
        catch( std::bad_alloc &ba )
        {
            std::cerr << "Failed to allocate parser: (" <<
                         ba.what() << ")\n";
            return false;
        }
        const int accept( 0 );
        if( parser->parse() != accept )
        {
            std::cerr << "Parse failed!!\n";
            return false;
        }
        return true;
    }
    return false;
}

void QIlib::lispLike_Driver::add_node(const QString &node)
{
    QIlib::AbstractNode* newNode = new  QIlib::AbstractNode(node,currentNode);
    currentNode = newNode;
}

void QIlib::lispLike_Driver::add_node(const QString &node, const QString &value)
{
    QIlib::AbstractNode* newNode = new  QIlib::AbstractNode(node,value,currentNode);
    currentNode = newNode;
}

void QIlib::lispLike_Driver::add_value(const QString &value)
{
    currentNode->Values.append(value);
}

void QIlib::lispLike_Driver::close_node()
{
    if(currentNode->parent)
        currentNode = currentNode->parent;
}










QIlib::AbstractNode::AbstractNode(QIlib::AbstractNode *parent)
{
    this->parent =parent;
    if(parent)
        parent->nodes.append(this);
}


QIlib::AbstractNode::AbstractNode(const QString &Name, QIlib::AbstractNode *parent)
    :name(Name)
{
    this->parent = parent;
    if(parent)
        parent->nodes.append(this);
}


QIlib::AbstractNode::AbstractNode(const QString &Name, const QString &Value, QIlib::AbstractNode *parent)
    :name(Name)
{
    this->parent = parent;
    if(parent)
        parent->nodes.append(this);
    Values.append(Value);
}

QString QIlib::AbstractNode::print()
{
    QString result;
    result.append(this->name+" ");
    for(int i=0;i<this->nodes.count();i++)
    {
        result.append(this->nodes.at(i)->print());
    }
    for(int i=0;i<this->Values.count();i++)
    {
        result.append(Values.at(i)+" ");
    }
    result.append(")");
    return result;
}
