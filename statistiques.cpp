#include "statistiques.h"
#include "ui_statistiques.h"

statistiques::statistiques(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statistiques)
{
    ui->setupUi(this);
    QPieSeries *series=new QPieSeries();
    series->append("< 500",tmpf.calcul_facture(0,500));
    series->append("[500..1000]",tmpf.calcul_facture(500,1000));
    series->append("[1000..1500]",tmpf.calcul_facture(1000,1500));
    series->append("[1500..2000]",tmpf.calcul_facture(1500,2000));

    QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("les prix des factures");
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartview=new QChartView(chart);

    this->setCentralWidget(chartview);
}

statistiques::~statistiques()
{
    delete ui;
}
