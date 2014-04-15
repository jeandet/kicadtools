#include <QDir>
#include <QFile>
#include <QApplication>
#include <qicadnetlist.h>
#include <QDebug>
#include <QTime>
/*
#include <lispLike_driver.h>
*/

int main(int argc, char *argv[])
{
    QApplication ap(argc,argv);
    QIlib::QIcadNetList NetListdriver;
    if(argc>1)
    {
        if(QFile::exists(argv[1]))
        {
            QTime tm;
            tm.start();
            NetListdriver.parseNetList(argv[1]);
            qDebug()<<"File parsed in "<<tm.elapsed()<<"ms";
            std::cout<<NetListdriver.print().toStdString();
        }
    }
    return 0;
}
