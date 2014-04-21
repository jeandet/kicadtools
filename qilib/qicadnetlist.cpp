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
    :netlistRoot(NULL)
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


void QIlib::QIcadNetList::updateConcreteTree()
{
    if(this->rootNode.nodes.count())
    {
        if(this->rootNode.nodes.at(0)->name==QIlib::Lexique::root_c)
        {
            if(this->netlistRoot==NULL)
            {
                this->netlistRoot = new QIcadNetListRoot(this->rootNode.nodes.at(0));
            }
        }
    }
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
    this->setNode(node);
}

void QIlib::QIcadNetListRoot::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
    if(node->name==QIlib::Lexique::root_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::design_c)
            {
                this->design.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::components_c)
            {
                this->setComponents(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::libparts_c)
            {
                this->setLibParts(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::libraries_c)
            {
                this->setLibraries(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::nets_c)
            {
                this->setNets(node->nodes.at(i));
            }
        }
    }
}

void QIlib::QIcadNetListRoot::setComponents(QIlib::AbstractNode *node)
{
    while(components.count())
    {
        QIcadNetListComponent* component;
        component = components.last();
        components.removeLast();
        delete component;
    }
    apendComponents(node);
}

void QIlib::QIcadNetListRoot::apendComponents(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::components_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::component_c)
            {
                this->components.append(new QIcadNetListComponent(node->nodes.at(i)));
            }
        }
    }
}

void QIlib::QIcadNetListRoot::setLibParts(QIlib::AbstractNode *node)
{
    while(libparts.count())
    {
        QIcadNetListLibPart* libpart;
        libpart = libparts.last();
        libparts.removeLast();
        delete libpart;
    }
    apendLibParts(node);
}

void QIlib::QIcadNetListRoot::apendLibParts(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::libparts_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::libpart_c)
            {
                this->libparts.append(new QIcadNetListLibPart(node->nodes.at(i)));
            }
        }
    }
}

void QIlib::QIcadNetListRoot::setLibraries(QIlib::AbstractNode *node)
{
    while(libraries.count())
    {
        QIcadNetListLibrary* lib;
        lib = libraries.last();
        libraries.removeLast();
        delete lib;
    }
    apendLibraries(node);
}

void QIlib::QIcadNetListRoot::apendLibraries(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::libraries_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::library_c)
            {
                this->libraries.append(new QIcadNetListLibrary(node->nodes.at(i)));
            }
        }
    }
}

void QIlib::QIcadNetListRoot::setNets(QIlib::AbstractNode *node)
{
    while(nets.count())
    {
        QIcadNetListNet* net;
        net = nets.last();
        nets.removeLast();
        delete net;
    }
    apendNets(node);
}

void QIlib::QIcadNetListRoot::apendNets(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::nets_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::net_c)
            {
                this->nets.append(new QIcadNetListNet(node->nodes.at(i)));
            }
        }
    }
}


QIlib::QIcadNetListComponent::QIcadNetListComponent(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    setNode(node);
}

void QIlib::QIcadNetListComponent::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::component_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::ref_c)
            {
                this->ref.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::value_c)
            {
                this->value.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::libsource_c)
            {
                this->libsource.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::sheetpath_c)
            {
                this->sheetpath.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tstamp_c)
            {
                this->tstamp.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadNetListDesign::QIcadNetListDesign(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadNetListDesign::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::design_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::source_c)
            {
                this->source.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::date_c)
            {
                this->date.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tool_c)
            {
                this->tool.setNode(node->nodes.at(i));
            }
        }
    }
}

QIlib::QIcadNetListLibPart::QIcadNetListLibPart(QIlib::AbstractNode *node)
{
        setNode(node);
}
/*
(libparts
    (libpart (lib guan) (part 24L-MOD-8)
      (fields
        (field (name Reference) IC)
        (field (name Value) 24L-MOD-8))
      (pins
        (pin (num 1) (name GND) (type power_in))
        (pin (num 2) (name VCC) (type power_in))
*/
void QIlib::QIcadNetListLibPart::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::libpart_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::lib_c)
            {
                this->lib.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::part_c)
            {
                this->part.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::fields_c)
            {
                setFields(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::pins_c)
            {
                setPins(node->nodes.at(i));
            }
        }
    }
}

void QIlib::QIcadNetListLibPart::setFields(QIlib::AbstractNode *node)
{
    while(fields.count())
    {
        QIcadNetListField* field;
        field = fields.last();
        fields.removeLast();
        delete field;
    }
    apendFields(node);
}

void QIlib::QIcadNetListLibPart::apendFields(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::fields_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::field_c)
            {
                this->fields.append(new QIcadNetListField(node->nodes.at(i)));
            }
        }
    }
}

void QIlib::QIcadNetListLibPart::setPins(QIlib::AbstractNode *node)
{
    while(pins.count())
    {
        QIcadNetListPin* pin;
        pin = pins.last();
        pins.removeLast();
        delete pin;
    }
    apendPins(node);
}

void QIlib::QIcadNetListLibPart::apendPins(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::pins_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::pin_c)
            {
                this->pins.append(new QIcadNetListPin(node->nodes.at(i)));
            }
        }
    }
}


QIlib::QIcadNetListLibrary::QIcadNetListLibrary(QIlib::AbstractNode *node)
{
    setNode(node);
}

void QIlib::QIcadNetListLibrary::setNode(QIlib::AbstractNode *node)
{
/*
    (library (logical guan)
      (uri /home/guan/boards/guan.lib))
*/
    if(node->name==QIlib::Lexique::library_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::logical_c)
            {
                this->logical.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::uri_c)
            {
                this->uri.setNode(node->nodes.at(i));
            }
        }
    }
}



QIlib::QIcadNetListField::QIcadNetListField(QIlib::AbstractNode *node)
{
    setNode(node);
}

void QIlib::QIcadNetListField::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::field_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::name_c)
            {
                this->name.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadNetListLibPart::QIcadNetListPin::QIcadNetListPin(QIlib::AbstractNode *node)
{
    setNode(node);
}

void QIlib::QIcadNetListLibPart::QIcadNetListPin::setNode(QIlib::AbstractNode *node)
{
    //(pin (num 1) (name GND) (type power_in))
    if(node->name==QIlib::Lexique::pin_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::name_c)
            {
                this->name.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::num_c)
            {
                this->num.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::type_c)
            {
                this->type.setNode(node->nodes.at(i));
            }
        }
    }
}

QIlib::QIcadNetListComponent::QIcadNetListLibSource::QIcadNetListLibSource(QIlib::AbstractNode *node)
{
    setNode(node);
}

void QIlib::QIcadNetListComponent::QIcadNetListLibSource::setNode(QIlib::AbstractNode *node)
{
    //(libsource (lib guan) (part 24L-MOD-8))
    if(node->name==QIlib::Lexique::libsource_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::lib_c)
            {
                this->lib.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::part_c)
            {
                this->part.setNode(node->nodes.at(i));
            }
        }
    }
}

QIlib::QIcadNetListComponent::QIcadNetListSheetPath::QIcadNetListSheetPath(QIlib::AbstractNode *node)
{
    setNode(node);
}

void QIlib::QIcadNetListComponent::QIcadNetListSheetPath::setNode(QIlib::AbstractNode *node)
{
    //(sheetpath (names /) (tstamps /))
    if(node->name==QIlib::Lexique::sheetpath_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::names_c)
            {
                this->names.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tstamps_c)
            {
                this->tstamps.setNode(node->nodes.at(i));
            }
        }
    }
}

QIlib::QIcadNetListNet::QIcadNetListNet(QIlib::AbstractNode *node)
{
    setNode(node);
}

void QIlib::QIcadNetListNet::setNode(QIlib::AbstractNode *node)
{
    /*
    (nets
        (net (code 15) (name "")
          (node (ref C4) (pin 1))
          (node (ref U2) (pin 4)))
        (net (code 16) (name GND)
          (node (ref D1) (pin 2))
          (node (ref C1) (pin 2))
          (node (ref IC1) (pin 1))
    */
    if(node->name==QIlib::Lexique::net_c)
    {
        this->p_node = node;
        while(NetNodes.count())
        {
            QIcadNetListNetNode* net;
            net = NetNodes.last();
            NetNodes.removeLast();
            delete net;
        }
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::name_c)
            {
                this->name.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::code_c)
            {
                this->code.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::node_c)
            {
                NetNodes.append(new QIcadNetListNetNode(node->nodes.at(i)));
            }
        }
    }
}

QIlib::QIcadNetListNet::QIcadNetListNetNode::QIcadNetListNetNode(QIlib::AbstractNode *node)
{
    setNode(node);
}

void QIlib::QIcadNetListNet::QIcadNetListNetNode::setNode(QIlib::AbstractNode *node)
{
    //(node (ref D1) (pin 2))
    if(node->name==QIlib::Lexique::node_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::ref_c)
            {
                this->ref.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::pin_c)
            {
                this->pin.setNode(node->nodes.at(i));
            }
        }
    }
}





















