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
#include "qicadnetlist.h"
#include <QRegularExpression>


const char* root_c                 ="(export";
const char* version_c              ="(version";
const char* design_c               ="(design";
const char* source_c               ="(source";
const char* date_c                 ="(date";
const char* tool_c                 ="(tool";
const char* components_c           ="(components";
const char* component_c            ="(comp";
const char* ref_c                  ="(ref";
const char* value_c                ="(value";
const char* libsource_c            ="(libsource";
const char* lib_c                  ="(lib";
const char* part_c                 ="(part";
const char* sheetpath_c            ="(sheetpath";
const char* names_c                ="(names";
const char* tstamps_c              ="(tstamps";
const char* tstamp_c               ="(tstamp";
const char* libparts_c             ="(libparts";
const char* libpart_c              ="(libpart";
const char* fields_c               ="(fields";
const char* field_c                ="(field";
const char* name_c                 ="(name";
const char* pins_c                 ="(pins";
const char* pin_c                  ="(pin";
const char* num_c                  ="(num";
const char* type_c                 ="(type";
const char* libraries_c            ="(libraries";
const char* library_c              ="(library";
const char* logical_c              ="(logical";
const char* uri_c                  ="(uri";
const char* nets_c                 ="(nets";
const char* net_c                  ="(net";
const char* code_c                 ="(code";
const char* node_c                 ="(node";


QIlib::QIcadNetList::QIcadNetList()
{

}


bool QIlib::QIcadNetList::parseNetList(const QString &netlist)
{

    parse(netlist.toStdString().c_str());
    updateConcreteTree();
    return false;
}

QString QIlib::QIcadNetList::print()
{
    return rootNode.print();
}

QIlib::AbstractNode *QIlib::QIcadNetList::getAbstractNode(const QString &node, int index)
{
    return getAbstractNode(&rootNode,node,&index);
}

QIlib::AbstractNode *QIlib::QIcadNetList::getAbstractNode(QIlib::AbstractNode *rootNode, const QString &node, int* index)
{
    for(int i=0;i<rootNode->nodes.count();i++)
    {
        if(rootNode->nodes.at(i)->name==node)
        {
            if((*index)==0)
            {
                return rootNode->nodes.at(i);
            }
            (*index)-=1;
        }
        else
        {
            if(0<rootNode->nodes.at(i)->nodes.count())
            {
                QIlib::AbstractNode *result=getAbstractNode(rootNode->nodes.at(i),node,index);
                if(NULL!=result)return result;
            }
        }
    }
    return NULL;
}

/*
    QString version;
    QIcadNetListDesign design;
    QList<QIcadNetListComponent*> components;
    QList<QIcadNetListLibPart*> libparts;
    QIcadNetListLevel rootSheet;
*/

#define setVal(dest,node,name,index) \
    (node) = getAbstractNode((name),(index));\
    if(((node)!=NULL)&&(0<(node)->Values.count())) \
{\
    (dest) = (node)->Values.at(0); \
    } \


void QIlib::QIcadNetList::updateConcreteTree()
{
    QIlib::AbstractNode *node;
    setVal(this->version,node,QIlib::Lexique::version_c,0);
    setVal(this->design.date,node,QIlib::Lexique::date_c,0);
    setVal(this->design.source,node,QIlib::Lexique::source_c,0);
    setVal(this->design.tool,node,QIlib::Lexique::tool_c,0);
    this->design.date.clear();
}





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



QIlib::QIcadNetListRoot::QIcadNetListRoot(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{

}


QIlib::QIcadNetListComponent::QIcadNetListComponent(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{

}
