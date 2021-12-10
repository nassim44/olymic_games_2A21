#ifndef SPECTATEURS_H
#define SPECTATEURS_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "ui_mainwindow.h"

class spectateurs
{
private:
    QString nom,prenom,nationalite,type;
    int id ,Age;
public:
    spectateurs();
    spectateurs(int,int,QString,QString,QString,QString);
    int getid();
    int getAge();
    QString gettype();
    QString getnom();
    QString getprenom();
    QString getnationalite();

    void setid(int );
    void setAge(int );
    void setnom(QString );
    void setprenom(QString );
    void setnationalite(QString );
    void settype(QString );

    bool ajouter();
    bool modifier(int id,int Age,QString nom,QString prenom,QString nationalite,QString type);
    QSqlQueryModel *afficher();
    bool supprimer(Ui::MainWindow *ui);
    void selectionner(Ui::MainWindow *ui,const QModelIndex &index);
    QSqlQueryModel * trierASC();
    QSqlQueryModel *trierDESC();
    void recherche(Ui::MainWindow *ui);
    bool verif_nom(QString nom) ;
    bool verif_age(int age) ;
    spectateurs valabilite(QString);

};

#endif // SPECTATEURS_H



