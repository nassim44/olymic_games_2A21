#ifndef CRUDMETIER_H
#define CRUDMETIER_H

#include <QDialog>

namespace Ui {
class crudmetier;
}

class crudmetier : public QDialog
{
    Q_OBJECT

public:
    explicit crudmetier(QWidget *parent = nullptr);
    ~crudmetier();

private:
    Ui::crudmetier *ui;
};

#endif // CRUDMETIER_H
