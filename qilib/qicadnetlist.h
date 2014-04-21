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

class QIcadNetListLevel
{
public:
    QIcadNetListLevel() {}
    QList<QIcadNetListLevel*> sublevels;
    QList<QIcadNet*> nets;
};

class QIcadNetListDesign
{
public:
    QIcadNetListDesign(){}
    QString source;
    QString date;
    QString tool;
};

class QIcadNetListComponent
{
public:
    typedef struct libsource_t
    {
        QString lib;
        QString part;
    }libsource_t;
    typedef struct sheetpath_t
    {
        QString names;
        QString tstamp;
    }sheetpath_t;
    QIcadNetListComponent(){}
    QString ref;
    QString value;
    QString tstamp;
    libsource_t libsource;
    sheetpath_t sheetpath;
};

class QIcadNetListLibPart
{
public:
    typedef struct fields_t
    {
        QString ref;
        QString value;
        QString footprint;
        QString datasheet;
    }fields_t;
    typedef struct pin_t
    {
        int num;
        QString name;
        QString type;
    }pin_t;
    QIcadNetListLibPart();
    QString lib;
    QString part;
    QStringList footprints;
    fields_t fields;
    QList<pin_t*> pins;
};

class QIcadAbstractNodeWrapper
{
public:
    QIcadAbstractNodeWrapper(QIlib::AbstractNode* node);
    ~QIcadAbstractNodeWrapper();
    QString value();
    QString value(int index);
    QString catValues();
    void setNode(QIlib::AbstractNode* node);
    QList<QIcadAbstractNodeWrapper*> childs;
    QIcadAbstractNodeWrapper* parent;

private:
    QIlib::AbstractNode* p_node;
};

class QIcadNetListRoot : public AbstractNode
{
public:
    QIcadNetListRoot(QIlib::AbstractNode* node);
    QIcadAbstractNodeWrapper source;
    QIcadAbstractNodeWrapper date;
    QIcadAbstractNodeWrapper tool;
    QList<QIcadNetListComponent*> components;
    QList<QIcadNetListLibPart*> libparts;
    QList<QIcadNetListLibrary*> libraries;
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
public:
     QIcadNetListComponent(AbstractNode* node);
     QIcadAbstractNodeWrapper ref;
     QIcadAbstractNodeWrapper value;
     QIcadAbstractNodeWrapper libsource;
     QIcadAbstractNodeWrapper sheetpath;
     QIcadAbstractNodeWrapper tstamp;
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
    };
public:
    QIcadNetListLibPart(AbstractNode* node);
    QList<QIcadNetListField*> fields;
    QList<QIcadNetListPin*> pins;
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
    };
public:
    QIcadNetListNet(AbstractNode* node);
    QList<QIcadNetListNetNode*> NetNodes;
};



class QIcadNetList : private lispLike_Driver
{
public:
    QIcadNetList();
    bool parseNetList(const QString& netlist);
    QString toString();
    QString fileName;
    QString version;
    QIcadNetListDesign design;
    QList<QIcadNetListComponent*> components;
    QList<QIcadNetListLibPart*> libparts;
    QIcadNetListLevel rootSheet;
    QString print();
    QIcadAbstractNodeWrapper netlistRoot;
private:
    QIlib::AbstractNode* getAbstractNode(const QString& node,int index);
    QIlib::AbstractNode* getAbstractNode(QIlib::AbstractNode* rootNode,const QString& node,int* index);
    void updateConcreteTree();
};
}
#endif // QICADNETLIST_H
