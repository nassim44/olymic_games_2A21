#ifndef STAF_H
#define STAF_H

#include <QDialog>

namespace Ui {
class Staf;
}

class Staf : public QDialog
{
    Q_OBJECT

public:
    explicit Staf(QWidget *parent = nullptr);
    ~Staf();

private:
    Ui::Staf *ui;
};

#endif // STAF_H
