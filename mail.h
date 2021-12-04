#ifndef MAIL_H
#define MAIL_H

#include <QMainWindow>

namespace Ui {
class Mail;
}

class Mail : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mail(QWidget *parent = nullptr);
    ~Mail();

private:
    Ui::Mail *ui;
};

#endif // MAIL_H
