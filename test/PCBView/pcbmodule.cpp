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
#include "pcbmodule.h"
#include "pcbline.h"
#include "pcbrectpad.h"

PCBModule::PCBModule(QIlib::QIcadPcbModule *moduleNode, PCBContext *context)
    :QGraphicsItemGroup(),context(context)
{
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    this->setFlags(ItemIsMovable|ItemIsSelectable|ItemIsFocusable);
//    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
//    this->addToGroup(new QGraphicsRectItem(0,0,2,2));
    this->setPos(moduleNode->pos());
    for(int i=0;i<moduleNode->fp_lines.count();i++)
    {
        this->addToGroup(new PCBLine((QIlib::QIcadAbstractPcbLine*)moduleNode->fp_lines.at(i),moduleNode->pos(),context));
    }
    for(int i=0;i<moduleNode->pads.count();i++)
    {
        this->addToGroup(new PCBRectPad((QIlib::QIcadPcbPad*)moduleNode->pads.at(i),moduleNode->pos(),context));
    }
    this->setRotation(moduleNode->angle());
}

