#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include <QDialog>
#include <QtSql/QSqlQuery>
#include "todolist.h"
#include <QFileDialog>
#include <QFile>
#include <QSortFilterProxyModel>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include "exportexcelobject.h"
#include<QWidget>
#include<QtSvg/QSvgRenderer>
#include<QDirModel>
#include"qrcode.h"
#include<fstream>
using qrcodegen::QrCode;
using qrcodegen::QrSegment;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->show_staff->setModel(S.afficher());
    connect(ui->sendBtn_3, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn_3, SIGNAL(clicked()), this, SLOT(browse()));
    
}

MainWindow::~MainWindow()
{
    
    delete ui;
}


void MainWindow::on_ajout_clicked()
{
                  int CIN=ui->li_cin->text().toInt();
                  QString NOM=ui->li_nom->text();
                  QString PRENOM=ui->li_prenom->text();
                  QString TYPES =ui->li_types->currentText();

                  Staff S (CIN,NOM,PRENOM,TYPES);
                  bool test=S.ajouter();

                          if(test)
                              {
                              QMessageBox::information(nullptr,QObject::tr("Ok"),
                                                   QObject::tr("Ajout effectué\n"
                                                                 "Click cancel to exit."),QMessageBox::Cancel);
                                ui->show_staff->setModel(S.afficher());

                              }
                          else
                              {
                              QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                                   QObject::tr("Ajout non effectué\n"
                                                                 "Click cancel to exit."),QMessageBox::Cancel);
                              }
}

void MainWindow::on_show_staff_activated(const QModelIndex &index)
{
    QString val=ui->show_staff->model()->data(index).toString();
    QSqlQuery qry ;
       qry.prepare("SELECT * from STAFF  where CIN='"+val+"' ");
       if(qry.exec())
       {
           while(qry.next())
           {


               ui->li_cin->setText(qry.value(0).toString());
               ui->li_nom->setText(qry.value(1).toString());
               ui->li_prenom->setText(qry.value(2).toString());
               ui->li_types->setCurrentText(qry.value(3).toString());

           }
       }
       ui->li_cin->setText(ui->show_staff->model()->data(ui->show_staff->model()->index(index.row(),0)).toString());
}

void MainWindow::on_Supprimer_clicked()
{
    int cin =ui->li_cin->text().toInt();
     bool test=S.supprimer(cin);
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->show_staff->setModel(S.afficher());

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

               int CIN=ui->li_cin->text().toInt();
               QString NOM=ui->li_nom->text();
               QString PRENOM=ui->li_prenom->text();
              QString TYPES=ui->li_types->currentText();



           Staff S (CIN,NOM,PRENOM,TYPES);


               bool test=S.modifier();
               if(test)

                   {
                   QMessageBox::information(nullptr,QObject::tr("Ok"),
                   QObject::tr("Modification effectuée\n"
                                                      "Click cancel to exit."),QMessageBox::Cancel);


                   ui->show_staff->setModel(S.afficher());

                   }
               else
                   {
                   QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                        QObject::tr("Modification non effectuée\n"
                                                      "Click cancel to exit."),QMessageBox::Cancel);

                   }
}

void MainWindow::on_Vider_clicked()
{
    ui->li_cin->setText("");
    ui->li_nom->setText("");
    ui->li_prenom->setText("");

}

void MainWindow::on_tri_nom_clicked()
{
 ui->show_staff->setModel(S.afficher_tri_nom());
}

void MainWindow::on_tri_prenom_clicked()
{
    ui->show_staff->setModel(S.afficher_tri_prenom());

}

void MainWindow::on_chercher_clicked()
{
    QString choix;
            choix=ui->li_rechercher->text();
            QString li_rechercher=ui->li_rechercher->text();
            ui->show_staff->setModel(S.chercher_staff(li_rechercher));
}

void MainWindow::on_todo_clicked()
{
    app=new CToDoList();
    app->show();
}
void  MainWindow::browse()
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

    ui->file_3->setText( fileListString );

}


void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mouhamed.abbassi@esprit.tn",ui->mail_pass_3->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mouhamed.abbassi@esprit.tn", ui->rcpt_3->text() , ui->subject_3->text(),ui->msg_3->toPlainText(), files );
    else
        smtp->sendMail("mouhamed.abbassi@esprit.tn", ui->rcpt_3->text() , ui->subject_3->text(),ui->msg_3->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt_3->clear();
    ui->subject_3->clear();
    ui->file_3->clear();
    ui->msg_3->clear();
    ui->mail_pass_3->clear();
}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                                const int rowCount = ui->show_staff->model()->rowCount();
                                const int columnCount = ui->show_staff->model()->columnCount();
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
                                    "<center> <H1> Liste Staff </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";


                                // headers
                                out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                for (int column = 0; column < columnCount; column++)
                                    if (!ui->show_staff->isColumnHidden(column))
                                        out << QString("<th>%1</th>").arg(ui->show_staff->model()->headerData(column, Qt::Horizontal).toString());
                                out << "</tr></thead>\n";

                                // data table
                                for (int row = 0; row < rowCount; row++) {
                                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                    for (int column = 0; column < columnCount; column++) {
                                        if (!ui->show_staff->isColumnHidden(column)) {
                                            QString data = ui->show_staff->model()->data(ui->show_staff->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_XL_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->show_staff);

        //colums to export
        obj.addField(0, "CIN", "char(20)");
        obj.addField(1, "NOM", "char(20)");
        obj.addField(2, "PRENOM", "char(20)");
        obj.addField(3, "TYPES", "char(20)");



        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}

void MainWindow::on_qr_2_clicked()
{
    if(ui->show_staff->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                            QObject::tr("Veuillez Choisir un identifiant.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {

                    int li_cin=ui->show_staff->model()->data(ui->show_staff->model()->index(ui->show_staff->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(li_cin).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    svgRenderer.render( &pixPainter );
                    ui->QRCODE->setPixmap(pix);

               }
}
