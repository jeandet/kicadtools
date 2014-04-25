#include "qicadpcb.h"


QIlib::QIcadPcb::QIcadPcb()
{

}

bool QIlib::QIcadPcb::parsePcb(const QString &pcb)
{
    parse(pcb.toStdString().c_str());
    updateConcreteTree();
    return false;
}

QString QIlib::QIcadPcb::toString()
{

}

QString QIlib::QIcadPcb::print()
{
    return rootNode.print();
}


void QIlib::QIcadPcb::updateConcreteTree()
{
//    if(this->rootNode.nodes.count())
//    {
//        if(this->rootNode.nodes.at(0)->name==QIlib::Lexique::root_c)
//        {
//            if(this->netlistRoot==NULL)
//            {
//                this->netlistRoot = new QIcadNetListRoot(this->rootNode.nodes.at(0));
//            }
//        }
//    }
}
