#ifndef STADE_H
#define STADE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDateTime>
class Stade
{
private:
    QString nom,type;
    int id ,capacite;


public:
    Stade();
    Stade(int,int,QString,QString);
    int getid(){return id;}
    int getcapacite(){return capacite;}
    QString getnom(){return nom;}
    QString gettype(){return type;}

    void setid(int id ){this->id=id;}
    void setcapacite(int capacite ){this->capacite=capacite;}
    void setnom(QString n){nom=n;}
    void settype(QString t){type=t;}
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int id);
    QSqlQueryModel* trier();
    QSqlQueryModel* trierparnom();
    QSqlQueryModel* trierpartype();
    QSqlQueryModel* recherche(QString nom, QString capacite,QString typestade);
    QSqlQueryModel* getids();
    Stade* getstade(int id);
    //QSqlQueryModel* getidj();
    //Stade* getjeux(int id);
    bool ajouterevent();
    Stade* afficherimage(int id);
    QSqlQueryModel* trierpartypeetcapacite();
    QSqlQueryModel* trierpartypeetnom();
    QSqlQueryModel* trierparnometcapacite();
    double location;


};

#endif // STADE_H
