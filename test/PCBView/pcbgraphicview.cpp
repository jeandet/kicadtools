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
#include "pcbgraphicview.h"

#include <math.h>
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QPixmapCache>

PCBGraphicView::PCBGraphicView(QWidget *parent)
    :QGraphicsView(parent)
{
    this->setRenderHint(QPainter::Antialiasing, true);
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setTransformationAnchor(AnchorUnderMouse);
    this->scale(qreal(0.8), qreal(0.8));
    this->setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    this->setViewport(new QOpenGLWidget());
    QPixmapCache::setCacheLimit(1024*1024*4);
    this->ctrl_pressed = false;
    this->shift_pressed = false;
}


void PCBGraphicView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Shift:
        this->shift_pressed = true;
        break;
    case Qt::Key_Control:
        this->ctrl_pressed = true;
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void PCBGraphicView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        this->shift_pressed = false;
        break;
    case Qt::Key_Control:
        this->ctrl_pressed = false;
        break;
    default:
        QGraphicsView::keyReleaseEvent(event);
    }
}

void PCBGraphicView::wheelEvent(QWheelEvent *event)
{
        if (event->modifiers() & Qt::ControlModifier)
        {
            event->accept();
            if (event->orientation()== Qt::Vertical)
                scaleView(pow((double)2, event->delta() / 240.0));
        }
        else
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                event->accept();
                QWheelEvent* tempevent = new QWheelEvent(event->pos(),(event->delta()/10),event->buttons(),event->modifiers(),Qt::Horizontal);
                QGraphicsView::wheelEvent(tempevent);
            }
            else
                QGraphicsView::wheelEvent(event);
        }
}



void PCBGraphicView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 20, 20, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 20, sceneRect.bottom(), sceneRect.width(), 20);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}


void PCBGraphicView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.02 || factor > 1000)
        return;
    scale(scaleFactor, scaleFactor);
}


void PCBGraphicView::zoomIn()
{
    scaleView(qreal(1.2));
}

void PCBGraphicView::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
