#ifndef QICADNETLIST_H
#define QICADNETLIST_H
#include <QString>
#include <QStringList>
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
#include <QList>
#include <QFile>
#include <parsers/lispLike_driver.h>
#include <qicadnet.h>

namespace QIlib{

namespace Lexique
{
extern "C" const char* root_c       ;
extern "C" const char* version_c     ;
extern "C" const char* design_c      ;
extern "C" const char* source_c      ;
extern "C" const char* date_c        ;
extern "C" const char* tool_c        ;
extern "C" const char* components_c  ;
extern "C" const char* component_c   ;
extern "C" const char* ref_c         ;
extern "C" const char* value_c       ;
extern "C" const char* libsource_c   ;
extern "C" const char* lib_c         ;
extern "C" const char* part_c        ;
extern "C" const char* sheetpath_c   ;
extern "C" const char* names_c       ;
extern "C" const char* tstamps_c     ;
extern "C" const char* tstamp_c      ;
extern "C" const char* libparts_c    ;
extern "C" const char* libpart_c     ;
extern "C" const char* fields_c      ;
extern "C" const char* field_c       ;
extern "C" const char* name_c        ;
extern "C" const char* pins_c        ;
extern "C" const char* pin_c         ;
extern "C" const char* num_c         ;
extern "C" const char* type_c        ;
extern "C" const char* libraries_c   ;
extern "C" const char* library_c     ;
extern "C" const char* logical_c     ;
extern "C" const char* uri_c         ;
extern "C" const char* nets_c        ;
extern "C" const char* net_c         ;
extern "C" const char* code_c        ;
extern "C" const char* node_c        ;

}



class QIcadAbstractNodeWrapper
{
public:
    QIcadAbstractNodeWrapper(QIlib::AbstractNode* node);
    QIcadAbstractNodeWrapper(){}
    ~QIcadAbstractNodeWrapper();
    QString value();
    QString value(int index);
    QString catValues();
    QList<QIcadAbstractNodeWrapper*> childs;
    QIcadAbstractNodeWrapper* parent;
    virtual void setNode(QIlib::AbstractNode* node);

    QIlib::AbstractNode* p_node;
};

class QIcadNetListDesign : public QIcadAbstractNodeWrapper
{
public:
    QIcadNetListDesign(QIlib::AbstractNode* node);
    QIcadNetListDesign(){}
    QIcadAbstractNodeWrapper source;
    QIcadAbstractNodeWrapper date;
    QIcadAbstractNodeWrapper tool;
    void setNode(QIlib::AbstractNode* node);
};



 /*
  * (comp (ref IC1)
      (value 24L-MOD-8)
      (libsource (lib guan) (part 24L-MOD-8))
      (sheetpath (names /) (tstamps /))
      (tstamp 52533BBE))
*/
class  QIcadNetListComponent:public QIcadAbstractNodeWrapper
{
    class QIcadNetListLibSource : QIcadAbstractNodeWrapper
    {
    public:
        QIcadNetListLibSource(AbstractNode* node);
        QIcadNetListLibSource(){}
        QIcadAbstractNodeWrapper lib;
        QIcadAbstractNodeWrapper part;
        void setNode(AbstractNode* node);
    };
    class QIcadNetListSheetPath : QIcadAbstractNodeWrapper
    {
    public:
        QIcadNetListSheetPath(AbstractNode* node);
        QIcadNetListSheetPath(){}
        QIcadAbstractNodeWrapper names;
        QIcadAbstractNodeWrapper tstamps;
        void setNode(AbstractNode* node);
    };
public:
     QIcadNetListComponent(AbstractNode* node);
     QIcadAbstractNodeWrapper ref;
     QIcadAbstractNodeWrapper value;
     QIcadNetListLibSource libsource;
     QIcadNetListSheetPath sheetpath;
     QIcadAbstractNodeWrapper tstamp;
     void setNode(QIlib::AbstractNode* node);
};


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
class QIcadNetListField : QIcadAbstractNodeWrapper
{
public:
    QIcadNetListField(AbstractNode* node);
    QIcadAbstractNodeWrapper name;
    void setNode(AbstractNode* node);
};


class QIcadNetListLibPart : QIcadAbstractNodeWrapper
{
    class QIcadNetListPin : QIcadAbstractNodeWrapper
    {
    public:
        QIcadNetListPin(AbstractNode* node);
        QIcadAbstractNodeWrapper type;
        QIcadAbstractNodeWrapper num;
        QIcadAbstractNodeWrapper name;
        void setNode(AbstractNode* node);
    };
public:
    QIcadNetListLibPart(AbstractNode* node);
    QIcadAbstractNodeWrapper lib;
    QIcadAbstractNodeWrapper part;
    QList<QIcadNetListField*> fields;
    QList<QIcadNetListPin*> pins;
    void setNode(AbstractNode* node);
    void setFields(QIlib::AbstractNode* node);
    void apendFields(QIlib::AbstractNode* node);
    void setPins(QIlib::AbstractNode* node);
    void apendPins(QIlib::AbstractNode* node);
};

/*
(libraries
    (library (logical guan)
      (uri /home/guan/boards/guan.lib))
    (library (logical device)
      (uri /usr/share/kicad/library/device.lib))
    (library (logical conn)
      (uri /usr/share/kicad/library/conn.lib)))
*/

class  QIcadNetListLibrary : QIcadAbstractNodeWrapper
{
public:
     QIcadNetListLibrary(AbstractNode* node);
     QIcadAbstractNodeWrapper uri;
     QIcadAbstractNodeWrapper logical;
     void setNode(AbstractNode* node);
};
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

class QIcadNetListNet : QIcadAbstractNodeWrapper
{
    class QIcadNetListNetNode: QIcadAbstractNodeWrapper
    {
    public:
        QIcadNetListNetNode(AbstractNode* node);
        QIcadAbstractNodeWrapper ref;
        QIcadAbstractNodeWrapper pin;
        void setNode(AbstractNode* node);
    };
public:
    QIcadNetListNet(AbstractNode* node);
    QList<QIcadNetListNetNode*> NetNodes;
    QIcadAbstractNodeWrapper code;
    QIcadAbstractNodeWrapper name;
    void setNode(AbstractNode* node);

};

class QIcadNetListRoot : public QIcadAbstractNodeWrapper
{
public:
    QIcadNetListRoot(QIlib::AbstractNode* node);
    QIcadNetListDesign design;
    QList<QIcadNetListComponent*> components;
    QList<QIcadNetListLibPart*> libparts;
    QList<QIcadNetListLibrary*> libraries;
    QList<QIcadNetListNet*> nets;
    void setNode(QIlib::AbstractNode* node);
    void setComponents(QIlib::AbstractNode* node);
    void apendComponents(QIlib::AbstractNode* node);
    void setLibParts(QIlib::AbstractNode* node);
    void apendLibParts(QIlib::AbstractNode* node);
    void setLibraries(QIlib::AbstractNode* node);
    void apendLibraries(QIlib::AbstractNode* node);
    void setNets(QIlib::AbstractNode* node);
    void apendNets(QIlib::AbstractNode* node);
};


class QIcadNetList : private lispLike_Driver
{
public:
    QIcadNetList();
    bool parseNetList(const QString& netlist);
    QString toString();
    QString fileName;
    QString print();
    QIcadNetListRoot* netlistRoot;
private:
    QIlib::AbstractNode* getAbstractNode(const QString& node,int index);
    QIlib::AbstractNode* getAbstractNode(QIlib::AbstractNode* rootNode,const QString& node,int* index);
    void updateConcreteTree();
};
}
#endif // QICADNETLIST_H
