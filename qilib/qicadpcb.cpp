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
    this->clrNets();
    this->clrModules();
    this->clrDimensions();
    this->clrLines();
    this->clrSegments();
    this->clrVias();
    this->clrArcs();
    this->clrCircles();
    this->clrTexts();
    this->clrZones();
    if(node->name==QIlib::Lexique::kicad_pcb_c)
    {
        this->p_node = node;
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
            if(node->nodes.at(i)->name==QIlib::Lexique::module_c)
            {
                this->apendModule(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::gr_line_c)
            {
                this->apendLine(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::dimension_c)
            {
                this->apendDimension(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::via_c)
            {
                this->apendVia(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::segment_c)
            {
                this->apendSegment(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::gr_text_c)
            {
                this->apendText(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::gr_arc_c)
            {
                this->apendArc(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::gr_circle_c)
            {
                this->apendCircle(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::zone_c)
            {
                this->apendZone(node->nodes.at(i));
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

void QIlib::QIcadPcbRoot::clrModules()
{
    while(modules.count())
    {
        QIcadPcbModule* module;
        module = modules.last();
        modules.removeLast();
        delete module;
    }
}

void QIlib::QIcadPcbRoot::apendModule(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::module_c)
    {
        this->modules.append(new QIcadPcbModule(node));
    }
}

void QIlib::QIcadPcbRoot::clrDimensions()
{
    while(dimensions.count())
    {
        QIcadPcbDimension* dimension;
        dimension = dimensions.last();
        dimensions.removeLast();
        delete dimension;
    }
}

void QIlib::QIcadPcbRoot::apendDimension(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::dimension_c)
    {
        this->dimensions.append(new QIcadPcbDimension(node));
    }
}

void QIlib::QIcadPcbRoot::apendLine(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_line_c)
    {
        this->lines.append(new QIcadPcbLine(node));
    }
}

void QIlib::QIcadPcbRoot::clrLines()
{
    while(lines.count())
    {
        QIcadPcbLine* line;
        line = lines.last();
        lines.removeLast();
        delete line;
    }
}

void QIlib::QIcadPcbRoot::clrSegments()
{
    while(segments.count())
    {
        QIcadPcbSegment* segment;
        segment = segments.last();
        segments.removeLast();
        delete segment;
    }
}

void QIlib::QIcadPcbRoot::apendSegment(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::segment_c)
    {
        this->segments.append(new QIcadPcbSegment(node));
    }
}

void QIlib::QIcadPcbRoot::clrVias()
{
    while(vias.count())
    {
        QIcadPcbVia* via;
        via = vias.last();
        vias.removeLast();
        delete via;
    }
}

void QIlib::QIcadPcbRoot::apendVia(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::via_c)
    {
        this->vias.append(new QIcadPcbVia(node,this->setup.defaultViaDrillSize()));
    }
}

void QIlib::QIcadPcbRoot::clrArcs()
{
    while(arcs.count())
    {
        QIcadPcbArc* arc;
        arc = arcs.last();
        arcs.removeLast();
        delete arc;
    }
}

void QIlib::QIcadPcbRoot::apendArc(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_arc_c)
    {
        this->arcs.append(new QIcadPcbArc(node));
    }
}

void QIlib::QIcadPcbRoot::clrCircles()
{
    while(circles.count())
    {
        QIcadPcbCircle* circle;
        circle = circles.last();
        circles.removeLast();
        delete circle;
    }
}

void QIlib::QIcadPcbRoot::apendCircle(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_circle_c)
    {
        this->circles.append(new QIcadPcbCircle(node));
    }
}

void QIlib::QIcadPcbRoot::clrTexts()
{
    while(texts.count())
    {
        QIcadPcbText* text;
        text = texts.last();
        texts.removeLast();
        delete text;
    }
}

void QIlib::QIcadPcbRoot::apendText(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_text_c)
    {
        this->texts.append(new QIcadPcbText(node));
    }
}

void QIlib::QIcadPcbRoot::clrZones()
{
    while(zones.count())
    {
        QIcadPcbZone* zone;
        zone = zones.last();
        zones.removeLast();
        delete zone;
    }
}

void QIlib::QIcadPcbRoot::apendZone(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::zone_c)
    {
        this->zones.append(new QIcadPcbZone(node));
    }
}

QIlib::QIcadPcbGeneralInfo::QIcadPcbGeneralInfo(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbGeneralInfo::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::general_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::links_c)
            {
                this->links.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::no_connect_c)
            {
                this->no_connections.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::area_c)
            {
                this->area.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::thickness_c)
            {
                this->thickness.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::drawings_c)
            {
                this->drawings.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tracks_c)
            {
                this->tracks.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::zones_c)
            {
                this->zones.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::modules_c)
            {
                this->modules.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::nets_c)
            {
                this->nets.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbLayers::QIcadPcbLayers(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbLayers::setNode(QIlib::AbstractNode *node)
{
    this->p_node = node;
    if(node->name==QIlib::Lexique::layers_c)
    {
        this->clrLayers();
        for(int i=0;i<node->nodes.count();i++)
        {
            this->apendLayer(node->nodes.at(i));
        }
    }
}

void QIlib::QIcadPcbLayers::clrLayers()
{
    while(layers.count())
    {
        QIcadPcbLayer* layer;
        layer = layers.last();
        layers.removeLast();
        delete layer;
    }
}

void QIlib::QIcadPcbLayers::apendLayer(QIlib::AbstractNode *node)
{
        this->layers.append(new QIcadPcbLayer(node));
}


QIlib::QIcadPcbLine::QIcadPcbLine(QIlib::AbstractNode *node)
    :QIcadAbstractPcbLine(node)
{
    this->setNode(node);
}


void QIlib::QIcadPcbLine::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_line_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::start_c)
            {
                this->p_startpos = nodeTo2DCoords(node->nodes.at(i));
                this->start.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::end_c)
            {
                this->p_stoppos = nodeTo2DCoords(node->nodes.at(i));
                this->end.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::angle_c)
            {
                this->angle.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->p_layers = node->nodes.at(i)->Values;
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->p_width = nodeValueToDouble(node->nodes.at(i));
                this->width.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbModule::QIcadPcbModule(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

const QPointF &QIlib::QIcadPcbModule::pos()
{
    return p_pos;
}

double QIlib::QIcadPcbModule::angle()
{
    return p_angle;
}

void QIlib::QIcadPcbModule::setNode(QIlib::AbstractNode *node)
{
    this->clrPads();
    if(node->name==QIlib::Lexique::module_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tedit_c)
            {
                this->tedit.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tstamp_c)
            {
                this->tstamp.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::at_c)
            {
                this->at.setNode(node->nodes.at(i));
                QStringList coords=node->nodes.at(i)->Values;
                p_pos = nodeTo2DCoords(node->nodes.at(i));
                if(coords.count()==3)
                {
                    p_angle = coords.at(2).toDouble();
                }
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tags_c)
            {
                this->tags.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::path_c)
            {
                this->path.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::attr_c)
            {
                this->attr.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::pad_c)
            {
                this->apendPad(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::fp_line_c)
            {
                this->apendLine(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::fp_text_c)
            {
                this->apendText(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::fp_circle_c)
            {
                this->apendCircle(node->nodes.at(i));
            }
        }
    }
}

void QIlib::QIcadPcbModule::clrPads()
{
    while(pads.count())
    {
        QIcadPcbPad* pad;
        pad = pads.last();
        pads.removeLast();
        delete pad;
    }
}

void QIlib::QIcadPcbModule::apendPad(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::pad_c)
    {
        this->pads.append(new QIcadPcbPad(node));
    }
}

void QIlib::QIcadPcbModule::clrTexts()
{
    while(fp_texts.count())
    {
        QIcadPcbFPText* text;
        text = fp_texts.last();
        fp_texts.removeLast();
        delete text;
    }
}

void QIlib::QIcadPcbModule::apendText(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::fp_text_c)
    {
        this->fp_texts.append(new QIcadPcbFPText(node));
    }
}

void QIlib::QIcadPcbModule::clrLines()
{
    while(fp_lines.count())
    {
        QIcadPcbFPLine* line;
        line = fp_lines.last();
        fp_lines.removeLast();
        delete line;
    }
}

void QIlib::QIcadPcbModule::apendLine(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::fp_line_c)
    {
        this->fp_lines.append(new QIcadPcbFPLine(node));
    }
}

void QIlib::QIcadPcbModule::clrCircles()
{
    while(fp_circles.count())
    {
        QIcadPcbFPCircle* circle;
        circle = fp_circles.last();
        fp_circles.removeLast();
        delete circle;
    }
}

void QIlib::QIcadPcbModule::apendCircle(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::fp_circle_c)
    {
        this->fp_circles.append(new QIcadPcbFPCircle(node));
    }
}


QIlib::QIcadPcbDimension::QIcadPcbDimension(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbDimension::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::dimension_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->width.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::gr_text_c)
            {
                this->gr_text.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::feature1_c)
            {
                this->feature1.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::crossbar_c)
            {
                this->crossbar.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::arrow1a_c)
            {
                this->arrow1a.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::arrow1b_c)
            {
                this->arrow1b.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::arrow2a_c)
            {
                this->arrow2a.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::arrow2b_c)
            {
                this->arrow2b.setNode(node->nodes.at(i));
            }
        }
    }
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


QIlib::QIcadPcbFPText::QIcadPcbFPText(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbFPText::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::pad_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::at_c)
            {
                this->at.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::effects_c)
            {
                this->effects.setNode(node->nodes.at(i));
            }
        }
    }
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
    if(node->name==QIlib::Lexique::setup_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::via_drill_c)
            {
                this->via_dril.setNode(node->nodes.at(i));
                this->p_defaultViaDrillSize = nodeValueToDouble(node->nodes.at(i));
            }
        }
    }
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
    :QIcadAbstractPcbLine(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbSegment::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::segment_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::start_c)
            {
                this->p_startpos = nodeTo2DCoords(node->nodes.at(i));
                this->start.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::end_c)
            {
                this->p_stoppos = nodeTo2DCoords(node->nodes.at(i));
                this->end.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->p_width = nodeValueToDouble(node->nodes.at(i));
                this->width.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->p_layers = node->nodes.at(i)->Values;
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::net_c)
            {
                this->net.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbVia::QIcadPcbVia(QIlib::AbstractNode *node, double defaultDrill)
    :QIcadAbstractNodeWrapper(node),p_drill(defaultDrill)
{
    this->setNode(node);
}

void QIlib::QIcadPcbVia::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::via_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::at_c)
            {
                this->at.setNode(node->nodes.at(i));
                p_pos = nodeTo2DCoords(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::size_c)
            {
                this->sizeNode.setNode(node->nodes.at(i));
                p_size = QSizeF(nodeValueToDouble(node->nodes.at(i)),nodeValueToDouble(node->nodes.at(i)));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::drill_c)
            {
                this->drillNode.setNode(node->nodes.at(i));
                p_drill = nodeValueToDouble(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layers_c)
            {
                this->layersNode.setNode(node->nodes.at(i));
                p_layers = node->nodes.at(i)->Values;
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::net_c)
            {
                this->net.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::tstamp_c)
            {
                this->tstamp.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbPad::QIcadPcbPad(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbPad::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::pad_c)
    {
        this->p_node = node;
        if(p_node->Values.count()>=3)
        {
            if(!this->p_node->Values.at((2)).compare("rect"))
            {
                this->p_shape = rectangle;
            }
            else
                if(!this->p_node->Values.at((2)).compare("circle"))
                {
                    this->p_shape = circle;
                }

        }
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::at_c)
            {
                this->at.setNode(node->nodes.at(i));
                this->p_pos = nodeTo2DCoords(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::size_c)
            {
                this->sizeNode.setNode(node->nodes.at(i));
                this->p_size = nodeTo2DSize(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layers_c)
            {
                this->layer.setNode(node->nodes.at(i));
                this->p_layers = node->nodes.at(i)->Values;
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::net_c)
            {
                this->netNode.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::drill_c)
            {
                this->drillNode.setNode(node->nodes.at(i));
                this->p_drill = nodeValueToDouble(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbFPLine::QIcadPcbFPLine(QIlib::AbstractNode *node)
    :QIcadAbstractPcbLine(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbFPLine::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::fp_line_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::start_c)
            {
                this->p_startpos = nodeTo2DCoords(node->nodes.at(i));
                this->start.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::end_c)
            {
                this->p_stoppos = nodeTo2DCoords(node->nodes.at(i));
                this->end.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->p_layers = node->nodes.at(i)->Values;
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->p_width = nodeValueToDouble(node->nodes.at(i));
                this->width.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbFPCircle::QIcadPcbFPCircle(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbFPCircle::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::fp_circle_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::center_c)
            {
                this->center.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::end_c)
            {
                this->end.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->width.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbText::QIcadPcbText(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbText::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_text_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::at_c)
            {
                this->at.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->width.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::effects_c)
            {
                this->effects.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbCircle::QIcadPcbCircle(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbCircle::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_circle_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::center_c)
            {
                this->center.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::end_c)
            {
                this->end.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->width.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbArc::QIcadPcbArc(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbArc::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::gr_arc_c)
    {
        this->p_node = node;
        for(int i=0;i<node->nodes.count();i++)
        {
            if(node->nodes.at(i)->name==QIlib::Lexique::start_c)
            {
                this->start.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::end_c)
            {
                this->end.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::angle_c)
            {
                this->angle.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::layer_c)
            {
                this->layer.setNode(node->nodes.at(i));
            }
            if(node->nodes.at(i)->name==QIlib::Lexique::width_c)
            {
                this->width.setNode(node->nodes.at(i));
            }
        }
    }
}


QIlib::QIcadPcbZone::QIcadPcbZone(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->setNode(node);
}

void QIlib::QIcadPcbZone::setNode(QIlib::AbstractNode *node)
{
    if(node->name==QIlib::Lexique::zone_c)
    {
        this->p_node = node;
    }
}


const QPointF QIlib::nodeTo2DCoords(QIlib::AbstractNode *node)
{
    QPointF point;
    QStringList coords=node->Values;
    if(coords.count()>=2)
    {
        point.setX(coords.at(0).toDouble());
        point.setY(coords.at(1).toDouble());
    }
    return point;
}


double QIlib::nodeValueToDouble(QIlib::AbstractNode *node, int index)
{
    if(node->Values.count()>index)
    {
        return node->Values.at(index).toDouble();
    }
    return 0.0;
}


int QIlib::nodeValueToInt(QIlib::AbstractNode *node, int index)
{
    if(node->Values.count()>index)
    {
        return node->Values.at(index).toInt();
    }
    return 0;
}


QIlib::QIcadPcbLayer::QIcadPcbLayer(QIlib::AbstractNode *node)
    :QIcadAbstractNodeWrapper(node)
{
    this->p_index = QString(this->p_node->name).remove('(').toInt();
    if(this->p_node->Values.count()>=1)
    {
        this->p_name = this->p_node->Values.at(0);
    }
    if(this->p_node->Values.count()>=2)
    {
        QString typestr=this->p_node->Values.at(1);
        this->p_type = none;
        if(!typestr.compare("signal"))
        {
            this->p_type = signal;
        }
        else
            if(!typestr.compare("user"))
            {
                this->p_type = user;
            }
    }
}


const QSizeF QIlib::nodeTo2DSize(QIlib::AbstractNode *node)
{
    QSizeF size;
    QStringList sz=node->Values;
    if(sz.count()>=2)
    {
        size.setWidth(sz.at(0).toDouble());
        size.setHeight(sz.at(1).toDouble());
    }
    return size;
}
