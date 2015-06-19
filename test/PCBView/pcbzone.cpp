/*------------------------------------------------------------------------------
--  This file is a part of the Kicad Tools Software
--  Copyright (C) 2015, Plasma Physics Laboratory - CNRS
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
#include "pcbzone.h"
#include <QPen>
#include <QPixmapCache>

PCBZone::PCBZone(QIlib::QIcadPcbZone *zoneNode, PCBContext *context)
    :QGraphicsItemGroup(),zoneNode(zoneNode),context(context)
{
    this->init();
}

void PCBZone::init()
{
    this->setFlags(ItemIsMovable|ItemIsSelectable|ItemIsFocusable);
    QPolygonF poly;
    for(int i=0;i<this->zoneNode->filledPolygon.points.points.count();i++)
    {
        poly.append(this->zoneNode->filledPolygon.points.points.at(i)->pos());
    }
    QGraphicsPixmapItem* test=new QGraphicsPixmapItem();
    QPixmap pix;
    QPainter painter;
    QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();
    QPen pen = polygonItem->pen();
    pen.setWidthF(0.01);

    polygonItem->setPen(pen);
    QBrush brush = polygonItem->brush();
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(context->layerColor(this->zoneNode->layer.value()));
    polygonItem->setBrush(brush);
    polygonItem->setZValue(-context->layer(this->zoneNode->layer.value()));
    polygonItem->setPolygon(poly);
    polygonItem->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
//    test->setPixmap(polygonItem->);
    //voir doc/qt/...
//    polygonItem->paint();
    this->addToGroup(polygonItem);

    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setOpacity(0.6);
}
