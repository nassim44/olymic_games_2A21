//#include "statj.h"
//#include "ui_statj.h"
//#include <QtCharts>
//#include <QChartView>
//#include <QPieSeries>
//#include <QSqlQuery>

//statj::statj(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::statj)
//{
//    ui->setupUi(this);
//    QPieSeries *series =new QPieSeries ;

//    QList<qreal> list= stat_j();
//     QList<QString> list2=stat_j_nom();

//     for(int i=0 ;i<list.size();i++)
//     {
//          series->append(list2[i],list[i]);

//     }
//        QChart *chart =new QChart;
//        chart->addSeries(series);
//        chart->setTitle("STATS des joueur");
//         QChartView *chartview= new QChartView(chart);
//         chartview->setParent(ui->horizontalFrame);
//}


//statj::~statj()
//{
//    //delete ui;
//}
//QList<qreal> statj::stat_j()
//{
//    QList<qreal> list ;
//    QSqlQuery query;
//    query.prepare("select pays,count(pays) from joueur group by pays");
//    query.exec();
//    while(query.next())
//    {list.append(query.value(1).toInt());}

//    return list;
//}

//QList<QString> statj::stat_j_nom()
//{QList<QString> list ;
//    QSqlQuery query;
//    query.prepare("select pays,count(pays) from joueur group by pays");
//    query.exec();
//    while(query.next())
//    {list.append(query.value(0).toString());}

//  return list;

//}

