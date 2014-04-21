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
#ifndef QINET_H
#define QINET_H
#include <QString>
#include <QList>

namespace QIlib{
class QIcadNetNode
{
public:
    QIcadNetNode(QString ref,QString node);
    QString ref(){return this->p_ref;}
    QString node(){return this->p_node;}
private:
    QString p_ref;
    QString p_node;
};

class QIcadNet
{
public:
    QIcadNet();
    ~QIcadNet();
    int code();
    QString name();
private:
    int p_code;
    QString p_name;
    QList<QIcadNetNode*> p_nodes;
};
}
#endif // QINET_H
