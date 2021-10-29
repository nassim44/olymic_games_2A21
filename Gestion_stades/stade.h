#ifndef STADE_H
#define STADE_H
#include <QString>
#include <QSqlQueryModel>

class Stade
{
    QString nom,type/*,date*/;
    int id ,capacite;
public:
    Stade();
    Stade(int,int,QString,QString/*,QString*/);
    QString getnom(){return nom;}
    QString gettype(){return type;}
    //QString getdate(){return date;}
    int getid(){return id;}
    void setnom(QString n){nom=n;}
    void settype(QString t){type=t;}
    //void setdate(QString d){date=d;}
    void setid(int id ){this->id=id;}
    void setcapacite(int capacite ){this->capacite=capacite;}
    bool ajouter();
    QSqlQueryModel* afficher();
   // bool supprimer(int);
};

#endif // STADE_H
