#ifndef SAHARWINDOW_H
#define SAHARWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class saharwindow; }
QT_END_NAMESPACE

class saharwindow : public QMainWindow
{
    Q_OBJECT

public:
    saharwindow(QWidget *parent = nullptr);
    ~saharwindow();

private:
    Ui::saharwindow *ui;
};
#endif // SAHARWINDOW_H
