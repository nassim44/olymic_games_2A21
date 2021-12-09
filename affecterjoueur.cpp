#include "affecterjoueur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <random>
#include <QtGui>
#include <qaxobject.h>
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
    queryEvent.prepare("SELECT * FROM EVENT WHERE ID_EVENT = :id");
    queryEvent.bindValue(":id",idEvent);
    queryEvent.exec();
    while(queryEvent.next()) {
        typeEvent = queryEvent.value(4).toString();
    }

    //Get type jeu
    queryJoueur.prepare("SELECT * FROM JOUEUR WHERE IDJ = :id");
    queryJoueur.bindValue(":id",idJoueur);
    queryJoueur.exec();
    while(queryJoueur.next()) {
        specialitejoueur = queryJoueur.value(4).toString();
    }


    if(QString::compare(typeEvent,specialitejoueur,Qt::CaseInsensitive) == 0)
    {
            queryInsert.prepare("INSERT INTO PREDICTION (ID_EV,ID_JOU) values (:ID_EV,:ID_JOU)");
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
/*void Affecterjoueur::modifierprediction(QString idEvent)
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



}*/
void Affecterjoueur::predictionExcel(QString idEvent)
{
    QString file("D:/Games/Classeur1.xlsx");
    QSqlQuery queryevent;
    QSqlQuery query;
    QString pred;
    int idJoueuer;

    QAxObject* excel=new QAxObject("Excel.Application");
    QAxObject* workbooks=excel->querySubObject("Workbooks");
    QAxObject* workbook=workbooks->querySubObject("Open(const QString&)",file);
    excel->dynamicCall("SetVisible(bool)",false);

    QAxObject* worksheet=workbook->querySubObject("WorkSheets(int)",1);

    QAxObject* usedrange=worksheet->querySubObject("UsedRange");
    QAxObject* rows=usedrange->querySubObject("Rows");
    QAxObject* columns=usedrange->querySubObject("Columns");

    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();

    queryevent.prepare("SELECT * FROM PREDICTION WHERE ID_EV = :ID_EV");
    queryevent.bindValue(":ID_EV",idEvent);
    queryevent.exec();

    while(queryevent.next()) {
        idJoueuer=queryevent.value(1).toInt();
        int nbtotalmatch=0;
        int win=0;
        for(int row=0;row<intRows;row++)
        {

            QAxObject* cell=worksheet->querySubObject("Cells(int,int)",row+1,1);
            QVariant value = cell->dynamicCall("Value()");

            if(idJoueuer == value.toInt() )
            {
                    QAxObject* cell1=worksheet->querySubObject("Cells(int,int)",row+1,2);
                    QVariant value1 = cell1->dynamicCall("Value()");
                    if(value1.toString()=="win")
                    {
                        win++;
                        nbtotalmatch++;
                    }else
                    {
                        nbtotalmatch++;
                    }
            }

        }
        pred =((win/nbtotalmatch)*100);

        query.prepare("UPDATE PREDICTION SET  PREDICTION=:PREDICTION where ID_EV = :ID_EV AND ID_JOU= :ID_JOU");
        query.bindValue (":PREDICTION",(int)((win/(double)nbtotalmatch)*100));
        query.bindValue (":ID_EV",idEvent);
        query.bindValue (":ID_JOU",QString::number(idJoueuer));
        query.exec();
    }


    /*for(int row=0;row<intRows;row++)
    {
        int nbtotalmatch=0;
        int win=0;
        QAxObject* cell=worksheet->querySubObject("Cells(int,int)",row+1,1);
        QVariant value = cell->dynamicCall("Value()");
        if(idEvent == value.toString() )
        {
                QAxObject* cell1=worksheet->querySubObject("Cells(int,int)",row+1,2);
                QVariant value1 = cell1->dynamicCall("Value()");
                if(value1.toString()=="win")
                {
                    win++;
                    nbtotalmatch++;
                }else
                {
                    nbtotalmatch++;
                }
        }
    }*/

    workbook->dynamicCall("Close");
    excel->dynamicCall("Quit()");
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
