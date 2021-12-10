#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stade.h"
#include <QApplication>
#include <QMessageBox>
//#include "stade.h"
#include <QIntValidator>
#include "event.h"
#include "affecterjoueur.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(verifiercode()));

    ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_capacite->setValidator(new QIntValidator(0,99999999,this));
    ui->tab_stade->setModel(sta.afficher());
    ui->tableView_affectation->setModel(event.afficher());
    ui->comboBox_3->setModel(sta.getids());
    ui->comboBox_4->setModel(sta.getids());
    ui->comboBox_stadeaff->setModel(sta.getids());
    ui->comboBox_jeuxaff->setModel(jeux.getidj());
    ui->comboBox_idjoueur->setModel(jou.getidjou());
    ui->comboBox_idevent->setModel(event.getidev());
    ui->comboBox_predevent->setModel(event.getidev());
    //ui->checkBox_trierparcapacite->setChecked(true);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/Map.qml")));
    ui->quickWidget->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{

        int id=ui->lineEdit_id->text().toInt();
        int capacite=ui->lineEdit_capacite->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        QString type=ui->comboBox->currentText();


        Stade S(id,capacite,nom,type);
        bool test=S.ajouter();
        if(test)
        {
            ui->tab_stade->setModel(sta.afficher());
            ui->comboBox_3->setModel(sta.getids());
            ui->comboBox_4->setModel(sta.getids());
            ui->comboBox_stadeaff->setModel(sta.getids());

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("Ajout non effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_clicked()
{
    Stade S1; S1.setid(ui->comboBox_4->currentText().toInt());
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

void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->comboBox_3->currentText().toInt();
    int capacite =ui->lineEdit_capacite_2->text().toInt();
    QString nom=ui->lineEdit_nom_2->text();
    QString type=ui->comboBox_2->currentText();

    Stade S(id,capacite,nom,type);
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

/*void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trier());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }
}*/
/*void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trierparnom());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }
}*/

void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    Stade* s = sta.getstade((&arg1)->toInt());
    ui->lineEdit_nom_2->setText(s->getnom());
    ui->lineEdit_capacite_2->setText(QString::number(s->getcapacite()));
    int index = ui->comboBox_2->findText(s->gettype());
    if ( index != -1 ) {
       ui->comboBox_2->setCurrentIndex(index);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString nom = ui->lineEdit_nom_3->text();
    QString cap = ui->lineEdit_capacite_3->text();
    QString typestade=ui->comboBox_recherche->currentText();
    ui->tab_stade->setModel(sta.recherche(nom,cap,typestade));
}



void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_nom_3->setText("");
    ui->lineEdit_capacite_3->setText("");
    ui->tab_stade->setModel(sta.afficher());
}

void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{

    sta.getstade((&arg1)->toInt());

}


void MainWindow::on_comboBox_stadeaff_currentIndexChanged(const QString &arg1)
{
    sta.getstade((&arg1)->toInt());
}

void MainWindow::on_comboBox_jeuxaff_currentIndexChanged(const QString &arg1)
{
    jeux.getjeux((&arg1)->toInt());
}



void MainWindow::on_pb_affecterevent_clicked()
{

    int id_event=ui->lineEdit_idevent->text().toInt();
    int id_stade=ui->comboBox_stadeaff->currentText().toInt();
    int id_jeux=ui->comboBox_jeuxaff->currentText().toInt();
    QDateTime date=ui->dateTimeEdit->dateTime();


    Event e(id_event,id_stade,id_jeux,date);

    QString message = e.ajouterevent();
    ui->tableView_affectation->setModel(event.afficher());
    if(QString::compare(message,"Match affecte", Qt::CaseInsensitive) == 0)
    {
        ui->comboBox_idevent->setModel(event.getidev());

        ui->tableView_affectation->setModel(event.afficher());
        QMessageBox::information(this,"Affectation avec succe",message);
    } else {
        QMessageBox::critical(this,"Affectation non realise",message);
    }

}




void MainWindow::on_comboBox_idjoueur_currentIndexChanged(const QString &arg1)
{
    jou.getjoueur((&arg1)->toInt());
}

void MainWindow::on_pushButton_3_clicked()
{



    int id_joueur=ui->comboBox_idjoueur->currentText().toInt();
    int id_event=ui->comboBox_idevent->currentText().toInt();

    Affecterjoueur A(id_joueur,id_event);

    QString message = A.ajouterjoueurevent();

    if(QString::compare(message,"joueur affecte", Qt::CaseInsensitive) == 0) {
        ui->comboBox_predevent->setModel(event.getidev());
        QMessageBox::information(this,"Affectation avec succe",message);
    } else {
        QMessageBox::critical(this,"Affectation non realise",message);
    }
}

void MainWindow::on_comboBox_idevent_currentIndexChanged(const QString &arg1)
{
    Event* e = event.getevent((&arg1)->toInt());

    ui->lineEdit_typeeventaff->setText(e->gettypeevent());
}

void MainWindow::on_comboBox_predevent_currentIndexChanged(const QString &arg1)
{
    event.getevent((&arg1)->toInt());
}

void MainWindow::on_pushButton_5_clicked()
{
    Affecterjoueur A1;
    A1.predictionExcel(ui->comboBox_predevent->currentText());
    ui->tableView_affectation->setModel(pred.afficherpredictionevnt(ui->comboBox_predevent->currentText()));
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("prediction effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_pushButton_Afficherevent_clicked()
{
    ui->tableView_affectation->setModel(event.afficher());
}

void MainWindow::on_pushButton_afficherprediction_clicked()
{
    ui->tableView_affectation->setModel(pred.afficherprediction());
}

/*void MainWindow::on_radioButton_triertype_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trierpartype());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }
}*/

void MainWindow::on_comboBox_mapidstade_currentIndexChanged(const QString &arg1)
{
 sta.getstade((&arg1)->toInt());
}



void MainWindow::on_pushButton_affichermap_2_clicked()
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

void MainWindow::on_checkBox_trierparcapacite_toggled(bool checked)
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

void MainWindow::on_checkBox_trirerparlettre_toggled(bool checked)
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

void MainWindow::on_checkBox_triertypestade_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trierpartype());
        //ui->label_arduino->setText("ON");
        /*A.write_to_arduino("1");
        data=A.read_from_arduino();
        QByteArray code=jou.verifier_code_bd(data);
        if(code != "code n'existe pas")
            //A.write_to_arduino(code);
            qDebug() << "arduino";
        else if (data=="code n'existe pas")
            //A.write_to_arduino("You can't enter");
        qDebug() << "arduino is not";*/

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

//------------------------- arduino-----------------------------
/*void MainWindow::verifiercode()
{
    data=A.read_from_arduino();
    QByteArray code=jou.verifier_code_bd(data);
    if(code != "code n'existe pas")
        //A.write_to_arduino(code);
        qDebug() << "arduino";
    else if (data=="code n'existe pas")
        //A.write_to_arduino("You can't enter");
    qDebug() << "arduino is not";
}*/
void MainWindow::update_label()
{
    data=A.read_from_arduino();
    qDebug() << data;

//QString dataasstring=QString(data);
QByteArray code=jou.verifier_code_bd(data);
if(code != "code n'existe pas"){
    A.write_to_arduino("1");
    qDebug() << "mawjoud fel base de données";
    QMessageBox::information(nullptr, QObject::tr("arduino"),
                    QObject::tr("carte existe\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
if(code =="code n'existe pas")
{

    qDebug() << "mehouch mawjoud fel BD";
QMessageBox::information(nullptr, QObject::tr("arduino"),
                QObject::tr("carte n'existe pas\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

        ui->lineEdit_ard->setText(data);

}

