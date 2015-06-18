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
#include "pcbline.h"
#include <QPen>

PCBLine::PCBLine(QIlib::QIcadAbstractPcbLine *lineNode, QPointF offset,PCBContext* context)
    :lineNode(lineNode),context(context)
{
    init(offset);
}

PCBLine::PCBLine(QIlib::QIcadAbstractPcbLine *lineNode, PCBContext *context)
    :lineNode(lineNode),context(context)
{
    init(QPointF(0,0));
}

void PCBLine::init(QPointF offset)
{
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    this->setFlags(ItemIsMovable|ItemIsSelectable|ItemIsFocusable);
    QPointF startPos=(offset+lineNode->startPos());
    QPointF stopPos=(offset+lineNode->stopPos());
    this->setLine(startPos.x(),startPos.y(),stopPos.x(),stopPos.y());
    QPen pen = this->pen();
    pen.setWidthF(lineNode->width());
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(context->layerColor(lineNode->layers().first()));
    this->setZValue(-context->layer(lineNode->layers().first()));
    this->setPen(pen);
    setOpacity(0.6);
}
