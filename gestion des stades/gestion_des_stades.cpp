#include "gestion_des_stades.h"
#include "ui_gestion_des_stades.h"
#include "stade.h"
#include <QApplication>
#include <QMessageBox>
#include <QIntValidator>
//#include "affecterjoueur.h"
#include"olympic_games.h"
#include"event.h"

//gestion_des_stades::gestion_des_stades(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::gestion_des_stades)
//{
//    ui->setupUi(this);
//}

gestion_des_stades::gestion_des_stades(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_des_stades)
{
    ui->setupUi(this);
    ui->comboBox_jeuxaff->setModel(og.getidj());


//    ui->lineEdit_id->setValidator(new QIntValidator(0,999,this));
//    ui->lineEdit_capacite->setValidator(new QIntValidator(0,999 ,this));
    ui->tab_stade->setModel(sta.afficher());
   // ui->tableView_affectation->setModel(event.afficher());
    ui->comboBox_3->setModel(sta.getids());
    ui->comboBox_4->setModel(sta.getids());
    ui->comboBox_stadeaff->setModel(sta.getids());
//    ui->comboBox_jeuxaff->setModel(oly.getidj());
//    ui->comboBox_idjoueur->setModel(jou.getidjou());
//    ui->comboBox_idevent->setModel(event.getidev());
//    ui->comboBox_predevent->setModel(event.getidev());
    //ui->checkBox_trierparcapacite->setChecked(true);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/Map.qml")));
    ui->quickWidget->show();

}


gestion_des_stades::~gestion_des_stades()
{
    delete ui;
}

void gestion_des_stades::on_pb_ajouter_clicked()
{

    int id=ui->lineEdit_id->text().toInt();
    int capacite=ui->lineEdit_capacite->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString type=ui->comboBox->currentText();


    Stade S(id,nom,type,capacite);
    bool test=S.ajouter();
    if(test)
    {
       ui->tab_stade->setModel(sta.afficher());
//            ui->comboBox_3->setModel(sta.getids());
//            ui->comboBox_4->setModel(sta.getids());
//            ui->comboBox_stadeaff->setModel(sta.getids());
//            int ID_JEUX=ui->lineEdit_IDjeux->text().toInt();
//            QString TYPE_JEUX=ui->comboBox_type_AJOUT_2->currentText();
//            QString NATION=ui->comboBox_Nation_Ajout->currentText();
//            QString DISCIPLINE=ui->comboBox_disc_ajout->currentText();
//            int NBR_JEUX=ui->spinBox_nbr_j_Ajout->text().toInt();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Ajout non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_des_stades::on_pushButton_clicked()
{
    Stade S1;
    S1.setid(ui->lineEdit_id_supp->text().toInt());
    bool test=S1.supprimer(S1.getid());
    if(test)
    {
        ui->tab_stade->setModel(sta.afficher());//refresh
        ui->comboBox_4->setModel(sta.getids());
        ui->comboBox_stadeaff->setModel(sta.getids());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Echec de supprission\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void gestion_des_stades::on_pb_modifier_clicked()
{
    int id=ui->comboBox_3->currentText().toInt();
    int capacite =ui->lineEdit_capacite_2->text().toInt();
    QString nom=ui->lineEdit_nom_2->text();
    QString type=ui->comboBox_2->currentText();

    Stade S(id,nom,type,capacite);
    bool test=S.modifier(id);


    if(test)
    {
        ui->tab_stade->setModel(sta.afficher());//refresh

        QMessageBox::information(nullptr, QObject::tr("modifier une Stade"),
                    QObject::tr("Stade modifé\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
        QMessageBox::critical(nullptr, QObject::tr("modifier une Stade"),
                    QObject::tr("Erreur!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void gestion_des_stades::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    Stade* s = sta.getstade((&arg1)->toInt());
    ui->lineEdit_nom_2->setText(s->getnom());
    ui->lineEdit_capacite_2->setText(QString::number(s->getcapacite()));
    int index = ui->comboBox_2->findText(s->gettype());
    if ( index != -1 ) {
       ui->comboBox_2->setCurrentIndex(index);
    }
}

void gestion_des_stades::on_pushButton_4_clicked()//boutton recherche
{
    QString nom = ui->lineEdit_nom_3->text();
    QString cap = ui->lineEdit_capacite_3->text();
    QString typestade=ui->comboBox_recherche->currentText();
    ui->tab_stade->setModel(sta.recherche(nom,cap,typestade));
}



void gestion_des_stades::on_pushButton_2_clicked()
{
    ui->lineEdit_nom_3->setText("");
    ui->lineEdit_capacite_3->setText("");
    ui->tab_stade->setModel(sta.afficher());
}

void gestion_des_stades::on_comboBox_4_currentIndexChanged(const QString &arg1)
{

    sta.getstade((&arg1)->toInt());

}


void gestion_des_stades::on_comboBox_stadeaff_currentIndexChanged(const QString &arg1)
{
    sta.getstade((&arg1)->toInt());
}

void gestion_des_stades::on_comboBox_jeuxaff_currentIndexChanged(const QString &arg1)
{
//    jeux.getjeux((&arg1)->toInt());
}


//--------------AFFECTER EVENT-------------------------------
void gestion_des_stades::on_pb_affecterevent_clicked()
{

    int ID_EVENT=ui->lineEdit_idevent->text().toInt();
    int ID_STADE=ui->comboBox_stadeaff->currentText().toInt();
    //int ID_JEUX=ui->comboBox_jeuxaff->currentText().toInt();
    int ID_JEUX=ui->lineEdit_idjeuxaff->text().toInt();

    QDateTime DATE=ui->dateTimeEdit->dateTime();


    Event e(ID_EVENT,ID_EVENT,ID_JEUX,DATE);

    QString message = e.ajouterevent();
    ui->tableView_affectation->setModel(EV.afficher());
    if(QString::compare(message,"Match affecte", Qt::CaseInsensitive) == 0)
    {
        ui->comboBox_idevent->setModel(EV.getidev());

        ui->tableView_affectation->setModel(EV.afficher());
        QMessageBox::information(this,"Affectation avec succés",message);
    } else {
        QMessageBox::critical(this,"Affectation non realisé",message);
    }

}




//void gestion_des_stades::on_comboBox_idjoueur_currentIndexChanged(const QString &arg1)
//{
//    jou.getjoueur((&arg1)->toInt());
//}

//void gestion_des_stades::on_pushButton_3_clicked()
//{



//    int id_joueur=ui->comboBox_idjoueur->currentText().toInt();
//    int id_event=ui->comboBox_idevent->currentText().toInt();

////    Affecterjoueur A(id_joueur,id_event);

////    QString message = A.ajouterjoueurevent();

//    if(QString::compare(message,"joueur affecte", Qt::CaseInsensitive) == 0) {
//        ui->comboBox_predevent->setModel(EV.getidev());
//        QMessageBox::information(this,"Affectation avec succe",message);
//    } else {
//        QMessageBox::critical(this,"Affectation non realise",message);
//    }
//}

void gestion_des_stades::on_comboBox_idevent_currentIndexChanged(const QString &arg1)
{
    Event* e = EV.getevent((&arg1)->toInt());

    ui->lineEdit_typeeventaff->setText(e->gettypeevent());
}

void gestion_des_stades::on_comboBox_predevent_currentIndexChanged(const QString &arg1)
{
    EV.getevent((&arg1)->toInt());
}

//void gestion_des_stades::on_pushButton_5_clicked()
//{
////    Affecterjoueur A1;
//    A1.predictionExcel(ui->comboBox_predevent->currentText());
//    ui->tableView_affectation->setModel(pred.afficherpredictionevnt(ui->comboBox_predevent->currentText()));
//    QMessageBox::information(nullptr, QObject::tr("OK"),
//                QObject::tr("prediction effectué\n"
//                            "Click Cancel to exit."), QMessageBox::Cancel);




//}

void gestion_des_stades::on_pushButton_Afficherevent_clicked()
{
    ui->tableView_affectation->setModel(EV.afficher());
}

void gestion_des_stades::on_pushButton_afficherprediction_clicked()
{
//    ui->tableView_affectation->setModel(pred.afficherprediction());
}

/*void MainWindow::on_radioButton_triertype_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trierpartype());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }
}*/

void gestion_des_stades::on_comboBox_mapidstade_currentIndexChanged(const QString &arg1)
{
 sta.getstade((&arg1)->toInt());
}



void gestion_des_stades::on_pushButton_affichermap_2_clicked()
{
    int cap = ui->comboBox_stadeaff->currentText().toInt();
    Stade* s=sta.afficherimage(cap);
    QImage yourImage("C:/Users/asus/Desktop/Nouveau dossier/foot.jpg");
    QString typeJeu = "Terrain de Football";
    QString typestade=s->gettype();
    if(QString::compare(typestade,typeJeu,Qt::CaseInsensitive) == 0)
    {

         //QLabel image =new QLabel(centralwidget);
         //ui->label_affichemap->setGeometry(QRect(20, 10, 371, 311));
         ui->label_affichemap->setPixmap(QPixmap(QPixmap::fromImage(yourImage)));
    }else
    {
        QImage yourImage("C:/Users/asus/Desktop/Nouveau dossier/handball.jpg");
         ui->label_affichemap->setPixmap(QPixmap(QPixmap::fromImage(yourImage)));
    }
}

void gestion_des_stades::on_checkBox_trierparcapacite_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trier());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }if(ui->checkBox_triertypestade->isChecked())
    {
         ui->tab_stade->setModel(sta.trierpartypeetcapacite());
    }
}
// tri------------------------------------------------------------------------
void gestion_des_stades::on_checkBox_trirerparlettre_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trierparnom());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }if(ui->checkBox_triertypestade->isChecked())
    {
         ui->tab_stade->setModel(sta.trierpartypeetnom());
    }

}

void gestion_des_stades::on_checkBox_triertypestade_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trierpartype());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }
    if(ui->checkBox_trierparcapacite->isChecked())
    {
         ui->tab_stade->setModel(sta.trierpartypeetcapacite());
    }if(ui->checkBox_trirerparlettre->isChecked())
    {
         ui->tab_stade->setModel(sta.trierpartypeetnom());
    }
}



