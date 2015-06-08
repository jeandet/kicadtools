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

namespace QIlib{


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

class QIcadPcbFpText : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbFpText(QIlib::AbstractNode* node);
    QIcadPcbFpText(){}
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper layer;
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

class QIcadPcbModule : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbModule(QIlib::AbstractNode* node);
    QIcadPcbModule(){}
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper tedit;
    QIcadAbstractNodeWrapper tstamp;
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper descr;
    QIcadAbstractNodeWrapper tags;
    QIcadAbstractNodeWrapper path;
    QIcadAbstractNodeWrapper attr;
    QList<QIcadAbstractNodeWrapper*> fp_texts;
    QList<QIcadAbstractNodeWrapper*> fp_lines;
    QList<QIcadAbstractNodeWrapper*> pads;
    QIcadPcbModuleModel model;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbSegment : public QIcadAbstractNodeWrapper
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
    QIcadPcbVia(QIlib::AbstractNode* node);
    QIcadPcbVia(){}
    QIcadAbstractNodeWrapper at;
    QIcadAbstractNodeWrapper size;
    QIcadAbstractNodeWrapper drill;
    QIcadAbstractNodeWrapper layer;
    QIcadAbstractNodeWrapper net;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcbLine : public QIcadAbstractNodeWrapper
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

class QIcadPcbLayers : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbLayers(QIlib::AbstractNode* node);
    QIcadPcbLayers(){}
    QList<QIcadAbstractNodeWrapper*> layers;
    void setNode(QIlib::AbstractNode* node);
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
    void setNode(QIlib::AbstractNode* node);
    void clrNets();
    void apendNet(QIlib::AbstractNode* node);
    void setModules(QIlib::AbstractNode* node);
    void apendModules(QIlib::AbstractNode* node);
    void setDimensions(QIlib::AbstractNode* node);
    void apendDimensions(QIlib::AbstractNode* node);
    void setLines(QIlib::AbstractNode* node);
    void apendLines(QIlib::AbstractNode* node);
    void setSegments(QIlib::AbstractNode* node);
    void apendSegments(QIlib::AbstractNode* node);
    void setVias(QIlib::AbstractNode* node);
    void apendVias(QIlib::AbstractNode* node);
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
