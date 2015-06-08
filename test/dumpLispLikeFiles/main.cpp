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
#include <QDir>
#include <QFile>
#include <QApplication>
#include <qicadnetlist.h>
#include <qicadpcb.h>
#include <QDebug>
#include <QTime>
/*
#include <lispLike_driver.h>
*/

int main(int argc, char *argv[])
{
    QApplication ap(argc,argv);
    if(argc>1)
    {
        if(QFile::exists(argv[1]))
        {
            QTime tm;
            if(ap.arguments().contains("--netList"))
            {
                QIlib::QIcadNetList NetListdriver;
                tm.start();
                NetListdriver.parseNetList(argv[1]);
                std::cout<<"File parsed in "<<tm.elapsed()<<"ms\n";
                if(ap.arguments().contains("--print"))
                {
                    std::cout<<NetListdriver.print().toStdString();
                }
                else
                {
                    for(int i=0;i<NetListdriver.netlistRoot->nets.count();i++)
                    {
                        std::cout<<"Found net:"<<NetListdriver.netlistRoot->nets.at(i)->name.value().toStdString()<<" "<<NetListdriver.netlistRoot->nets.at(i)->code.value().toStdString()<<"\n";
                    }
                }
            }
            else
            {
                QIlib::QIcadPcb pcbDriver;
                tm.start();
                pcbDriver.parsePcb(argv[1]);
                std::cout<<"File parsed in "<<tm.elapsed()<<"ms\n";
                if(ap.arguments().contains("--print"))
                {
                    std::cout<<pcbDriver.print().toStdString();
                }
                else
                {
//                    for(int i=0;i<NetListdriver.netlistRoot->nets.count();i++)
//                    {
//                        std::cout<<"Found net:"<<NetListdriver.netlistRoot->nets.at(i)->name.value().toStdString()<<" "<<NetListdriver.netlistRoot->nets.at(i)->code.value().toStdString()<<"\n";
//                    }
                }
            }
        }

    }
    return 0;
}
