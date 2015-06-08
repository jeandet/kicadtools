#include "qicadpcb.h"


QIlib::QIcadPcb::QIcadPcb()
    :pcbRoot(NULL)
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
    if(this->rootNode.nodes.count())
    {
        if(this->rootNode.nodes.at(0)->name==QIlib::Lexique::kicad_pcb_c)
        {
            if(this->pcbRoot==NULL)
            {
                this->pcbRoot = new QIcadPcbRoot(this->rootNode.nodes.at(0));
            }
        }
    }
}


QIlib::QIcadPcbRoot::QIcadPcbRoot(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbRoot::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
    this->clrNets();
    if(node->name==QIlib::Lexique::kicad_pcb_c)
    {
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::version_c)
            {
                this->version.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::host_c)
            {
                this->host.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::page_c)
            {
                this->page.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::general_c)
            {
                this->general.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layers_c)
            {
                this->layers.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::setup_c)
            {
                this->setup.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::net_c)
            {
                this->apendNet(node->nodes.at(i));
            }
        }
    }
}

void QIlib::QIcadPcbRoot::clrNets()
{
    while(nets.count())
    {
        QIcadAbstractNodeWrapper* net;
        net = nets.last();
        nets.removeLast();
        delete net;
    }
}

void QIlib::QIcadPcbRoot::apendNet(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::net_c)
    {
        this->nets.append(new QIcadAbstractNodeWrapper(node));
    }
}


QIlib::QIcadPcbGeneralInfo::QIcadPcbGeneralInfo(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbGeneralInfo::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbLayers::QIcadPcbLayers(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbLayers::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbLine::QIcadPcbLine(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbLine::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbModule::QIcadPcbModule(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbModule::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbDimension::QIcadPcbDimension(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbDimension::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbModuleModel::QIcadPcbModuleModel(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbModuleModel::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbFpText::QIcadPcbFpText(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbFpText::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbFpTextEffects::QIcadPcbFpTextEffects(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbFpTextEffects::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbFpTextEffectsFont::QIcadPcbFpTextEffectsFont(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbFpTextEffectsFont::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbNetClass::QIcadPcbNetClass(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbNetClass::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbSetup::QIcadPcbSetup(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbSetup::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbPlotParams::QIcadPcbPlotParams(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbPlotParams::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbSegment::QIcadPcbSegment(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbSegment::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}


QIlib::QIcadPcbVia::QIcadPcbVia(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbVia::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
}
