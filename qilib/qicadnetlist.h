#ifndef QICADNETLIST_H
#define QICADNETLIST_H
#include <QString>
#include <QStringList>
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
    QIcadAbstractNodeWrapper();
    ~QIcadAbstractNodeWrapper();
    QString value();
    QList<QIcadAbstractNodeWrapper*> childs;
    QIcadAbstractNodeWrapper* parent;
private:
    QIlib::AbstractNode* node;
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
private:
    QIlib::AbstractNode* getAbstractNode(const QString& node,int index);
    QIlib::AbstractNode* getAbstractNode(QIlib::AbstractNode* rootNode,const QString& node,int* index);
    void updateConcreteTree();
};
}
#endif // QICADNETLIST_H
