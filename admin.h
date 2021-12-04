#ifndef ADMIN_H
#define ADMIN_H
#include<QSqlQuery>
#include<QString>
#include <QMainWindow>

namespace Ui {
class admin;
}

class admin : public QMainWindow
{
    Q_OBJECT
//---------------------------------



//---------------------------------

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
    bool login(QString,QString);


private slots:
    //bool on_pushButton_authentifier_clicked();

    void on_pushButton_admin_clicked();

private:
    Ui::admin *ui;

};

#endif // ADMIN_H
