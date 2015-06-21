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
#include "pcbpad.h"
#include <QPen>

PCBPad::PCBPad(QIlib::QIcadPcbPad *padNode, PCBContext *context)
    :QGraphicsItemGroup(),padNode(padNode),context(context)
{
    this->init(QPointF(0.0,0.0));
}



PCBPad::PCBPad(QIlib::QIcadPcbPad *padNode, QPointF offset, PCBContext *context)
    :QGraphicsItemGroup(),padNode(padNode),context(context)
{
    this->init(offset);
}

void PCBPad::init( QPointF offset)
{
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    offset-=QPointF(this->padNode->size().width()/2,this->padNode->size().height()/2);
    if(this->padNode->shape()==QIlib::QIcadPcbPad::rectangle)
    {
        QRectF rec(this->padNode->pos()+offset,this->padNode->size());
        for(int i=0;i<this->padNode->layers().count();i++)
        {
            QGraphicsRectItem* rect = new QGraphicsRectItem();
            rect->setTransformOriginPoint(rec.center());
            QPen pen = rect->pen();
            pen.setWidthF(0.01);
            rect->setPen(pen);
            QBrush brush = rect->brush();
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(context->layerColor(this->padNode->layers().at(i)));
            rect->setBrush(brush);
            rect->setRect(rec);
            rect->setZValue(-context->layer(padNode->layers().at(i)));
            rect->setRotation(padNode->angle());
            this->addToGroup(rect);
        }
        QGraphicsTextItem* text=new QGraphicsTextItem(QString::number(padNode->padNumber()));
        text->setScale(0.01);
        text->setPos(rec.center());
//        text->setTransformOriginPoint(rec.center());
//        text->setRotation(padNode->angle());
        text->setZValue(1);
        this->addToGroup(text);

    }
    if(this->padNode->shape()==QIlib::QIcadPcbPad::circle)
    {
        for(int i=0;i<this->padNode->layers().count();i++)
        {
            QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem();
            QPen pen = ellipse->pen();
            pen.setWidthF(0.01);
            ellipse->setPen(pen);
            QBrush brush = ellipse->brush();
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(context->layerColor(this->padNode->layers().at(i)));
            ellipse->setBrush(brush);
            QRectF rec(this->padNode->pos()+offset,this->padNode->size());
            ellipse->setRect(rec);
            ellipse->setZValue(-context->layer(padNode->layers().at(i)));
            this->addToGroup(ellipse);
        }
    }
    setOpacity(0.6);
}
