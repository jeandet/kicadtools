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





QIlib::QIcadAbstractNodeWrapper::QIcadAbstractNodeWrapper()
{

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
