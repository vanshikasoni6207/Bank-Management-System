#include "createaccount.h"
#include "ui_createaccount.h"
#include <QMessageBox>
#include <fstream>
#include <QResizeEvent>
#include <QRegularExpression>
using namespace std;
CreateAccount::CreateAccount(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
}
void CreateAccount::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int w= ui->centralwidget->width();
    ui->centralwidget->height();
    int boxWidth = qMin(400,w-160);
    int left = (w-boxWidth)/2;
    ui->calabel->setGeometry(left,30,boxWidth,45);
    ui->aclabel->setGeometry(left,100,boxWidth,25);
    ui->txtAccountNo->setGeometry(left,125,boxWidth,40);
    ui->namelabel->setGeometry(left,180,boxWidth,25);
    ui->txtName->setGeometry(left,205,boxWidth,40);
    ui->pinlabel->setGeometry(left,260,boxWidth,25);
    ui->txtPin->setGeometry(left,285,boxWidth,40);
    ui->balancelabel->setGeometry(left,340,boxWidth,25);
    ui->txtBalance->setGeometry(left,365,boxWidth,40);
    int buttonWidth=qMin(220,w-100);
    int buttonLeft=(w-buttonWidth)/2;
    ui->btncreateaccount->setGeometry(buttonLeft,425,buttonWidth,45);
    ui->btnBack->setGeometry((w-100)/2,480,100,35);
}
CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_btnBack_clicked()
{
    close();
}

void CreateAccount::on_btncreateaccount_clicked()
{

        QString acc = ui->txtAccountNo->text().trimmed();
        QString name = ui->txtName->text().trimmed();
        QString pin = ui->txtPin->text();
        QString balance = ui->txtBalance->text().trimmed();

        // Validate account number
        if (!acc.contains(QRegularExpression("^[0-9]{8,18}$")))
        {
            QMessageBox::warning(
                this, "Error",
                "Account number must contain 8 to 18 digits.");
            return;
        }

        // Validate PIN
        if (!pin.contains(QRegularExpression("^[0-9]{6}$")))
        {
            QMessageBox::warning(
                this, "Error",
                "PIN must contain exactly 6 digits.");
            return;
        }

        // Validate name
        if (name.isEmpty())
        {
            QMessageBox::warning(this, "Error", "Enter your name.");
            return;
        }

        // Validate initial balance
        bool balanceOk = false;
        double initialBalance = balance.toDouble(&balanceOk);

        if (!balanceOk || initialBalance < 0 ||
            !qIsFinite(initialBalance))
        {
            QMessageBox::warning(
                this, "Error",
                "Enter a valid, non-negative initial balance.");
            return;
        }

        const char *filePath =
            R"(D:\c ++\Bankinsystem project\output\Bank.txt)";

        // Check whether the account number already exists
        ifstream inputFile(filePath);

        if (!inputFile)
        {
            QMessageBox::critical(
                this, "Error",
                "Unable to read account records.");
            return;
        }

        string fileAcc, fileName, filePin, fileBalance;

        while (getline(inputFile, fileAcc))
        {
            // Every account must have four lines
            if (!getline(inputFile, fileName) ||
                !getline(inputFile, filePin) ||
                !getline(inputFile, fileBalance))
            {
                inputFile.close();

                QMessageBox::critical(
                    this, "Data Error",
                    "Bank.txt contains an incomplete account record.");
                return;
            }

            if (QString::fromStdString(fileAcc).trimmed() == acc)
            {
                inputFile.close();

                QMessageBox::warning(
                    this, "Duplicate Account",
                    "This account number already exists. "
                    "Please use a different account number.");
                return;
            }
        }

        if (inputFile.bad())
        {
            inputFile.close();

            QMessageBox::critical(
                this, "Error",
                "Unable to read account records completely.");
            return;
        }

        inputFile.close();

        // Save the account only after validation and duplicate checking
        ofstream outputFile(filePath, ios::app);

        if (!outputFile)
        {
            QMessageBox::critical(
                this, "Error",
                "Unable to save account details.");
            return;
        }

        // Store account number and PIN as strings
        outputFile << acc.toStdString() << '\n';
        outputFile << name.toStdString() << '\n';
        outputFile << pin.toStdString() << '\n';
        outputFile << initialBalance << '\n';

        outputFile.close();

        if (!outputFile)
        {
            QMessageBox::critical(
                this, "Error",
                "Account data could not be saved correctly.");
            return;
        }

        QMessageBox::information(
            this, "Success",
            "Account created successfully!");

        ui->txtAccountNo->clear();
        ui->txtName->clear();
        ui->txtPin->clear();
        ui->txtBalance->clear();
    }
