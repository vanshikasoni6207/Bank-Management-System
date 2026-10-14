#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
protected:
    void resizeEvent(QResizeEvent *event)override;
private slots:
    void on_backbutton_clicked();

    void on_loginbutton_clicked();



private:
    Ui::Login *ui;
};

#endif // LOGIN_H
