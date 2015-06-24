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
#include "polygonssplit.h"

PolygonsSplit::PolygonsSplit()
{

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

QList<QPolygonF> PolygonsSplit::splitPolygons(QPolygonF polygon, int maxPoints, int recursive)
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
        QRectF rects[4];
        QList<QPolygonF> polygons[4];
        rects[0]=QRectF(brect.topLeft(),center);
        rects[1]=QRectF(topCenter,centerRight);
        rects[2]=QRectF(center,brect.bottomRight());
        rects[3]=QRectF(centerLeft,bottomCenter);
        #pragma omp parallel for if ((recursive > 0))  shared(polygons,polygon,rects,maxPoints)
        for(int i=0;i<4;i++)
            polygons[i]=splitPolygons(polygon.intersected(rects[i]),maxPoints,recursive-1);

        for(int i=0;i<4;i++)
            result.append(polygons[i]);
    }
    else
        result.append(polygon);
    return result;
}
