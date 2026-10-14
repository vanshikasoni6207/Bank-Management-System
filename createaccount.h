#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QMainWindow>

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

protected:
    void resizeEvent(QResizeEvent *event)override;
private slots:
    void on_btnBack_clicked();
    void on_btncreateaccount_clicked();

private:
    Ui::CreateAccount *ui;
};

#endif // CREATEACCOUNT_H