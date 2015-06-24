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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygon.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QTextStream>
#include <qcustomplot.h>
#include <QBrush>
#include "samplepolygons.h"
#include <polygonssplit.h>

QMap<QString, QList<QPolygonF> > clippedCache;

const QList<QString> files =
        QList<QString>()
        << ":/polygons/polygon1.txt"
        << ":/polygons/polygon2.txt"
        << ":/polygons/polygon3.txt"
        << ":/polygons/polygon4.txt"
        << ":/polygons/polygon5.txt"
        << ":/polygons/polygon6.txt"
        << ":/polygons/polygon7.txt"
        << ":/polygons/polygon8.txt"
        << ":/polygons/polygon9.txt"
        << ":/polygons/polygon10.txt"
        << ":/polygons/polygon11.txt"
        << ":/polygons/polygon12.txt"
        << ":/polygons/polygon13.txt"
        << ":/polygons/polygon14.txt"
        << ":/polygons/polygon15.txt"
        << ":/polygons/polygon16.txt"
        << ":/polygons/polygon17.txt"
        << ":/polygons/polygon18.txt"
        << ":/polygons/polygon19.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->p_scene = new QGraphicsScene();
    this->ui->graphicsView->setScene(this->p_scene);
    this->p_scene->setSceneRect(0, 0, 500, 200);
    connect(this->ui->actionTest1,SIGNAL(triggered(bool)),this,SLOT(runTest()));
    connect(this->ui->actionRunTestTimeVsPolygonsCount,SIGNAL(triggered(bool)),this,SLOT(runTestTimeVsPolygonsCount()));
    connect(this->ui->actionT_imeVsPolygonsCount_Clipped,SIGNAL(triggered(bool)),this,SLOT(runTestTimeVsPolygonsCount_clipped()));
    connect(this->ui->actionT_imeVsPolygonsCountVsClipped,SIGNAL(triggered(bool)),this,SLOT(runTestTimeVsPolygonsCountVsclipped()));
    this->ui->plot->addGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runTest()
{
    QElapsedTimer tim;
    this->ui->plot->graph()->clearData();
    for(int i=4;i<200;i+=2)
    {
        QPolygonF poly = buildPolygon(i);
        tim.restart();
        this->p_scene->clear();
        this->addPoly(poly,100);
        this->p_scene->update();
        this->ui->graphicsView->repaint();
        QApplication::processEvents();
        this->ui->graphicsView->scaleView(1.2);
        this->ui->graphicsView->repaint();
        QApplication::processEvents();
        this->ui->graphicsView->scaleView(1.0/1.2);
        this->ui->graphicsView->repaint();
        QApplication::processEvents();
        double elapsed = tim.elapsed();
        QTextStream(stdout) <<"i = " << i << " " << elapsed << endl;
        this->ui->plot->graph()->addData(i,elapsed);
    }
    this->ui->plot->rescaleAxes();
}

void MainWindow::runTestTimeVsEdgeCount()
{

}

void MainWindow::runTestTimeVsPolygonsCountVsclipped()
{
    clearGraphs();
    for(int i=4;i<5;i++)
    {
        this->ui->plot->addGraph();
        int numEdges = getEdgeCount(files.at(i));
        QCPDataMap *data = runTestTimeVsPolygonsCount(files.at(i),0.7,false,Qt::red);
        this->ui->plot->graph()->setData(data);
        this->ui->plot->graph()->setName(files.at(i)+"("+QString::number(numEdges)+"edges)");
        this->ui->plot->graph()->setPen(QPen(QColor(Qt::red)));
        numEdges = getEdgeCount(files.at(i));
        this->ui->plot->addGraph();
        data = runTestTimeVsPolygonsCount(files.at(i),0.7,true,Qt::blue);
        this->ui->plot->graph()->setData(data);
        this->ui->plot->graph()->setName(files.at(i)+"("+QString::number(numEdges)+"edges)");
        this->ui->plot->graph()->setPen(QPen(QColor(Qt::blue)));
    }
    this->ui->plot->rescaleAxes();
    this->ui->plot2->rescaleAxes();
}

void MainWindow::runTestTimeVsPolygonsCount(bool clipped)
{
    clearGraphs();
    this->ui->plot2->addGraph();
    for(int i=0;i<files.count();i++)
    {
        this->ui->plot->addGraph();
        int numEdges = getEdgeCount(files.at(i));
        QCPDataMap *data = runTestTimeVsPolygonsCount(files.at(i),0.7,clipped);
        this->ui->plot->graph()->setData(data);
        this->ui->plot->graph()->setName(files.at(i)+"("+QString::number(numEdges)+"edges)");
        this->ui->plot->graph()->setPen(QPen(QColor(i*256/files.count(),100,files.count()*256/(i+1))));
        int iter=0;
        double time=0.0;
        QCPDataMapIterator it(*data);
        while (it.hasNext())
        {
            it.next();
            iter+=  it.value().key;
            time+= it.value().value;
        }
        this->ui->plot2->graph()->addData(numEdges,time/iter);
    }
    this->ui->plot->rescaleAxes();
    this->ui->plot2->rescaleAxes();
}

void MainWindow::runTestTimeVsPolygonsCount_clipped()
{
    runTestTimeVsPolygonsCount(true);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

int MainWindow::getEdgeCount(const QString &fileName)
{
    int lc=0;
    if(QFile::exists(fileName))
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        if(file.isOpen())
        {
            while (!file.atEnd())
            {
                file.readLine();
                lc++;
            }
        }
    }
    return lc;
}

void MainWindow::clearGraphs()
{
    while (this->ui->plot->graphCount())
    {
        this->ui->plot->removeGraph(0);
    }
    while (this->ui->plot2->graphCount())
    {
        this->ui->plot2->removeGraph(0);
    }
}

QCPDataMap * MainWindow::runTestTimeVsPolygonsCount(const QString &file,double opacity,bool partitionnePoly,QColor color)
{
    QCPDataMap *data = new QCPDataMap();
    this->ui->plot->graph()->clearData();
    QPolygonF poly = loadFromFile(file);
    this->p_scene->clear();
    for(int i=1;i<50;i+=2)
    {
        QGraphicsItem* item;
        if(partitionnePoly)
        {
            item = new QGraphicsItemGroup();
            QList<QPolygonF> clippedPolygons;
            if(!clippedCache.contains(file))
            {
                clippedPolygons = PolygonsSplit::splitPolygons(poly,100,5);
                clippedCache[file] = clippedPolygons;
            }
            else
            {
                clippedPolygons = clippedCache[file];
            }
            for(int l=0;l<clippedPolygons.count();l++)
            {
                QGraphicsPolygonItem * subitem = new QGraphicsPolygonItem(clippedPolygons.at(l));
                QBrush brush = subitem->brush();
                brush.setColor(color);
                brush.setStyle(Qt::SolidPattern);
                subitem->setBrush(brush);
                //                QPen pen = subitem->pen();
                //                pen.setWidthF(0.05);
                subitem->setPen(Qt::NoPen);
                ((QGraphicsItemGroup*)item)->addToGroup(subitem);
            }
        }
        else
        {
            item = new QGraphicsPolygonItem(poly);
            QBrush brush = ((QGraphicsPolygonItem*)item)->brush();
            brush.setColor(color);
            brush.setStyle(Qt::SolidPattern);
            ((QGraphicsPolygonItem*)item)->setBrush(brush);
            QPen pen = ((QGraphicsPolygonItem*)item)->pen();
            pen.setWidthF(0.05);
            ((QGraphicsPolygonItem*)item)->setPen(pen);
        }
        item->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsFocusable);
        item->setZValue(i);
        item->setOpacity(opacity);
        item->moveBy(((double)rand())*(50)/INT_MAX,((double)rand())*(50)/INT_MAX);
        this->p_scene->addItem(item);
        double elapsed = drawingTime();
        (*data)[i] = QCPData(i,elapsed);
    }
    return data;
}

void MainWindow::forceSceneRepaint()
{
    this->p_scene->update();
    this->ui->graphicsView->repaint();
    QApplication::processEvents();
}

double MainWindow::drawingTime()
{
    QElapsedTimer tim;
    tim.start();
    this->ui->graphicsView->scaleView(1.2);
    this->forceSceneRepaint();
    this->ui->graphicsView->scaleView(1.0/1.2);
    this->forceSceneRepaint();
    return tim.elapsed();
}

QPolygonF MainWindow::buildPolygon(int edgesCount)
{
    return TestPolygon(this->p_scene->sceneRect(),edgesCount).polygon();
}

void MainWindow::addPoly(int polyCount, int edgesCount, bool uniquePolygon)
{
    if(uniquePolygon)
    {
        TestPolygon* poly = new TestPolygon(this->p_scene->sceneRect(),edgesCount);
        for(int i=0;i<polyCount;i++)
        {
            QPointF point =QPointF(((double)rand())*(this->p_scene->sceneRect().width())/INT_MAX,((double)rand())*(this->p_scene->sceneRect().height())/INT_MAX);
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(poly->polygon().translated(point));
            QBrush brush = item->brush();
            brush.setColor(Qt::blue);
            brush.setStyle(Qt::SolidPattern);
            item->setBrush(brush);
            QPen pen = item->pen();
            pen.setWidthF(0.05);
            item->setPen(pen);
            this->p_scene->addItem(item);
        }
        delete poly;
    }
    else
    {
        for(int i=0;i<polyCount;i++)
        {
            this->p_scene->addItem(new TestPolygon(this->p_scene->sceneRect(),edgesCount));
        }
    }
}

void MainWindow::addPoly(const QPolygonF &polygon, int polyCount)
{
    for(int i=0;i<polyCount;i++)
    {
        QPointF point =QPointF(((double)rand())*(this->p_scene->sceneRect().width())/INT_MAX,((double)rand())*(this->p_scene->sceneRect().height())/INT_MAX);
        QGraphicsPolygonItem* item = new QGraphicsPolygonItem(polygon.translated(point));
        QBrush brush = item->brush();
        brush.setColor(Qt::blue);
        brush.setStyle(Qt::SolidPattern);
        item->setBrush(brush);
        QPen pen = item->pen();
        pen.setWidthF(0.05);
        item->setPen(pen);
        this->p_scene->addItem(new QGraphicsPolygonItem(polygon.translated(point)));
    }
}
