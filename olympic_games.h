#ifndef OLYMPIC_GAMES_H
#define OLYMPIC_GAMES_H
#include<QString>
#include<QSqlDatabase>
#include <QDialog>
#include<QSqlQuery>
#include <QApplication>
#include<QSqlQueryModel>


class olympic_games
{
private:
    int ID_JEUX;
    int NBR_JEUX;
    QString TYPE_JEUX;
    QString NATION;
    QString DISCIPLINE;

public:
    olympic_games();
    olympic_games(int ID_JEUX,QString TYPE_JEUX,QString NATION,QString DISCIPLINE,int NBR_JEUX);


      //Geters
      int get_ID(){return ID_JEUX ;}
      QString get_type(){return TYPE_JEUX;}
      QString get_nation(){return NATION;}
      QString get_discipline(){return DISCIPLINE;}
      int get_nbr(){return NBR_JEUX ;}
      QSqlQueryModel* getidj();


           //Seters
           void set_id(int x){ID_JEUX=x;}
           void set_type(QString n){TYPE_JEUX=n;}
           void set_nation(QString m){NATION=m;}
           void set_discipline(QString disc){DISCIPLINE=disc;}

           ///CRUD
           bool ajouter();
           QSqlQueryModel *afficher();
           bool supprimer(int);
           bool modifier(int id);

           //Metiers
//           QSqlQueryModel*rechercher(int ID);

           QSqlQueryModel * rechercher(int id);//chercher selon ID_JEUX
           QSqlQueryModel * rechercher1(QString type);//chercher selon le type de jeux
           QSqlQueryModel * rechercher2(QString discipline);//chercher selon le discipline de jeux
           QSqlQueryModel * rechercher3(QString nation);//chercher selon la nation de jeux
           QSqlQueryModel * tri();
           QSqlQueryModel * tri2();
           QSqlQueryModel * tri3();
           QSqlQueryModel * tri4();



           QSqlQueryModel* wombo_combo();


};

#endif // OLYMPIC_GAMES_H
