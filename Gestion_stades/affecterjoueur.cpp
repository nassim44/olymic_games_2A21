#include "affecterjoueur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <random>
Affecterjoueur::Affecterjoueur()
{
    id_event=0;id_jou=0;
}
Affecterjoueur::Affecterjoueur(int id_jou,int id_event)
{
    this->id_event=id_event;
    this->id_jou=id_jou;

}
QString Affecterjoueur::ajouterjoueurevent()
{
    QSqlQuery queryEvent;
    QSqlQuery queryJoueur;
    QSqlQuery queryInsert;
    QString idEvent = QString::number(id_event);
    QString idJoueur = QString::number(id_jou);

    QString specialitejoueur = "";
    QString typeEvent = "";

    //Get type stade
    queryEvent.prepare("SELECT * FROM event WHERE ID_EVENT = :id");
    queryEvent.bindValue(":id",idEvent);
    queryEvent.exec();
    while(queryEvent.next()) {
        typeEvent = queryEvent.value(4).toString();
    }

    //Get type jeu
    queryJoueur.prepare("SELECT * FROM joueur WHERE ID_JOUEUR = :id");
    queryJoueur.bindValue(":id",idJoueur);
    queryJoueur.exec();
    while(queryJoueur.next()) {
        specialitejoueur = queryJoueur.value(3).toString();
    }


    if(QString::compare(typeEvent,specialitejoueur,Qt::CaseInsensitive) == 0)
    {
            queryInsert.prepare("INSERT INTO prediction (ID_EV,ID_JOU) values (:ID_EV,:ID_JOU)");
            queryInsert.bindValue (":ID_EV",idEvent);
            queryInsert.bindValue (":ID_JOU",idJoueur);

            if(queryInsert.exec())
            {
                return "joueur affecte";
            } else {
                return "joueur non affecte";
            }

    }
    return "L'event et le joueur n'ont pas le meme specialite";
}
/*QSqlQueryModel* Event::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM event");



    return model;
}
*/
void Affecterjoueur::modifierprediction(QString idEvent)
{
    QSqlQuery query;
    QSqlQuery queryevent;
    QSqlQuery querycount;
    int high=100;

    qsrand(qrand());
    QString idJoueuer;
    QString pred;
    int size;
    queryevent.prepare("SELECT * FROM PREDICTION WHERE ID_EV = :ID_EV");
    queryevent.bindValue(":ID_EV",idEvent);
    queryevent.exec();
    querycount.prepare("SELECT COUNT(*) FROM PREDICTION WHERE ID_EV = :ID_EV");
    querycount.bindValue(":ID_EV",idEvent);
    querycount.exec();
    if(querycount.first()){
        size = querycount.value(0).toInt();
    }

    int i=1;
    int somme=0;
    while(queryevent.next()) {
       idJoueuer=queryevent.value(1).toString();

        if(i!=size)
        {
            pred = QString::number(qrand() % (high+1));
            high = high - pred.toInt();
            somme = somme+high;
            query.prepare("UPDATE PREDICTION SET  PREDICTION=:PREDICTION where ID_EV = :ID_EV AND ID_JOU= :ID_JOU");
            query.bindValue (":ID_JOU",idJoueuer);
            query.bindValue (":PREDICTION",pred);
            query.bindValue (":ID_EV",idEvent);
            query.exec();
           // i++;

        }else
        {
            query.prepare("UPDATE PREDICTION SET  PREDICTION=:PREDICTION where ID_EV = :ID_EV AND ID_JOU= :ID_JOU");
            query.bindValue (":ID_JOU",idJoueuer);
            query.bindValue (":PREDICTION",100-somme);
            query.bindValue (":ID_EV",idEvent);
            query.exec();
        }
    }



}
QSqlQueryModel* Affecterjoueur::afficherprediction()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM prediction");
    return model;
}

QSqlQueryModel* Affecterjoueur::afficherpredictionevnt(QString id)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM prediction WHERE ID_EV = " + id);
    return model;
}
