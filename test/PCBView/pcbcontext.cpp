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
#include "pcbcontext.h"

Qt::GlobalColor Colours[]= {
    Qt::red,
    Qt::blue,
    Qt::black,
    Qt::green,
    Qt::darkGreen,
    Qt::cyan,
    Qt::darkRed,
    Qt::gray,
    Qt::yellow,
    Qt::darkBlue,
    Qt::darkCyan,
    Qt::magenta,
    Qt::darkMagenta,
    Qt::darkYellow,
    Qt::darkGray,
    Qt::lightGray
};

PCBContext::PCBContext(QObject *parent) : QObject(parent)
{

}

void PCBContext::addlayer(const QString &name, int number)
{
    this->layers_map[name]=number;
    layers_colors[number] = Colours[number%15];
}

int PCBContext::layer(const QString &name)
{
    return layers_map[name];
}

const QColor &PCBContext::layerColor(const QString &name)
{
    return layers_colors[layers_map[name]];
}

const QColor &PCBContext::layerColor(int number)
{
    return layers_colors[number];
}

const QString PCBContext::layer(int number)
{
    return layers_map.key(number);
}

void PCBContext::clear()
{
    this->layers_colors.clear();
    this->layers_map.clear();
}

