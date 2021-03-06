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
#include "pcbmodule.h"
#include "pcbline.h"
#include "pcbvia.h"
#include "pcbzone.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->p_scene = new QGraphicsScene();
    //    this->p_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->context = new PCBContext();
    this->ui->graphicsView->setScene(this->p_scene);
    this->pcbDriver =NULL;
    connect(this->ui->actionRedraw,SIGNAL(triggered(bool)),this,SLOT(redraw()));
    connect(this->ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redraw()
{
    this->p_scene->update();
}

void MainWindow::openFile()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Open kicad PCB file"),
                                                "",
                                                tr("PCB file (*.kicad_pcb)"));
    if(QFile::exists(file))
        loadFile(file);
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

void MainWindow::loadFile(const QString &file)
{
    this->p_scene->setSceneRect(0, 0, 500, 200);
    if(pcbDriver!=NULL)delete pcbDriver;
    pcbDriver = new QIlib::QIcadPcb();
    this->context->clear();
    this->p_scene->clear();
    pcbDriver->parsePcb(file);
    for(int i=0;i<pcbDriver->pcbRoot->layers.layers.count();i++)
    {
        this->context->addlayer(pcbDriver->pcbRoot->layers.layers.at(i)->name(),pcbDriver->pcbRoot->layers.layers.at(i)->index());
    }
#pragma omp parallel for
    for(int i=0;i<pcbDriver->pcbRoot->modules.count();i++)
    {
        PCBModule* module = new PCBModule(pcbDriver->pcbRoot->modules.at(i),this->context);
#pragma omp critical
        this->p_scene->addItem(module);
    }
#pragma omp parallel for
    for(int i=0;i<pcbDriver->pcbRoot->lines.count();i++)
    {
        PCBLine* line=new PCBLine((QIlib::QIcadAbstractPcbLine*)pcbDriver->pcbRoot->lines.at(i),this->context);
#pragma omp critical
        this->p_scene->addItem(line);
    }
#pragma omp parallel for
    for(int i=0;i<pcbDriver->pcbRoot->segments.count();i++)
    {
        PCBLine* line=new PCBLine((QIlib::QIcadAbstractPcbLine*)pcbDriver->pcbRoot->segments.at(i),this->context);
#pragma omp critical
        this->p_scene->addItem(line);
    }
#pragma omp parallel for
    for(int i=0;i<pcbDriver->pcbRoot->vias.count();i++)
    {
        PCBVia* via =new PCBVia(pcbDriver->pcbRoot->vias.at(i),this->context);
#pragma omp critical
        this->p_scene->addItem(via);
    }
#pragma omp parallel for
    for(int i=0;i<pcbDriver->pcbRoot->zones.count();i++)
    {
        PCBZone* zone=new PCBZone(pcbDriver->pcbRoot->zones.at(i),this->context);
#pragma omp critical
        this->p_scene->addItem(zone);
    }
}
