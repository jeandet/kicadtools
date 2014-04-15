#ifndef LISPLIKE_DRIVER_H
#define LISPLIKE_DRIVER_H
#include <string>
#include "lispLike_scanner.h"
#include <lispLike/lispLike.hpp>
#include <QString>
#include <QList>
#include <QStringList>
#include <iostream>
#include <cstdlib>
#include <fstream>

namespace QIlib{

class AbstractNode
{
public:
    AbstractNode( QIlib::AbstractNode* parent=NULL);
    AbstractNode(const QString& Name, QIlib::AbstractNode* parent=NULL);
    AbstractNode(const QString& Name,const QString& Value, QIlib::AbstractNode* parent=NULL);
    QString print();
    QList<QIlib::AbstractNode*> nodes;
    QString name;
    QStringList Values;
    QIlib::AbstractNode* parent;
};

class lispLike_Driver
{
public:
    lispLike_Driver();

    virtual ~lispLike_Driver();
    bool parse( const char *filename );
    void add_node( const QString &node );
    void add_node( const QString &node , const QString &value);
    void add_value( const QString &value );
    void close_node();


protected:

    QIlib::lispLike_Parser *parser;
    QIlib::lispLike_Scanner *scanner;
    QIlib::AbstractNode rootNode;
    QIlib::AbstractNode* currentNode;
};
}
#endif // LISPLIKE_DRIVER_H
