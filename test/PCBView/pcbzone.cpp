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
#include "polypartition/src/polypartition.h"


PCBZone::PCBZone(QIlib::QIcadPcbZone *zoneNode, PCBContext *context)
    :QGraphicsItemGroup(),zoneNode(zoneNode),context(context)
{
    this->initQtClipping();
}

void PCBZone::initTriangPolypartition()
{
    TPPLPartition pp;
    this->setFlags(ItemIsMovable|ItemIsSelectable|ItemIsFocusable);
    TPPLPoly test;
    std::list<TPPLPoly> triangles;
    test.Init(this->zoneNode->filledPolygon.points.points.count());
    for(int i=0;i<this->zoneNode->filledPolygon.points.points.count();i++)
    {
        test[i].x =this->zoneNode->filledPolygon.points.points.at(i)->pos().x();
        test[i].y =this->zoneNode->filledPolygon.points.points.at(i)->pos().y();
    }
    pp.Triangulate_OPT(&test,&triangles);
    for(std::list<TPPLPoly>::iterator iter = triangles.begin();iter != triangles.end(); iter++)
    {
        QPolygonF poly;
        TPPLPoly t = *iter;
        for(int i=0;i<t.GetNumPoints();i++)
        {
            poly.append(QPointF(t[i].x,t[i].y));
        }
        QGraphicsPolygonItem* triangleItem = new QGraphicsPolygonItem();
        QPen pen = triangleItem->pen();
        pen.setWidthF(0.05);

        triangleItem->setPen(pen);
        QBrush brush = triangleItem->brush();
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(context->layerColor(this->zoneNode->layer.value()));
        triangleItem->setBrush(brush);
        triangleItem->setZValue(-context->layer(this->zoneNode->layer.value()));
        triangleItem->setPolygon(poly);
        triangleItem->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        this->addToGroup(triangleItem);
    }

    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setOpacity(0.6);
}

void PCBZone::initQtClipping()
{
    this->setFlags(ItemIsMovable|ItemIsSelectable|ItemIsFocusable);
    QPolygonF poly;
    for(int i=0;i<this->zoneNode->filledPolygon.points.points.count();i++)
    {
        QPointF p;
        p.setX(this->zoneNode->filledPolygon.points.points.at(i)->pos().x());
        p.setY(this->zoneNode->filledPolygon.points.points.at(i)->pos().y());
        poly.append(p);
    }
    QList<QPolygonF> clippedPolygons = splitPolygons(poly,100);
    for(int i=0;i<clippedPolygons.count();i++)
    {
        QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();
//        QPen pen = polygonItem->pen();
//        pen.setWidthF(0.01);

        polygonItem->setPen(Qt::NoPen);
//        polygonItem->setPen(pen);
        QBrush brush = polygonItem->brush();
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(context->layerColor(this->zoneNode->layer.value()));
        polygonItem->setBrush(brush);
        polygonItem->setZValue(-context->layer(this->zoneNode->layer.value()));
        polygonItem->setPolygon(clippedPolygons.at(i));
//        polygonItem->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        this->addToGroup(polygonItem);
    }


    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setOpacity(0.6);
}

QPolygonF intersect(QPointF topLeft,QPointF bottomRight,QPolygonF poly)
{
    QPolygonF rect;
    rect.append(topLeft);
    rect.append(QPointF(bottomRight.x(),topLeft.y()));
    rect.append(bottomRight);
    rect.append(QPointF(topLeft.x(),bottomRight.y()));
    return poly.intersected(rect);
}

QList<QPolygonF> PCBZone::splitPolygons(QPolygonF polygon, int maxPoints)
{
    QList<QPolygonF> result;
    if(polygon.size()>maxPoints)
    {
        QRectF brect =  polygon.boundingRect();
        QPointF center = brect.center();
        QPointF centerLeft = QPointF(brect.x(),brect.center().y());
        QPointF centerRight = QPointF(brect.topRight().x(),brect.center().y());
        QPointF topCenter = QPointF(center.x(),brect.topLeft().y());
        QPointF bottomCenter = QPointF(center.x(),brect.bottomLeft().y());
        result.append(splitPolygons(intersect(brect.topLeft(),center,polygon),maxPoints));
        result.append(splitPolygons(intersect(topCenter,centerRight,polygon),maxPoints));
        result.append(splitPolygons(intersect(center,brect.bottomRight(),polygon),maxPoints));
        result.append(splitPolygons(intersect(centerLeft,bottomCenter,polygon),maxPoints));
    }
    else
        result.append(polygon);
    return result;
}
