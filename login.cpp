#include "login.h"
#include "accountdashboard.h"
#include "ui_login.h"
#include <QMessageBox>
#include <fstream>
#include <QRegularExpression>
#include <string>
using namespace std;
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
void Login::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int w= ui->centralwidget->width();
    int boxWidth=qMin(400,w-160);
    int left = (w-boxWidth)/2;
    ui->login->setGeometry(left,40,boxWidth,50);
    ui->login->setAlignment(Qt::AlignCenter);
    ui->accnolabel->setGeometry(left,130,boxWidth,25);
    ui->txtaccno->setGeometry(left,155,boxWidth,40);
    ui->pinlabel->setGeometry(left,220,boxWidth,25);
    ui->txtpin->setGeometry(left,245,boxWidth,40);
    int buttonwidth=qMin(220,w-100);
    int buttonleft=(w-buttonwidth)/2;
    ui->loginbutton->setGeometry(buttonleft,320,buttonwidth,45);
    ui->backbutton->setGeometry((w-100)/2,380,100,35);
}

void Login::on_loginbutton_clicked()
{

        QString acc = ui->txtaccno->text().trimmed();
        QString pin = ui->txtpin->text();

        // Validate account number
        if (!acc.contains(QRegularExpression("^[0-9]{8,18}$")))
        {
            QMessageBox::warning(
                this, "Invalid Input",
                "Account number must contain 8 to 18 digits.");
            return;
        }

        // Validate PIN
        if (!pin.contains(QRegularExpression("^[0-9]{6}$")))
        {
            QMessageBox::warning(
                this, "Invalid Input",
                "PIN must contain exactly 6 digits.");
            return;
        }

        ifstream file(
            R"(D:\c ++\Bankinsystem project\output\Bank.txt)");

        if (!file)
        {
            QMessageBox::critical(
                this, "Error",
                "Unable to fetch account details.");
            return;
        }

        string fileAcc, name, filePin, balance;
        bool found = false;
        bool invalidData = false;

        while (getline(file, fileAcc))
        {
            // Read the remaining three fields
            if (!getline(file, name) ||
                !getline(file, filePin) ||
                !getline(file, balance))
            {
                invalidData = true;
                break;
            }

            // Reject malformed account records
            QString storedAcc =
                QString::fromStdString(fileAcc).trimmed();
            QString storedPin =
                QString::fromStdString(filePin).trimmed();

            if (!storedAcc.contains(
                    QRegularExpression("^[0-9]{8,18}$")) ||
                !storedPin.contains(
                    QRegularExpression("^[0-9]{6}$")))
            {
                invalidData = true;
                break;
            }

            if (storedAcc == acc && storedPin == pin)
            {
                found = true;
                break;
            }
        }

        if (file.bad())
            invalidData = true;

        file.close();

        if (invalidData)
        {
            QMessageBox::critical(
                this, "Data Error",
                "Account data is incomplete or invalid.");
            return;
        }

        if (found)
        {
            QMessageBox::information(
                this, "Login Successful",
                "Welcome, " + QString::fromStdString(name) + "!");

            AccountDashboard *dashboard =
                new AccountDashboard(acc);

            dashboard->show();
            close();
        }
        else
        {
            QMessageBox::warning(
                this, "Login Failed",
                "Invalid account number or PIN.");
        }
    }



void Login::on_backbutton_clicked()
{
    close();
}

