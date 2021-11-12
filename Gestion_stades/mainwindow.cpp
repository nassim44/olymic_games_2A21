#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stade.h"
#include <QApplication>
#include <QMessageBox>
//#include "stade.h"
#include <QIntValidator>
#include "event.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_capacite->setValidator(new QIntValidator(0,99999999,this));
    ui->tab_stade->setModel(sta.afficher());
    ui->tableView_affectation->setModel(event.afficher());
    ui->comboBox_3->setModel(sta.getids());
    ui->comboBox_4->setModel(sta.getids());
    ui->comboBox_stadeaff->setModel(sta.getids());
    ui->comboBox_jeuxaff->setModel(jeux.getidj());
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

void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trier());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (checked == true){
        ui->tab_stade->setModel(sta.trierparnom());
    } else {
         ui->tab_stade->setModel(sta.afficher());
    }
}

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
    ui->tab_stade->setModel(sta.recherche(nom,cap));
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


    int id_stade=ui->comboBox_stadeaff->currentText().toInt();
    int id_jeux=ui->comboBox_jeuxaff->currentText().toInt();
    QDateTime date=ui->dateTimeEdit->dateTime();


    Event e(id_stade,id_jeux,date);

    QString message = e.ajouterevent();
    if(QString::compare(message,"Match affecte", Qt::CaseInsensitive) == 0) {
        QMessageBox::information(this,"Affectation avec succe",message);
    } else {
        QMessageBox::critical(this,"Affectation non realise",message);
    }

}
