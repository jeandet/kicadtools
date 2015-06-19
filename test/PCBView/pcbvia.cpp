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
#include "pcbvia.h"
#include <QPen>


PCBVia::PCBVia(QIlib::QIcadPcbVia *viaNode, PCBContext *context)
    :QGraphicsItemGroup(),viaNode(viaNode),context(context)
{
    this->init(QPointF(0.0,0.0));
}

PCBVia::PCBVia(QIlib::QIcadPcbVia *viaNode, QPointF offset, PCBContext *context)
    :QGraphicsItemGroup(),viaNode(viaNode),context(context)
{
    this->init(offset);
}

void PCBVia::init(QPointF offset)
{
    this->path.addEllipse(this->viaNode->pos(),this->viaNode->size().width()/2,this->viaNode->size().height()/2);
    double thickness = (this->viaNode->size().width()-this->viaNode->drill())/2;
    this->path.addEllipse(this->viaNode->pos(),(this->viaNode->size().width()/2)-thickness,(this->viaNode->size().height()/2)-thickness);
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    this->setFlags(ItemIsMovable|ItemIsSelectable|ItemIsFocusable);
    offset-=QPointF(this->viaNode->size().width()/2,this->viaNode->size().height()/2);

    for(int i=0;i<this->viaNode->layers().count();i++)
    {
        QGraphicsPathItem* pathitem = new QGraphicsPathItem();
        QPen pen = pathitem->pen();
        pen.setWidthF(0.01);

        pathitem->setPen(pen);
        QBrush brush = pathitem->brush();
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(context->layerColor(this->viaNode->layers().at(i)));
        pathitem->setBrush(brush);
//        QRectF rec(this->viaNode->pos()+offset,QSizeF(this->viaNode->size().width()-thickness,this->viaNode->size().width()-thickness));
//        pathitem->setRect(rec);
        pathitem->setZValue(-context->layer(viaNode->layers().at(i)));
        pathitem->setPath(path);
        this->addToGroup(pathitem);
    }

    setOpacity(0.6);
}
