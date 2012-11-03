#ifndef exp_H
#define exp_H
#include <QObject>
#include <qstack.h>
#include <qmath.h>
#include <QHash>


struct node
{
    node()
    {
        this->L = this->R = NULL ;
        this->operat = NULL ;
    }
    QChar operat ;
    double num;
    node* R ;
    node* L ;
};

class expression
{

public:
    double Resault ;
    node* Root;
    QString sss;
    expression();
    void start();
    expression(QString);

    node* Determine(QString str);
    void AddToTree(node * &T,QString str);
    double Calculate(node *&);
};

#endif // exppppppp_H
