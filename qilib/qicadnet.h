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
