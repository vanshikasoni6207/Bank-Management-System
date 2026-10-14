#ifndef ACCOUNTDASHBOARD_H
#define ACCOUNTDASHBOARD_H
#include <QString>
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
namespace Ui {
class AccountDashboard;
}

class AccountDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountDashboard(const QString &accountNo, QWidget *parent = nullptr);
    ~AccountDashboard();
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:

    void on_chbalancebtn_clicked();

    void on_depositbtn_clicked();

    void on_accdetbtn_clicked();

    void on_logoutbtn_clicked();

    void on_Withdrawbtn_clicked();

    void on_changepinbtn_clicked();

private:
    Ui::AccountDashboard *ui;
    QString accountnumber;
     void resizeWidgets();
    void showMessage(
        const QString &title,
        const QString &message,
        QMessageBox::Icon icon);
     void styleInputDialog(QInputDialog &dialog);
};

#endif // ACCOUNTDASHBOARD_H
