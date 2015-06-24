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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void runTest();
    void runTestTimeVsEdgeCount();
    void runTestTimeVsPolygonsCountVsclipped();
    void runTestTimeVsPolygonsCount(bool clipped=false);
    void runTestTimeVsPolygonsCount_clipped();
protected:
    void changeEvent(QEvent *e);

private:
    int getEdgeCount(const QString& fileName);
    void clearGraphs();
    QCPDataMap *runTestTimeVsPolygonsCount(const QString& file, double opacity=1.0, bool partitionnePoly=false, QColor color=Qt::blue);
    void forceSceneRepaint();
    double drawingTime();
    QPolygonF buildPolygon(int edgesCount);
    void addPoly(int polyCount,int edgesCount,bool uniquePolygon=true);
    void addPoly(const QPolygonF& polygon,int polyCount);
    Ui::MainWindow *ui;
    QGraphicsScene* p_scene;
};

#endif // MAINWINDOW_H
