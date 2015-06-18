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
#ifndef PCBLINE_H
#define PCBLINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <qicadpcb.h>
#include <pcbcontext.h>

class PCBLine: public QGraphicsLineItem
{
public:
    PCBLine(QIlib::QIcadAbstractPcbLine* lineNode,QPointF offset,PCBContext* context);
    PCBLine(QIlib::QIcadAbstractPcbLine* lineNode,PCBContext* context);
private:
    void init(QPointF offset);
    QIlib::QIcadAbstractPcbLine* lineNode;
    PCBContext* context;
};

#endif // PCBLINE_H
