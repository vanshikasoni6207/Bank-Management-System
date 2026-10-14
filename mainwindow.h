#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    void resizeEvent(QResizeEvent *event)override;

private slots:
    void on_btnExit_clicked();

    void on_btnCreateAccount_clicked();

    void on_btnLogin_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
