/*Mainly copied from http://research.engineering.wustl.edu/~beardj/FlexBisonC++.html*/
#include "lispLike_driver.h"
#include<assert.h>

QIlib::lispLike_Driver::lispLike_Driver()
    :parser( NULL ),scanner( NULL )
{
    currentNode = &rootNode;
}

QIlib::lispLike_Driver::~lispLike_Driver()
{
    delete(scanner);
    scanner = NULL;
    delete(parser);
    parser = NULL;
}

bool QIlib::lispLike_Driver::parse(const char *filename)
{
    if(filename!=NULL)
    {
        std::ifstream in_file( filename );
        if( ! in_file.good() ) return false;

        delete(scanner);
        try
        {
            scanner = new QIlib::lispLike_Scanner( &in_file );
        }
        catch( std::bad_alloc &ba )
        {
            std::cerr << "Failed to allocate scanner: (" <<
                         ba.what() << ")\n";
            return false;
        }

        delete(parser);
        try
        {
            parser = new QIlib::lispLike_Parser( (*scanner) /* scanner */,
                                                 (*this) /* driver */ );
        }
        catch( std::bad_alloc &ba )
        {
            std::cerr << "Failed to allocate parser: (" <<
                         ba.what() << ")\n";
            return false;
        }
        const int accept( 0 );
        if( parser->parse() != accept )
        {
            std::cerr << "Parse failed!!\n";
            return false;
        }
        return true;
    }
    return false;
}

void QIlib::lispLike_Driver::add_node(const QString &node)
{
    QIlib::AbstractNode* newNode = new  QIlib::AbstractNode(node,currentNode);
    currentNode = newNode;
}

void QIlib::lispLike_Driver::add_node(const QString &node, const QString &value)
{
    QIlib::AbstractNode* newNode = new  QIlib::AbstractNode(node,value,currentNode);
    currentNode = newNode;
}

void QIlib::lispLike_Driver::add_value(const QString &value)
{
    currentNode->Values.append(value);
}

void QIlib::lispLike_Driver::close_node()
{
    if(currentNode->parent)
        currentNode = currentNode->parent;
}










QIlib::AbstractNode::AbstractNode(QIlib::AbstractNode *parent)
{
    this->parent =parent;
    if(parent)
        parent->nodes.append(this);
}


QIlib::AbstractNode::AbstractNode(const QString &Name, QIlib::AbstractNode *parent)
    :name(Name)
{
    this->parent = parent;
    if(parent)
        parent->nodes.append(this);
}


QIlib::AbstractNode::AbstractNode(const QString &Name, const QString &Value, QIlib::AbstractNode *parent)
    :name(Name)
{
    this->parent = parent;
    if(parent)
        parent->nodes.append(this);
    Values.append(Value);
}

QString QIlib::AbstractNode::print()
{
    QString result;
    result.append(this->name+" ");
    for(int i=0;i<this->nodes.count();i++)
    {
        result.append(this->nodes.at(i)->print());
    }
    for(int i=0;i<this->Values.count();i++)
    {
        result.append(Values.at(i)+" ");
    }
    result.append(")");
    return result;
}
