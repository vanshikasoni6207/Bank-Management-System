#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "createaccount.h"
#include "Login.h"
#include <QResizeEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(800,600);
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int x=(width()-ui->btnCreateAccount->width())/2;
    ui->btnCreateAccount->move(x,200);
    ui->btnLogin->move(x,270);
    ui->btnExit->move(x,340);
    ui->mainlabel->move((width()-ui->mainlabel->width())/2,50);
    ui->Bankicon->move((width()-ui->mainlabel->width())/2.9,50);
    ui->welcomelabel->move((width()-ui->welcomelabel->width())/2,100);
    ui->notelabel->move((width()-ui->notelabel->width())/2,130);
    int iconSize = ui->btnCreateAccount->height() * 0.45;

    ui->btnCreateAccount->setIconSize(QSize(iconSize, iconSize));
    ui->btnLogin->setIconSize(QSize(iconSize, iconSize));
    ui->btnExit->setIconSize(QSize(iconSize, iconSize));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnExit_clicked()
{
    close();
}


void MainWindow::on_btnCreateAccount_clicked()
{
    CreateAccount *window = new CreateAccount(this);
    window->show();
}


void MainWindow::on_btnLogin_clicked()
{
    Login *window = new Login(this);
    window->show();
}

