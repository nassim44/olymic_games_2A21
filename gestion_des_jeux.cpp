#include "gestion_des_jeux.h"
#include "ui_gestion_des_jeux.h"
#include <QString>
#include <QDateEdit>
#include <QApplication>
#include <QTabWidget>
#include "connection.h"
#include <QDialog>
#include "olympic_games.h"

#include<QMessageBox>
#include<QDebug>
#include<QRegExpValidator>
#include<QLabel>

#include<QIntValidator>//contorle de saisie (int)
#include<QModelIndex>

#include<QComboBox>
#include<QCompleter>

#include "smtp.h"
#include <QFileDialog>
#include<QFile>
#include<QStringList>

#include<QTimer>
#include<QDateTime>

#include<QtCharts/QPieSlice>
#include<QtCharts/QChartView>
#include<QtCharts/QPieSeries>
#include<QPainter>
#include<QChart>
#include<QChartView>

#include"admin.h"


//_____________________________________________________________________________________________________


#define NOM_RX "^([a-z]+[A-Z]+[ ]?|[a-z]+[A-Z])+$"
#define NUM_RX "^([0-9]+[,.]?)+$"
      QRegExp rxNom(NOM_RX);
      QRegExp rxNum(NUM_RX);
      QRegExpValidator* valiNom= new QRegExpValidator(rxNom);
       QRegExpValidator* valiNum= new QRegExpValidator(rxNum);




//______________________________________________________________________________________________________
Gestion_des_jeux::Gestion_des_jeux(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestion_des_jeux)
{
    ui->setupUi(this);
// afficher la date et l'heure selon une horloge digitale
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(showDate()));
    timer->start();



  //  QDialog::showFullScreen();// plein écran
//-----------------------------------------------CONTROLE DE SAISIE--------------------------------------------------------------------
    ui->tableView->setModel(olg.afficher());
    ui->lineEdit_IDjeux->setValidator(new QIntValidator(0000,9999,this));//controler la saisie de l'ID_JEUX max 8_chiffres
    ui->lineEdit_M_ID_N->setValidator(new QIntValidator(0000,9999,this));
    ui->lineEdit__ID_supp->setValidator(new QIntValidator(0000,9999,this));

///CHERCHER
    Model_Completer=new QCompleter(this);
                            Model_Completer->setModel(olg.wombo_combo());
                            ui->lineEdit_id_cherche->setCompleter(Model_Completer);
}


//--------------------------------------AFFICHER DATE---------------------------------------------------------------------------
void  Gestion_des_jeux::showDate()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString("dddd : dd : MMMM : yyyy");

    ui->label_Date->setText(datetimetext);
}
//--------------------------------------AFFICHER HEURE---------------------------------------------------------------------------

void  Gestion_des_jeux::showTime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    if((time.second() % 2)==0)
    {
        time_text[3]= ' ';
        time_text[8]= ' ';

    }

    ui->Digital_horloge->setText(time_text);
    ui->Digital_horloge_2->setText(time_text);


}
//---------------------------------------------------------------------------------------------------------------------------------------
Gestion_des_jeux::~Gestion_des_jeux()
{
    delete ui;
}


//AJOUT__________________________________________________________________________________________________
void Gestion_des_jeux::on_pushButton_AJOUTER_clicked()
{

            int ID_JEUX=ui->lineEdit_IDjeux->text().toInt();
            QString TYPE_JEUX=ui->comboBox_type_AJOUT_2->currentText();
            QString NATION=ui->comboBox_Nation_Ajout->currentText();
            QString DISCIPLINE=ui->comboBox_disc_ajout->currentText();
            int NBR_JEUX=ui->spinBox_nbr_j_Ajout->text().toInt();

   olympic_games O( ID_JEUX, TYPE_JEUX, NATION, DISCIPLINE,NBR_JEUX);
   //controler la saisie entre type jeu et discipline
   if (((TYPE_JEUX=="Individuel")&&((DISCIPLINE== "Football")||(DISCIPLINE== "Handball")||(DISCIPLINE== "VoleyBall")||(DISCIPLINE== "BasketBall")))
           ||((TYPE_JEUX=="Collectif")&&((DISCIPLINE== "Tenis")||(DISCIPLINE== "Boxe")||((DISCIPLINE== "Natation")||((DISCIPLINE== "Taekwando"))))))
   {

       QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                QObject::tr("discipline non validée\n"
                                            "Click Cancel to exit."),QMessageBox::Cancel);
   }
       else
   {
   bool test =O.ajouter();
   if(test)
   {

       ui->tableView->setModel(olg.afficher());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("Ajout effectué\n"
                                                   "Click Cancel to exit."),QMessageBox::Cancel);
   }
              else
                  QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                           QObject::tr("Ajout non effectué\n"
                                                       "Click Cancel to exit."),QMessageBox::Cancel);


           }
   // Vider les cases
   ui->lineEdit_IDjeux->clear();
   ui->comboBox_type_AJOUT_2->clear();
   ui->comboBox_Nation_Ajout->clear();
   ui->comboBox_disc_ajout->clear();
   ui->spinBox_nbr_j_Ajout->clear();

}
//AJOUT____________________________________________________________________________________________________

/*void Gestion_des_jeux::on_tableView_activated(const QModelIndex &index)
{
    ui->tableView->setModel((Etmp.afficher()));
}*/
// __________Supprimer______________________________________________________________________________________

void Gestion_des_jeux::on_pushButton_supprimer_clicked()
{
    int id=ui->lineEdit__ID_supp->text().toInt();
    bool test=olg.supprimer(id);
    if(test)
    {
        ui->tableView_aff_supp->setModel(olg.afficher());

        ui->tableView->setModel(olg.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Suppression non effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    //vider le lineEdit
    ui->lineEdit__ID_supp->clear();

}

//afficher__________________________aprés suppression____________________________________________________
void Gestion_des_jeux::on_pushButton_afficher_supp_clicked()
{
    ui->tableView_aff_supp->setModel(olg.afficher());

}

//_________________________________________________________________________________________________________
// bouton affciher---->afficher________cliquer sur aficher pour affiche la base_____________________
/*void Gestion_des_jeux::on_pushButton_13_clicked()
{
    ui->tableView->setModel(olg.afficher());
}*/




//---------------------------------------------------------------Modifier-------------------------------------------------------------------------------
void Gestion_des_jeux::on_pushButton_Modifier_clicked()
{
    bool test=false;
    int idd = ui->lineEdit_M_ID_N->text().toInt();
    int ID_JEUX =ui->lineEdit_M_ID->text().toInt();
    QString TYPE_JEUX  =ui->comboBox_type_modifier->currentText();
    QString NATION=ui->comboBox_Nation->currentText();
    QString DISCIPLINE = ui->comboBox_disc_modifier->currentText();
    int NBR_JEUX = ui->spinBox_3->text().toInt();
    olympic_games Og(ID_JEUX,TYPE_JEUX,NATION,DISCIPLINE,NBR_JEUX);

    if (((TYPE_JEUX=="Individuel")&&((DISCIPLINE== "Football")||(DISCIPLINE== "Handball")||(DISCIPLINE== "VoleyBall")||(DISCIPLINE== "BasketBall")))
       ||((TYPE_JEUX=="Collectif")&&((DISCIPLINE== "Tennis")||(DISCIPLINE== "Boxe")||((DISCIPLINE== "Natation")||((DISCIPLINE== "Taekwando"))))))
    {

        QMessageBox::critical(nullptr,QObject::tr("Not OK"),//tester  le controle de saisie du type de jeux
                                 QObject::tr("discipline non validée\n"
                                 "Click Cancel to exit."),QMessageBox::Cancel);
    }
        else
    {
  test=Og.modifier(idd); //appel fonction modifier
  if(test)
   {

              ui->tableView->setModel(Og.afficher());//refresh
              ui->tableView_modifier->setModel(Og.afficher());//refresh


        QMessageBox::information(nullptr, QObject::tr("modifier une olympic_games"),
                                QObject::tr("Base de donné mise à jour.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

   }
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier une olympic_games"),
                  QObject::tr("Erreur , vérifier vos données !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}
    //-----faire un clear après la modification
     ui->lineEdit_M_ID_N->clear();
     ui->lineEdit_M_ID->clear();
     ui->comboBox_type_modifier->clear();
     ui->comboBox_Nation->clear();
     ui->comboBox_disc_modifier->clear();
     ui->spinBox_3->clear();
}


//--------------------------------------------------- afficher_dans_le_tableView_de_la_modification_

void Gestion_des_jeux::on_pushButton_Modifier_2_clicked()
{
    ui->tableView_modifier->setModel(olg.afficher());

}
//-------------------------------------------------------cliquer sur chaque case-------------------------------------------------
void Gestion_des_jeux::on_tableView_modifier_clicked(const QModelIndex &index)
{
    ui->lineEdit_M_ID_N->setText(ui->tableView_modifier->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
}
//--------------------------------------------------------------------s'authentifier--------------------------------------------------
/*void Gestion_des_jeux::on_pushButton_authentifier_clicked()
{
    bool test=false;

    QSqlDatabase db;
    QSqlQuery query(db);
    QString select ="SELECT login from account wher login=admin and password=admin";
    qDebug()<<select;
    query.prepare(select);
    query.addBindValue(ui->lineEdit_login->text());
    query.addBindValue(ui->lineEdit_pasword->text());
    query.exec();
    if(test)
  {


  QMessageBox::information(nullptr, QObject::tr("S'authentifier"),
                    QObject::tr("accés autorisé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("S'authentifier"),
                    QObject::tr("Erreur mot de passe ou login incorrect !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }

*/

//------------------------------------------------------------chercher-------------------------------------------------------------------
/*void Gestion_des_jeux::on_pushButton_chercher_clicked()
{
   // QString rech=ui->tableView_rechercher->text();
    //QString res =QString::number(id);

    int rech=ui->lineEdit_id_recher->text().toInt();

          ui->tableView_rechercher->setModel(olg.rechercher(rech));

          ui->lineEdit_id_recher->clear();

}*/

//----------------------------------------------------------Chercher-selon-ID_JEUX------------------------------------------------------------------
void Gestion_des_jeux::on_CHERCHER_clicked()
{
    int id=ui->lineEdit_id_cherche->text().toInt();

                Model_Completer=new QCompleter(this);
                    Model_Completer->setModel(olg.wombo_combo());
                    ui->lineEdit_id_cherche->setCompleter(Model_Completer);
                      QSqlQueryModel * Model_Complete=olg.rechercher( id);
                      if (Model_Complete != nullptr)
                        {
                         ui->tableView_rechercher->setModel(Model_Complete);
                         ui->lineEdit_id_cherche->setCompleter(Model_Completer);
                        }
}
//----------------------------------------------------------Chercher-selon-TYPE_JEUX------------------------------------------------------------------

void Gestion_des_jeux::on_pushButton_chercher_type_clicked()
{
    QString type=ui->chercher_type->text();
    Model_Completer->setModel(olg.wombo_combo());
    ui->chercher_type->setCompleter(Model_Completer);
      QSqlQueryModel * Model_Complete=olg.rechercher1(type);
      if (Model_Complete != nullptr)
        {
         ui->tableView_rechercher->setModel(Model_Complete);
         ui->chercher_type->setCompleter(Model_Completer);
        }
}
//----------------------------------------------------------CHERCHE-SELON-DISCIPLINE-DE-JEUX------------------------------------------------------------------
void Gestion_des_jeux::on_chercher_discipline_clicked()
{
    QString discipline=ui->lineEdit_cherche_DIS->text();
    Model_Completer->setModel(olg.wombo_combo());
    ui->lineEdit_cherche_DIS->setCompleter(Model_Completer);
      QSqlQueryModel * Model_Complete=olg.rechercher2(discipline);
      if (Model_Complete != nullptr)
        {
         ui->tableView_rechercher->setModel(Model_Complete);
         ui->lineEdit_cherche_DIS->setCompleter(Model_Completer);
        }
}

//----------------------------------------------------------CHERCHE-SELON-NATION-DE-JEUX------------------------------------------------------------------

void Gestion_des_jeux::on_CHERCHER_NATION_clicked()
{
    QString nation=ui->lineEdit_RN->text();
    Model_Completer->setModel(olg.wombo_combo());
    ui->lineEdit_RN->setCompleter(Model_Completer);
      QSqlQueryModel * Model_Complete=olg.rechercher2(nation);
      if (Model_Complete != nullptr)
        {
          ui->tableView_rechercher->setModel(Model_Complete);
         ui->lineEdit_RN->setCompleter(Model_Completer);
        }
}


//---------------------------------------------------------------------TRI-----------------------------------------------------------------------------------

void Gestion_des_jeux::on_pushButton_trier_clicked()
{
    ui->tableView_rechercher->setModel(olg.tri());

}
//-----------------------------------------------------------TRI-PAR TYPE-DE-JEUX ---------------------------------------------------------------------------------

void Gestion_des_jeux::on_pushButton_tri_type_clicked()
{
      ui->tableView_rechercher->setModel(olg.tri2());
}
//-----------------------------------------------------------TRI-PAR DISCIPLINE ---------------------------------------------------------------------------------
void Gestion_des_jeux::on_pushButton_TRI_dis_clicked()
{
    ui->tableView_rechercher->setModel(olg.tri3());

}
//-----------------------------------------------------------TRI-PAR NATION ---------------------------------------------------------------------------------
void Gestion_des_jeux::on_pushButton_TRI_Nation_clicked()
{
    ui->tableView_rechercher->setModel(olg.tri4());
}
//-------------------------------------------------------------MAILING------------------------------------------------------------------------------------------------------------------------
void Gestion_des_jeux::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void  Gestion_des_jeux::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}


void   Gestion_des_jeux::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Mail envoyé!\n\n" ) );
    ui->rcpt->clear();
    ui->sujet->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}


void Gestion_des_jeux::on_sendBtn_clicked()
{

    Smtp* smtp = new Smtp("dhia.zeddini.14@gmail.com",ui->mail_pass->text(), "Smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
//(const QString &from, const QString &to, const QString &subject, const QString &body)
    if( !files.isEmpty() )
        smtp->sendMail("dhia.zeddini.14@gmail.com", ui->rcpt->text() ,ui->sujet->text(), ui->msg->toPlainText(), files );
    else
        smtp->sendMail("dhia.zeddini.14@gmail.com", ui->rcpt->text() ,ui->sujet->text(),ui->msg->toPlainText());
}

//-------------------------------------------------------------MAILING------------------------------------------------------------------------------------------------------------------------





/*void Gestion_des_jeux::on_Stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                            model->setQuery("select * from VOITURE where HRE < 10 ");
                            float heure1=model->rowCount();
                            model->setQuery("select * from VOITURE where HRE  between 10 and 14 ");
                            float heure2=model->rowCount();
                            model->setQuery("select * from VOITURE where HRE >14 ");
                            float heure3=model->rowCount();
                            float total=heure1+heure2+heure3;
                            QString a=QString("moins de 10 hr "+QString::number((heure1*100)/total,'f',2)+"%" );
                            QString b=QString("entre 10 et 14 hr "+QString::number((heure2*100)/total,'f',2)+"%" );
                            QString c=QString("+14 hr "+QString::number((heure3*100)/total,'f',2)+"%" );
                            QPieSeries *series = new QPieSeries();
                            series->append(a,heure1);
                            series->append(b,heure2);
                            series->append(c,heure3);
                    if (heure1!=0)
                    {QPieSlice *slice = series->slices().at(0);
                     slice->setLabelVisible();
                     slice->setPen(QPen());}
                    if ( heure2!=0)
                    {
                             // Add label, explode and define brush for 2nd slice
                             QPieSlice *slice1 = series->slices().at(1);
                             //slice1->setExploded();
                             slice1->setLabelVisible();
                    }
                    if(heure3!=0)
                    {
                             // Add labels to rest of slices
                             QPieSlice *slice2 = series->slices().at(2);
                             //slice1->setExploded();
                             slice2->setLabelVisible();
                    }
                            // Create the chart widget
                            QChart *chart = new QChart();
                            // Add data to chart with title and hide legend
                            chart->addSeries(series);
                            chart->setTitle("Pourcentage Par heure :Nombre Des voiture "+ QString::number(total));
                            chart->legend()->hide();
                            // Used to display the chart
                            QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);
                            chartView->resize(1000,500);
                            chartView->show();

}*/


