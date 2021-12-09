#include "spectateurs.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QCameraInfo>

spectateurs::spectateurs()
{
id=0; nom="" ; prenom="";nationalite="";Age=0,type="";
}

spectateurs::spectateurs(int id,int Age,QString nom,QString prenom,QString nationalite,QString type)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->Age=Age;
    this->nationalite=nationalite;
    this->type=type;}
    int spectateurs::getid(){return id;}
    int spectateurs::getAge(){return Age;}
    QString spectateurs::getnom(){return nom;}
    QString spectateurs::getprenom(){return prenom;}
    QString spectateurs::getnationalite(){return nationalite;}
    QString spectateurs::gettype(){return type;}


    void spectateurs::setid(int id ){this->id=id;}
    void spectateurs::setAge(int Age ){this->Age=Age;}
    void spectateurs::setnom(QString n){nom=n;}
    void spectateurs::setprenom(QString t){prenom=t;}
    void spectateurs::setnationalite(QString t){nationalite=t;}
    void spectateurs::settype(QString t){type=t;}

bool spectateurs::ajouter()
{

    QSqlQuery query;
    QString res=QString::number(id);
    QString A=QString::number(Age);

    query.prepare("INSERT INTO SPECTATEURS (ID,NOM,PRENOM,AGE,NATIONALITE,type) values (:ID,:NOM,:PRENOM,:AGE,:NATIONALITE,:TYPE)");
    query.bindValue (":ID",res);
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":AGE",Age);
    query.bindValue(":NATIONALITE",nationalite);
    query.bindValue(":TYPE",type);



    return query.exec();
}
QSqlQueryModel * spectateurs::afficher()
{
    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("select * from SPECTATEURS");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("NATIONALITE"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));


    return modal;

}

void spectateurs::selectionner(Ui::MainWindow *ui,const QModelIndex &index)
{ QSqlQuery qry;
    QString val;
   val=ui->tableView->model()->data(index).toString();

   qry.prepare("SELECT * FROM spectateurs  where ID='"+val+"' or NOM='"+val+"' or PRENOM='"+val+"' or NATIONALITE='"+val+"' or Age='"+val+"' or TYPE='"+val+"' ");
       if(qry.exec())
       {
           while (qry.next())

           {

               ui->lineEdit_id->setText(qry.value(0).toString());
                ui->lineEdit_nom->setText(qry.value(1).toString());
                ui->lineEdit_prenom->setText(qry.value(2).toString());
                ui->lineEdit_pays->setText(qry.value(4).toString());
                ui->lineEdit_age->setText(qry.value(3).toString());
                ui->comboBox->setCurrentText(qry.value(5).toString());

           }

       }


}

bool spectateurs::supprimer(Ui::MainWindow *ui)
{
    QString id;
    id=ui->lineEdit_id->text();
      QSqlQuery query ;
      query.prepare("DELETE FROM spectateurs WHERE ID='"+id+"'");
      if(query.exec())
      {
                  return query.exec();
      }
      else return false;


}


bool spectateurs::modifier(int id,int Age,QString nom,QString prenom,QString nationalite,QString type)
{
    QString res=QString::number(id);
    QString A=QString::number(Age);
    QSqlQuery query ;


       query.prepare("update spectateurs set nom=:nom,prenom=:prenom,age=:Age,nationalite=:nationalite,type=:type where id=:id");
       query.bindValue(":id",res);
       query.bindValue(":nom",nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":Age",A);
       query.bindValue(":nationalite",nationalite);
       query.bindValue(":type",type);



       return query.exec();
}
QSqlQueryModel * spectateurs::trierASC()
{
    QSqlQuery * q=new QSqlQuery();
    QSqlQueryModel * model=new QSqlQueryModel();
    q->prepare("SELECT * FROM Spectateurs order by age ASC");
    q->exec();
    model->setQuery(*q);
    return model;
}
QSqlQueryModel * spectateurs::trierDESC()
{
    QSqlQuery * q=new QSqlQuery();
    QSqlQueryModel * model=new QSqlQueryModel();
    q->prepare("SELECT * FROM Spectateurs order by age DESC");
    q->exec();
    model->setQuery(*q);
    return model;
}

void spectateurs::recherche(Ui::MainWindow *ui)
{
    QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        QString mot =ui->lineEdit_3->text();

        q.prepare("select * from Spectateurs where (ID LIKE '%"+mot+"%' or NOM LIKE '%"+mot+"%' or PRENOM LIKE '%"+mot+"%' or AGE LIKE '%"+mot+"%' or NATIONALITE"
                                                   " LIKE '%"+mot+"%' or TYPE LIKE '%"+mot+"%' )");

        q.exec() ;
        modal->setQuery(q);
        ui->tableView->setModel(modal);

}


bool spectateurs::verif_nom(QString ch_nom){
    bool test=true;
    int i;
    if(true)
    {
        for(i=0;i<ch_nom.length();i++){
            if(!(((ch_nom[i]>='A')&&(prenom[i]<='Z'))||((prenom[i]>='a')&&(prenom[i]<='z')))){
                test=false;
                return  test;
        }
    }
  }
    return  test;
}

bool spectateurs::verif_age(int age){
    bool test=true;

    if((age>99) || (age<0))
    {
                test=false;
                return  test;
    }

    return  test;
}



bool checkCameraAvailability()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}





