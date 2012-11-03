#include "exp.h"
expression::expression()
{
    this->Root = NULL;
}

expression::expression(QString str)
{
    QString strr ="5+19";
    Root = new node;
    if (sss!= "")
       AddToTree(this->Root,sss);
    this->Resault = Calculate(Root);
}

void expression::start()
{
    QString strr ="5+19";
    Root = new node;
    if (sss!= "")
       AddToTree(this->Root,sss);
    this->Resault = Calculate(Root);
}

node* expression::Determine(QString str)
{
    node* resault = new node;
    resault->num = 1 ;
    resault->operat = NULL;
    node * internal ;
    QString tempnum ="";
    QString temp = "" ;
    QString tempchar ="" ;
    bool editcon =false ;
    for (int j =0;j<str.length();j++)
    {
        while ( (j<str.length())&&(str[j].isDigit()||(str[j]=='.')||(str[j]=='-')||(str[j]=='+') ))
        {
            editcon = true ;
            tempnum+=str[j];
            j++;
        }
        if (editcon)
        {
            editcon = false ;
            if (tempnum=="-") //for -sin
                resault->num *=-1 ;
            else if (tempnum!="+") //for +sin
                resault->num=tempnum.toDouble() ;
            tempnum="";
        }
        if (j<str.length())
        {
            tempchar = "" ;
            while ( ((str[j]!='(')&&(!str[j].isDigit())&&(str[j]!='*')&&(str[j]!='/')&&(str[j]!='-')&&(str[j]!='+')&&(str[j]!='.'))&&((j<str.length()) ) ) //for const varible
            {
                tempchar +=str[j];
                j++ ;
            }

            if (str[j]=='(') //for sin (....)  or  x^2 ;
            {
                j++; //for ( ;
                while (j!=str.length()-1)
                {
                    temp+=str[j];
                    j++;
                }
                AddToTree(internal,temp);
                if (tempchar == "sin")
                    resault->num = sin(Calculate(internal));
                else
                    resault->num = cos(Calculate(internal));
            } // for processing the poly internal function ex.sin(...)
        }
     } // finish main for

    return resault ;
 } //finish all function



double expression::Calculate (node * & T)
{
    if ( (T->R!=NULL)&&(T->L!=NULL) ) // for print the poly in case infix ;
    {
        switch (T->operat.cell())
        {
        case '+': return Calculate(T->L )+ Calculate(T->R );
            break;
        case '-': return Calculate(T->L )- Calculate(T->R );
            break;
        case '*': return Calculate(T->L )* Calculate(T->R );
            break;
        case '/': return Calculate(T->L )/ Calculate(T->R );
            break;
        }//finish the switch
    }
    else
        return T->num;

} //finish the all function ;


void expression::AddToTree( node *&T ,QString str) // return poly* >>> root tree >> expppppppen .
   {
       QStack <QChar> s_op ;
       QStack <node*> s_func;
       bool internal=false ,internal2  = false ;
       QString temp ="";
       node* T2 = 0;
       for (int i=0 ; i<str.length();i++)
       {
           if ((str[i]=='+')||(str[i]=='-'))
           {
               if (internal) //for operat internal funtion
                   temp+=str[i];
               else
               {
                   if( ((temp=="")&&(i==0))||(temp=="")&&(str[i-1]=='(') )
                       temp+=str[i];
                   else
                   {
                      if (temp!="") //for operat after )
                       {
                           s_func.push_front(Determine(temp));
                           temp="";
                       }
                      while ( (!s_op.empty())&&(s_op.front()!='(') )
                      {
                           T2 = new node ;
                           T2->operat = s_op.front();   s_op.pop_front();
                           T2->R = s_func.front();      s_func.pop_front();
                           T2->L = s_func.front();      s_func.pop_front();
                           s_func.push_front(T2);
                           T=T2 ; T2 = NULL ;
                      }
                      if (str[i]=='-')
                          temp+= str[i] ;
                      s_op.push_front('+');
                  }
               }
           } // finsh processing the + and -
           else if ( (str[i]=='*')||(str[i]=='/'))  // processing the * and /
           {
               if (internal)
                   temp+=str[i];
               else
               {
                   if (temp!="")
                   {
                       s_func.push_front(Determine(temp));
                       temp="";
                   }
                   if ( (!s_op.empty())&&( (s_op.front()=='*')||(s_op.front()=='/') ) )
                   {
                       T2 = new node ;
                       T2->operat = s_op.front();   s_op.pop_front();
                       T2->R = s_func.front();      s_func.pop_front();
                       T2->L = s_func.front();      s_func.pop_front();
                       s_func.push_front(T2);
                       T=T2 ; T2 = NULL ;
                   }
                   s_op.push_front(str[i]);
               }
           }
           else if (str[i]=='(') //processing the ( and internal boolean ;
           {
               if (temp!="")
               {
                   if (!internal)
                       internal = true;
                   else
                       internal2 = true ;
                   temp+=str[i];
               }
               else
               {
                   s_op.push_front(str[i]);
               }
           }
           else if (str[i]==')')
           {
               if (internal)
               {
                   temp+=str[i];
                   if (internal2)
                       internal2 = false ;
                   else
                       internal = false ;
               }
               else
               {
                   s_func.push_front(Determine(temp));
                   temp = "";
                   while (s_op.front()!='(') // note:
                   {
                       T2 = new node ;
                       T2->operat = s_op.front();   s_op.pop_front();
                       T2->R = s_func.front();      s_func.pop_front();
                       T2->L = s_func.front();      s_func.pop_front();
                       s_func.push_front(T2);
                       T=T2 ; T2 = NULL ;
                   }
                   s_op.pop_front(); //pop the ( in stack ;
               }
           }
           else if (str[i]!=' ') // const and char >>> ex: 30 , sin ,cos
               temp+=str[i];
       }
   if (temp!="")
       {
        s_func.push_front(Determine(temp)); //
        temp="";
       }
   while (!s_op.empty())
   {
       T2 = new node ;
       T2->operat = s_op.front();   s_op.pop_front();
       T2->R = s_func.front();      s_func.pop_front();
       T2->L = s_func.front();      s_func.pop_front();
       s_func.push_front(T2);
       T=T2 ; T2 = NULL ;
   }
   T = s_func.front();
} // finish the all function



