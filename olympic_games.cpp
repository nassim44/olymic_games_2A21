#include "olympic_games.h"
#include "connection.h"
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlDatabase>
#include "gestion_des_jeux.h"

olympic_games::olympic_games(){}
olympic_games::olympic_games(int ID_JEUX,QString TYPE_JEUX,QString NATION,QString DISCIPLINE,int NBR_JEUX)
{
this->ID_JEUX=ID_JEUX;
this->NBR_JEUX=NBR_JEUX;
this->TYPE_JEUX=TYPE_JEUX;
this->NATION=NATION;
this->DISCIPLINE=DISCIPLINE;
}
bool olympic_games;
//AJOUT
bool olympic_games::ajouter()
{
    QSqlQuery query;
    QString res = QString ::number(ID_JEUX);

    query.prepare(" insert into olympic_games (ID_JEUX,TYPE_JEUX,NATION,DISCIPLINE,NBR_JEUX)""values(:ID_JEUX,:TYPE_JEUX,:NATION,:DISCIPLINE,:NBR_JEUX)");
    //Créer les variables  liées
    query.bindValue(":ID_JEUX",res);
    query.bindValue(":TYPE_JEUX",TYPE_JEUX);
    query.bindValue(":NATION",NATION);
    query.bindValue(":DISCIPLINE",DISCIPLINE);
    query.bindValue(":NBR_JEUX",NBR_JEUX);

    return  query.exec();//envoyer la requete pour l'exécuter
}

//Afficher__________________________________________________________________
QSqlQueryModel * olympic_games::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from olympic_games");
    return model;
}
//Modifier__________________________________________________________________
bool olympic_games::modifier(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare(" UPDATE OLYMPIC_GAMES SET  TYPE_JEUX = :type_jeux , NATION = :nation , DISCIPLINE = :discipline , NBR_JEUX = :nbr_jeux  where ID_JEUX = :idd ");
query.bindValue(":idd", res);
//query.bindValue(":id_jeux",ID_JEUX );
query.bindValue(":type_jeux", TYPE_JEUX);
query.bindValue(":nation", NATION);
query.bindValue(":discipline", DISCIPLINE);
query.bindValue(":nbr_jeux", NBR_JEUX);

return query.exec();
}



//SUPPRESSION
bool olympic_games::supprimer(int id)
{
    QSqlQuery query;
    QString res =QString::number(id);
    query.prepare("Delete from OLYMPIC_GAMES where ID_JEUX= :ID_JEUX");
    query.bindValue(":ID_JEUX",res);
    return query.exec();
}
// RECHERCHER-------------------------------------------------------------------------------------------------------------------
/*QSqlQueryModel* olympic_games::rechercher(int ID_JEUX)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString res =QString::number(ID_JEUX);
        QString recher="select * from evenment where ID_JEUX like '%"+res+"%' ";


        model->setQuery(recher);
        return model;
}*/
//wombo combo
QSqlQueryModel* olympic_games::wombo_combo()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select Code_ABar from Produits");
    return model;
}
//-------------rechercher --------ID-JEUX-----------------------------

  QSqlQueryModel*  olympic_games::rechercher(int id)
 {

      QString res=QString::number(id);//convertir int id to tring

    QSqlQuery qry;


     qry.prepare("SELECT * FROM OLYMPIC_GAMES where ID_JEUX =:id");
     qry.bindValue(":id",res);
     qry.exec();
     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);

     return model;
 }

  //--------------------------------------------------------Chercher selon le type de jeux-----------------------------------------------------------
  QSqlQueryModel * olympic_games::rechercher1(QString type)
  {
      QSqlQuery qury;
      qury.prepare("SELECT * FROM OLYMPIC_GAMES where TYPE_JEUX =:type");
      qury.bindValue(":type",type);
      qury.exec();
      QSqlQueryModel *model= new QSqlQueryModel;
      model->setQuery(qury);

      return model;
  }
//---------------------------CHERCHER SELON LE DISCIPLINE---------------------------------------------------------------------------------------
  QSqlQueryModel * olympic_games:: rechercher2(QString discipline)
  {
      QSqlQuery qury;
      qury.prepare("SELECT * FROM OLYMPIC_GAMES where DISCIPLINE =:discipline");
      qury.bindValue(":discipline",discipline);
      qury.exec();
      QSqlQueryModel *model= new QSqlQueryModel;
      model->setQuery(qury);

      return model;
  }
  //---------------------------CHERCHER SELON LA NATION ---------------------------------------------------------------------------------------
  QSqlQueryModel * olympic_games::rechercher3(QString nation)//chercher selon la nation de jeux
  {

      QSqlQuery qury;
      qury.prepare("SELECT * FROM OLYMPIC_GAMES where DISCIPLINE =:nation");
      qury.bindValue(":nation",nation);
      qury.exec();
      QSqlQueryModel *model= new QSqlQueryModel;
      model->setQuery(qury);

      return model;
  }
  //---------------------------------------tri---------------------------------------------------------

  QSqlQueryModel* olympic_games::tri()
  {
      QSqlQueryModel * model= new QSqlQueryModel();
             model->setQuery("SELECT * FROM OLYMPIC_GAMES ORDER BY NBR_JEUX");
             return model;
  }

  //---------------------------------------tri---PAR TYPE DE JEUX ------------------------------------------------------
  QSqlQueryModel* olympic_games::tri2()
  {
      QSqlQueryModel * model= new QSqlQueryModel();
             model->setQuery("SELECT * FROM OLYMPIC_GAMES ORDER BY TYPE_JEUX");
             return model;
  }

  //---------------------------------------tri---PAR DISCIPLINE ------------------------------------------------------
  QSqlQueryModel* olympic_games::tri3()
  {
      QSqlQueryModel * model= new QSqlQueryModel();
             model->setQuery("SELECT * FROM OLYMPIC_GAMES ORDER BY DISCIPLINE");
             return model;
  }
  //---------------------------------------tri---PAR NATION ------------------------------------------------------

  QSqlQueryModel* olympic_games::tri4()
  {
      QSqlQueryModel * model= new QSqlQueryModel();
             model->setQuery("SELECT * FROM OLYMPIC_GAMES ORDER BY NATION");
             return model;
  }
