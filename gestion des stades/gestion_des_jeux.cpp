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

#include<QtCharts>
#include<QChartView>

#include <QMultimedia>
#include <QMediaPlayer>
#include <QThread>

#include"admin.h"
#include<QPropertyAnimation>

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

//    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
//  ui->quickWidget->show();



// afficher la date et l'heure selon une horloge digitale
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(showDate()));
    timer->start();

    //-----------------------annimerbouton ajouter-------------
    animation =new QPropertyAnimation(ui->pushButton_AJOUTER ,"geometry");
    animation->setDuration(700);
    animation->setStartValue(ui->pushButton_AJOUTER->geometry());
    animation->setEndValue(QRect(250,500,100,50));
    animation->start();

    //-----------------------annimerbouton afficher -------------

//     animation1=new QPropertyAnimation(ui->pushButton_13 ,"geometry");
//            animation1->setDuration(1000);
//            animation1->setStartValue(ui->pushButton_13->geometry());
//            animation1->setEndValue(QRect(10,10,10,10));
//            animation1->start();



    //----------------------------------------
player= new QMediaPlayer(this);


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
              //--------------------------------------------------------------
              player->setMedia(QUrl::fromLocalFile("C:/Users/Admin/Downloads/619563db00e020.41154621.mp3"));
                                        player->play();
                                        qDebug()<<player->errorString();
                                        QThread::sleep(1);
              //---------------------------------------------------------------
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

        //--------------SOUND---------------------------------------------------
        player->setMedia(QUrl::fromLocalFile("C:/Users/Admin/Desktop/Atelier_Connexion/supprimerSound.mp3"));
                                  player->play();
                                  qDebug()<<player->errorString();
                                  QThread::sleep(1);
     //-------------------------------SOUND--------------------------------------------------


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


        //-------------------------------SOUND--------------------------------------------------
        player->setMedia(QUrl::fromLocalFile("C:/Users/Admin/Desktop/Atelier_Connexion/elementModifié.mp3"));
                                  player->play();
                                  qDebug()<<player->errorString();
                                  QThread::sleep(1);
        //-------------------------------SOUND--------------------------------------------------



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


//------------------------------------ afficher_dans_le_tableView_de_la_modification----------------------------------------------

void Gestion_des_jeux::on_pushButton_Modifier_2_clicked()
{
    ui->tableView_modifier->setModel(olg.afficher());

}
//-------------------------------------------------------cliquer sur chaque case-------------------------------------------------
void Gestion_des_jeux::on_tableView_modifier_clicked(const QModelIndex &index)
{
    ui->lineEdit_M_ID_N->setText(ui->tableView_modifier->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
}


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
       //-------------------------------SOUND--------------------------------------------------
                player->setMedia(QUrl::fromLocalFile("C:/Users/Admin/Desktop/Atelier_Connexion/elementTrouvé.mp3"));
                player->play();
                qDebug()<<player->errorString();
                QThread::sleep(1);
       //-------------------------------SOUND--------------------------------------------------
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
      //-------------------------------SOUND--------------------------------------------------
               player->setMedia(QUrl::fromLocalFile("C:/Users/Admin/Desktop/Atelier_Connexion/elementTrouvé.mp3"));
               player->play();
               qDebug()<<player->errorString();
               QThread::sleep(1);
      //-------------------------------SOUND--------------------------------------------------
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
      //-------------------------------SOUND--------------------------------------------------
               player->setMedia(QUrl::fromLocalFile("C:/Users/Admin/Desktop/Atelier_Connexion/elementTrouvé.mp3"));
               player->play();
               qDebug()<<player->errorString();
               QThread::sleep(1);
      //-------------------------------SOUND--------------------------------------------------
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

//void  Gestion_des_jeux::browse()
//{
//    files.clear();

//    QFileDialog dialog(this);
//    dialog.setDirectory(QDir::homePath());
//    dialog.setFileMode(QFileDialog::ExistingFiles);

//    if (dialog.exec())
//        files = dialog.selectedFiles();

//    QString fileListString;
//    foreach(QString file, files)
//        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

//    ui->file->setText( fileListString );
//}


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

    Smtp* smtp = new Smtp("fedi.br.14@gmail.com",ui->mail_pass->text(), "Smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
//(const QString &from, const QString &to, const QString &subject, const QString &body)
    if( !files.isEmpty() )
        smtp->sendMail("fedi.br.14@gmail.com", ui->rcpt->text() ,ui->sujet->text(), ui->msg->toPlainText(), files );
    else
        smtp->sendMail("fedi.br.14@gmail.com", ui->rcpt->text() ,ui->sujet->text(),ui->msg->toPlainText());

    //-------------------------------SOUND--------------------------------------------------
             player->setMedia(QUrl::fromLocalFile("C:/Users/Admin/Desktop/Atelier_Connexion/mailEnvoyé.mp3"));
             player->play();
             qDebug()<<player->errorString();
             QThread::sleep(1);
    //-------------------------------SOUND--------------------------------------------------
}




//-------------------------------------------------------------STAT------------------------------------------------------------------------------------------------------------------------
void Gestion_des_jeux::on_statistique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                            model->setQuery("select * from OLYMPIC_GAMES where NBR_JEUX < 7 ");
                            float nbr1=model->rowCount();
                            model->setQuery("select * from OLYMPIC_GAMES where NBR_JEUX  between 2 and 5 ");
                            float nbr2=model->rowCount();
                            model->setQuery("select * from OLYMPIC_GAMES where NBR_JEUX >3 ");
                            float nbr3=model->rowCount();
                            float total=nbr1+nbr2+nbr3;
                            QString a=QString(" nombre de jeux inférieur  à 7 "+QString::number((nbr1*100)/total,'f',2)+"%" );
                            QString b=QString("nombre de jeux entre 2 et 6 "+QString::number((nbr2*100)/total,'f',2)+"%" );
                            QString c=QString(" nombre de jeux plus que 3 "+QString::number((nbr3*100)/total,'f',2)+"%" );
                            QPieSeries *series = new QPieSeries();
                            series->append(a,nbr1);
                            series->append(b,nbr2);
                            series->append(c,nbr3);
                    if (nbr1!=0)
                    {QPieSlice *slice = series->slices().at(0);
                     slice->setLabelVisible();
                     slice->setPen(QPen());}
                    if ( nbr2!=0)
                    {
                             // Add label, explode and define brush for 2nd slice
                             QPieSlice *slice1 = series->slices().at(1);
                             //slice1->setExploded();
                             slice1->setLabelVisible();
                    }
                    if(nbr3!=0)
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
                            chart->setTitle("Pourcentage Par nombre  :Nombre Des jeux "+ QString::number(total));
                            chart->legend()->hide();
                            // Used to display the chart
                            QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);
                            chartView->resize(1000,500);
                            chartView->show();
}


