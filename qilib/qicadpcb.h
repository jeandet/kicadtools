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
#ifndef QICADPCB_H
#define QICADPCB_H
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <parsers/lispLike_driver.h>
#include <qicadlisplikelexique.h>
#include <QPointF>
#include <QRectF>

namespace QIlib{
const QPointF nodeTo2DCoords(QIlib::AbstractNode* node);
const QSizeF nodeTo2DSize(QIlib::AbstractNode* node);
double nodeValueToDouble(QIlib::AbstractNode* node,int index=0);
int nodeValueToInt(QIlib::AbstractNode* node,int index=0);

class QIcadAbstractPcbLine : public QIcadAbstractNodeWrapper
{
public:
    QIcadAbstractPcbLine(QIlib::AbstractNode* node)
        :QIcadAbstractNodeWrapper(node)
    {}
    QIcadAbstractPcbLine(){}
    virtual const QPointF& startPos(){return p_startpos;}
    virtual const QPointF& stopPos(){return p_stoppos;}
    virtual double width(){return p_width;}
    virtual const QStringList& layers(){return p_layers;}
protected:
    double p_width;
    QPointF p_startpos;
    QPointF p_stoppos;
    QStringList p_layers;
};

class QIcadPcbLayer : public QIcadAbstractNodeWrapper
{
public:
    typedef enum
    {
        signal,
        user,
        none
    }layetType_t;
    QIcadPcbLayer(QIlib::AbstractNode* node);
    QIcadPcbLayer(){}
    int index(){return p_index;}
    const QString& name(){return p_name;}
    layetType_t type(){return p_type;}
protected:
    int p_index;
    QString p_name;
    layetType_t p_type;
};

class QIcadPcbPlotParams : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbPlotParams(QIlib::AbstractNode* node);
    QIcadPcbPlotParams(){}
    QIcadAbstractNodeWrapper layerselection;
    QIcadAbstractNodeWrapper usegerberextensions;
    QIcadAbstractNodeWrapper excludeedgelayer;
    QIcadAbstractNodeWrapper linewidth;
    QIcadAbstractNodeWrapper plotframeref;
    QIcadAbstractNodeWrapper viasonmask;
    QIcadAbstractNodeWrapper mode;
    QIcadAbstractNodeWrapper useauxorigin;
    QIcadAbstractNodeWrapper hpglpennumber;
    QIcadAbstractNodeWrapper hpglpenspeed;
    QIcadAbstractNodeWrapper hpglpendiameter;
    QIcadAbstractNodeWrapper hpglpenoverlay;
    QIcadAbstractNodeWrapper psnegative;
    QIcadAbstractNodeWrapper psa4output;
    QIcadAbstractNodeWrapper plotreference;
    QIcadAbstractNodeWrapper plotvalue;
    QIcadAbstractNodeWrapper plotothertext;
    QIcadAbstractNodeWrapper plotinvisibletext;
    QIcadAbstractNodeWrapper padsonsilk;
    QIcadAbstractNodeWrapper subtractmaskfromsilk;
    QIcadAbstractNodeWrapper outputformat;
    QIcadAbstractNodeWrapper mirror;
    QIcadAbstractNodeWrapper drillshape;
    QIcadAbstractNodeWrapper scaleselection;
    QIcadAbstractNodeWrapper outputdirectory;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbSetup : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbSetup(QIlib::AbstractNode* node);
    QIcadPcbSetup(){}
    QIcadAbstractNodeWrapper last_trace_width;
    QIcadAbstractNodeWrapper trace_clearance;
    QIcadAbstractNodeWrapper zone_clearance;
    QIcadAbstractNodeWrapper zone_45_only;
    QIcadAbstractNodeWrapper trace_min;
    QIcadAbstractNodeWrapper segment_width;
    QIcadAbstractNodeWrapper edge_width;
    QIcadAbstractNodeWrapper via_size;
    QIcadAbstractNodeWrapper via_dril;
    QIcadAbstractNodeWrapper via_min_size;
    QIcadAbstractNodeWrapper via_min_drill;
    QIcadAbstractNodeWrapper uvia_size;
    QIcadAbstractNodeWrapper uvia_drill;
    QIcadAbstractNodeWrapper uvias_allowed;
    QIcadAbstractNodeWrapper uvia_min_size;
    QIcadAbstractNodeWrapper uvia_min_drill;
    QIcadAbstractNodeWrapper pcb_text_width;
    QIcadAbstractNodeWrapper pcb_text_size;
    QIcadAbstractNodeWrapper mod_edge_width;
    QIcadAbstractNodeWrapper mod_text_size;
    QIcadAbstractNodeWrapper mod_text_width;
    QIcadAbstractNodeWrapper pad_size;
    QIcadAbstractNodeWrapper pad_drill;
    QIcadAbstractNodeWrapper pad_to_mask_clearance;
    QIcadAbstractNodeWrapper aux_axis_origin;
    QIcadAbstractNodeWrapper visible_elements;
    QIcadPcbPlotParams plotParams;
    void setNode(QIlib::AbstractNode* node);
    double defaultViaDrillSize(){return p_defaultViaDrillSize;}
private:
    double p_defaultViaDrillSize;
};

class QIcadPcbNetClass : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbNetClass(QIlib::AbstractNode* node);
    QIcadPcbNetClass(){}
    QIcadAbstractNodeWrapper clearance;
    QIcadAbstractNodeWrapper trace_width;
    QIcadAbstractNodeWrapper via_dia;
    QIcadAbstractNodeWrapper via_drill;
    QIcadAbstractNodeWrapper uvia_dia;
    QIcadAbstractNodeWrapper uvia_drill;
    QList<QIcadAbstractNodeWrapper*> nets;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbFpTextEffectsFont : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbFpTextEffectsFont(QIlib::AbstractNode* node);
    QIcadAbstractNodeWrapper size;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbFpTextEffects : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbFpTextEffects(QIlib::AbstractNode* node);
    QIcadPcbFpTextEffects(){}
    QIcadAbstractNodeWrapper font;
    QIcadAbstractNodeWrapper thickness;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbFPText : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbFPText(QIlib::AbstractNode* node);
    QIcadPcbFPText(){}
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper layer;
    QIcadPcbFpTextEffects effects;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbModuleModel : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbModuleModel(QIlib::AbstractNode* node);
    QIcadPcbModuleModel(){}
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper scale;
    QIcadAbstractNodeWrapper rotate;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbDimension : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbDimension(QIlib::AbstractNode* node);
    QIcadPcbDimension(){}
    QIcadAbstractNodeWrapper width;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper gr_text;
    QIcadAbstractNodeWrapper feature1;
    QIcadAbstractNodeWrapper feature2;
    QIcadAbstractNodeWrapper crossbar;
    QIcadAbstractNodeWrapper arrow1a;
    QIcadAbstractNodeWrapper arrow1b;
    QIcadAbstractNodeWrapper arrow2a;
    QIcadAbstractNodeWrapper arrow2b;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbPad : public QIcadAbstractNodeWrapper
{
public:
    typedef enum
    {
        rectangle,
        circle
    }padShape;
    QIcadPcbPad(QIlib::AbstractNode* node,double modAngle=0.0);
    QIcadPcbPad(){}
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper sizeNode;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper netNode;
    QIcadAbstractNodeWrapper drillNode;
    const QStringList& layers(){return p_layers;}
    const QSizeF& size(){return p_size;}
    const QPointF& pos(){return p_pos;}
    double drill(){return p_drill;}
    void setModuleAngle(double modAngle){p_Mod_angle= modAngle;}
    double angle(){return  - (p_angle - p_Mod_angle);}
    padShape shape(){return p_shape;}
    int padNumber(){return p_padNumber;}
    void setNode(QIlib::AbstractNode* node);
private:
    int p_padNumber;
    padShape p_shape;
    double p_drill;
    double p_angle;
    // Dirty fix to transform pad angle from
    // PCB coordinates to Module coordinates
    double p_Mod_angle;
    QSizeF p_size;
    QPointF p_pos;
    QStringList p_layers;
};

class QIcadPcbFPLine : public QIcadAbstractPcbLine
{
public:
    QIcadPcbFPLine(QIlib::AbstractNode* node);
    QIcadPcbFPLine(){}
    QIcadAbstractNodeWrapper start;
    QIcadAbstractNodeWrapper end;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper width;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbFPCircle : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbFPCircle(QIlib::AbstractNode* node);
    QIcadPcbFPCircle(){}
    QIcadAbstractNodeWrapper center;
    QIcadAbstractNodeWrapper end;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper width;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbModule : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbModule(QIlib::AbstractNode* node);
    QIcadPcbModule(){}
    const QPointF& pos();
    double angle();
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper tedit;
    QIcadAbstractNodeWrapper tstamp;
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper descr;
    QIcadAbstractNodeWrapper tags;
    QIcadAbstractNodeWrapper path;
    QIcadAbstractNodeWrapper attr;
    QList<QIcadPcbFPText*> fp_texts;
    QList<QIcadPcbFPLine*> fp_lines;
    QList<QIcadPcbFPCircle*> fp_circles;
    QList<QIcadPcbPad*> pads;
    QIcadPcbModuleModel model;
    void setNode(QIlib::AbstractNode* node);
    void clrPads();
    void apendPad(QIlib::AbstractNode* node);
    void clrTexts();
    void apendText(QIlib::AbstractNode* node);
    void clrLines();
    void apendLine(QIlib::AbstractNode* node);
    void clrCircles();
    void apendCircle(QIlib::AbstractNode* node);
private:
    void updatePadsAngle();
    QPointF p_pos;
    double p_angle;
};

class QIcadPcbSegment : public QIcadAbstractPcbLine
{
public:
    QIcadPcbSegment(QIlib::AbstractNode* node);
    QIcadPcbSegment(){}
    QIcadAbstractNodeWrapper start;
    QIcadAbstractNodeWrapper end;
    QIcadAbstractNodeWrapper width;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper net;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbVia : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbVia(QIlib::AbstractNode* node, double defaultDrill=0);
    QIcadPcbVia(){}
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper sizeNode;
    QIcadAbstractNodeWrapper drillNode;
    QIcadAbstractNodeWrapper layersNode;
    QIcadAbstractNodeWrapper net;
    QIcadAbstractNodeWrapper tstamp;
    void setNode(QIlib::AbstractNode* node);
    const QStringList& layers(){return p_layers;}
    const QSizeF& size(){return p_size;}
    const QPointF& pos(){return p_pos;}
    double drill(){return p_drill;}
private:
    double p_drill;
    QSizeF p_size;
    QPointF p_pos;
    QStringList p_layers;
};

class QIcadPcbLine : public QIcadAbstractPcbLine
{
public:
    QIcadPcbLine(QIlib::AbstractNode* node);
    QIcadPcbLine(){}
    QIcadAbstractNodeWrapper start;
    QIcadAbstractNodeWrapper end;
    QIcadAbstractNodeWrapper angle;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper width;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbZone : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbZone(QIlib::AbstractNode* node);
    QIcadPcbZone(){}
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbArc : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbArc(QIlib::AbstractNode* node);
    QIcadPcbArc(){}
    QIcadAbstractNodeWrapper start;
    QIcadAbstractNodeWrapper end;
    QIcadAbstractNodeWrapper angle;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper width;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbCircle : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbCircle(QIlib::AbstractNode* node);
    QIcadPcbCircle(){}
    QIcadAbstractNodeWrapper center;
    QIcadAbstractNodeWrapper end;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper width;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbText : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbText(QIlib::AbstractNode* node);
    QIcadPcbText(){}
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper width;
    QIcadPcbFpTextEffects effects;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbLayers : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbLayers(QIlib::AbstractNode* node);
    QIcadPcbLayers(){}
    QList<QIcadPcbLayer*> layers;
    void setNode(QIlib::AbstractNode* node);
    void clrLayers();
    void apendLayer(QIlib::AbstractNode* node);
};

class QIcadPcbGeneralInfo : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbGeneralInfo(QIlib::AbstractNode* node);
    QIcadPcbGeneralInfo(){}
    QIcadAbstractNodeWrapper links;
    QIcadAbstractNodeWrapper no_connections;
    QIcadAbstractNodeWrapper area;
    QIcadAbstractNodeWrapper thickness;
    QIcadAbstractNodeWrapper drawings;
    QIcadAbstractNodeWrapper tracks;
    QIcadAbstractNodeWrapper zones;
    QIcadAbstractNodeWrapper modules;
    QIcadAbstractNodeWrapper nets;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbRoot : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbRoot(QIlib::AbstractNode* node);
    QIcadAbstractNodeWrapper version;
    QIcadAbstractNodeWrapper host;
    QIcadAbstractNodeWrapper page;
    QIcadPcbGeneralInfo general;
    QIcadPcbLayers layers;
    QIcadPcbSetup setup;
    QList<QIcadAbstractNodeWrapper*> nets;
    QList<QIcadPcbModule*> modules;
    QList<QIcadPcbDimension*> dimensions;
    QList<QIcadPcbLine*> lines;
    QList<QIcadPcbSegment*> segments;
    QList<QIcadPcbVia*> vias;
    QList<QIcadPcbArc*> arcs;
    QList<QIcadPcbCircle*> circles;
    QList<QIcadPcbText*> texts;
    QList<QIcadPcbZone*> zones;
    void setNode(QIlib::AbstractNode* node);
    void clrNets();
    void apendNet(QIlib::AbstractNode* node);
    void clrModules();
    void apendModule(QIlib::AbstractNode* node);
    void clrDimensions();
    void apendDimension(QIlib::AbstractNode* node);
    void apendLine(QIlib::AbstractNode* node);
    void clrLines();
    void clrSegments();
    void apendSegment(QIlib::AbstractNode* node);
    void clrVias();
    void apendVia(QIlib::AbstractNode* node);
    void clrArcs();
    void apendArc(QIlib::AbstractNode* node);
    void clrCircles();
    void apendCircle(QIlib::AbstractNode* node);
    void clrTexts();
    void apendText(QIlib::AbstractNode* node);
    void clrZones();
    void apendZone(QIlib::AbstractNode* node);
};

class QIcadPcb : private lispLike_Driver
{
public:
    QIcadPcb();
    bool parsePcb(const QString& pcb);
    QString toString();
    QString fileName;
    QString print();

    QIcadPcbRoot* pcbRoot;
private:
    void updateConcreteTree();
};


}
#endif // QICADPCB_H
