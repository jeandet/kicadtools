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

class QIcadPcbRoot : public QIcadAbstractNodeWrapper
{
public:
    QIcadPcbRoot(QIlib::AbstractNode* node);
    QIcadAbstractNodeWrapper version;
    QIcadAbstractNodeWrapper host;
    void setNode(QIlib::AbstractNode* node);
};

class QIcadPcb : private lispLike_Driver
{
public:
    QIcadPcb();
    bool parsePcb(const QString& pcb);
    QString toString();
    QString fileName;
    QString print();
private:
    void updateConcreteTree();
};


}
#endif // QICADPCB_H
