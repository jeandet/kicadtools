#include "qicadnet.h"

QIlib::QIcadNet::QIcadNet()
{
}

QIlib::QIcadNet::~QIcadNet()
{

}


QIlib::QIcadNetNode::QIcadNetNode(QString ref, QString node)
{
    this->p_ref = ref;
    this->p_node = node;
}
