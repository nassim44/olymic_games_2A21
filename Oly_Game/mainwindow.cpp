#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "facture.h"
#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableWidget>
#include <QDate>
#include <QTextDocument>
#include <QFileDialog>
#include <QFile>
#include <QtPrintSupport/QAbstractPrintDialog>
#include "statistiques.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
       ui->show_fact->setModel(F.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajout_clicked()
{
    int id=ui->li_id->text().toInt();
     QDate date=ui->li_date->date();
     QString designation=ui->li_designation->text();
     int prix=ui->li_prix->text().toInt();
     int quantite=ui->li_qt->text().toInt();
     int total=ui->li_total->text().toInt();

Facture F(id, date, designation, prix, quantite, total);
bool test=F.ajouter();

            if(test)
                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Ajout effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                  ui->show_fact->setModel(F.afficher());

                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Ajout non effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }
}

void MainWindow::on_show_fact_activated(const QModelIndex &index)
{
    QString val=ui->show_fact->model()->data(index).toString();
    QSqlQuery qry ;
       qry.prepare("SELECT * from FACTURE  where ID='"+val+"' ");
       if(qry.exec())
       {
           while(qry.next())
           {


               ui->li_id->setText(qry.value(0).toString());
               ui->li_date->setDate(qry.value(1).toDate());
               ui->li_designation->setText(qry.value(2).toString());
               ui->li_prix->setText(qry.value(3).toString());
               ui->li_qt->setText(qry.value(4).toString());
               ui->li_total->setText(qry.value(3).toString());



           }
       }
}

void MainWindow::on_Supprimer_clicked()
{
    int cin =ui->li_id->text().toInt();
     bool test=F.supprimer(cin);
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->show_fact->setModel(F.afficher());

       }
   else
       {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       }
}

void MainWindow::on_modifier_clicked()
{
    int id=ui->li_id->text().toInt();
     QDate date=ui->li_date->date();
     QString designation=ui->li_designation->text();
     int prix=ui->li_prix->text().toInt();
     int quantite=ui->li_qt->text().toInt();
     int total=ui->li_total->text().toInt();



     Facture F(id,date,designation,prix,quantite,total);


    bool test=F.modifier();
    if(test)

        {
        QMessageBox::information(nullptr,QObject::tr("Ok"),
        QObject::tr("Modification effectuée\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);


        ui->show_fact->setModel(F.afficher());

        }
    else
        {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                             QObject::tr("Modification non effectuée\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);

        }
}


void MainWindow::on_stat_clicked()
{
    statistiques *a=new statistiques();
      a->show();
}

//***************RECHERCHER TICKERT ***********
void MainWindow::on_ajout_2_clicked()
{
    QString choix;
            choix=ui->li_chercher->text();
            QString li_rechercher=ui->li_chercher->text();
            ui->show_fact->setModel(F.chercher(li_rechercher));

}

void MainWindow::on_TRI_date_clicked()
{
     ui->show_fact->setModel(F.tri_date());
}

void MainWindow::on_TRI_prix_clicked()
{
    ui->show_fact->setModel(F.tri_prix());

}

void MainWindow::on_PDF_clicked()
{
    QString strStream;
               QTextStream out(&strStream);
                               const int rowCount = ui->show_fact->model()->rowCount();
                               const int columnCount = ui->show_fact->model()->columnCount();
                               QString TT = QDate::currentDate().toString("yyyy/MM/dd");



                               out <<  "<html>\n"
                                   "<head>\n"
                                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                   <<  QString("<title>%1</title>\n").arg("strTitle")
                                   <<  "</head>\n"
                                   "<body bgcolor=#ffffff link=#5000A0>\n"
                                       "<h1 style=\"text-align: center;\">"
                                       "<strong>                                                      "+TT+" </ strong>"


                                  //     "<align='right'> " << datefich << "</align>"

                                   "<center> <H1> LES FACTURES </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";


                               // headers
                               out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                               for (int column = 0; column < columnCount; column++)
                                   if (!ui->show_fact->isColumnHidden(column))
                                       out << QString("<th>%1</th>").arg(ui->show_fact->model()->headerData(column, Qt::Horizontal).toString());
                               out << "</tr></thead>\n";

                               // data table
                               for (int row = 0; row < rowCount; row++) {
                                   out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                   for (int column = 0; column < columnCount; column++) {
                                       if (!ui->show_fact->isColumnHidden(column)) {
                                           QString data = ui->show_fact->model()->data(ui->show_fact->model()->index(row, column)).toString().simplified();
                                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                       }
                                   }
                                   out << "</tr>\n";
                               }
                               out <<  "</table> </center>\n"
                                   "</body>\n"
                                   "</html>\n";


                               QTextDocument *document = new QTextDocument();
                               document->setHtml(strStream);
                               QPrinter printer;

                               QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                               if (dialog->exec() == QDialog::Accepted) {
                                   document->print(&printer);
                               }


                               delete document;
}
