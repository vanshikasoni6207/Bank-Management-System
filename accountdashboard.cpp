#include "accountdashboard.h"
#include <fstream>
#include "ui_accountdashboard.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <string>
#include <QString>
#include <QInputDialog>
#include <QResizeEvent>
#include <vector>
#include <QtMath>
#include <QSaveFile>
#include <QTextStream>
using namespace std;

struct AccountRecord
{
    string accno;
    string name;
    string pin;
    string balance;
};
bool saveBankData(
    const QString &filePath,
    const std::vector<AccountRecord> &records)
{
    QSaveFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    for (const AccountRecord &record : records)
    {
        out << QString::fromStdString(record.accno) << '\n';
        out << QString::fromStdString(record.name) << '\n';
        out << QString::fromStdString(record.pin) << '\n';
        out << QString::fromStdString(record.balance) << '\n';
    }

    out.flush();

    if (out.status() != QTextStream::Ok)
    {
        file.cancelWriting();
        return false;
    }

    return file.commit();
}

AccountDashboard::AccountDashboard(const QString &accountNo, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AccountDashboard)
{
    ui->setupUi(this);

    accountnumber = accountNo;

    // Minimum window size
    setMinimumSize(600, 500);

    // Main window background
    this->setStyleSheet(
        "QMainWindow {"
        "background-color: #202124;"
        "}"
        );

    // Main Dashboard Label
    ui->ADlabel->setStyleSheet(
        "QLabel {"
        "color: #F5E6C8;"
        "font-size: 28px;"
        "font-weight: bold;"
        "}"
        );

    ui->ADlabel->setAlignment(Qt::AlignCenter);


    // Common button style
    QString buttonStyle =
        "QPushButton {"
        "background-color: #2D2F33;"
        "color: #F5E6C8;"
        "border: 1px solid #B89B5E;"
        "border-radius: 12px;"
        "font-size: 16px;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "background-color: #393B40;"
        "}"
        "QPushButton:pressed {"
        "background-color: #242529;"
        "}";


    // Button styles
    ui->chbalancebtn->setStyleSheet(buttonStyle);
    ui->depositbtn->setStyleSheet(buttonStyle);
    ui->Withdrawbtn->setStyleSheet(buttonStyle);
    ui->accdetbtn->setStyleSheet(buttonStyle);
    ui->changepinbtn->setStyleSheet(buttonStyle);


    // Logout button
    ui->logoutbtn->setStyleSheet(
        "QPushButton {"
        "background-color: #34363A;"
        "color: #F5E6C8;"
        "border: 1px solid #B89B5E;"
        "border-radius: 12px;"
        "font-size: 15px;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "background-color: #44464B;"
        "}"
        );


    // Initial positioning
    resizeWidgets();
}

void AccountDashboard::showMessage(
    const QString &title,
    const QString &message,
    QMessageBox::Icon icon)
{
    QMessageBox msgBox(this);

    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setIcon(icon);

    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: #202124;"
        "}"
        "QLabel {"
        "    color: #F5E6C8;"
        "    font-size: 15px;"
        "    min-width: 280px;"
        "}"
        "QPushButton {"
        "    background-color: #2D2F33;"
        "    color: #F5E6C8;"
        "    border: 1px solid #B89B5E;"
        "    border-radius: 6px;"
        "    padding: 7px 22px;"
        "    min-width: 70px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #393B40;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #242529;"
        "}"
        );

    msgBox.exec();
}
void AccountDashboard::styleInputDialog(QInputDialog &dialog)
{
    dialog.setStyleSheet(
        "QInputDialog {"
        "    background-color: #202124;"
        "}"
        "QLabel {"
        "    color: #F5E6C8;"
        "    font-size: 15px;"
        "}"
        "QLineEdit, QDoubleSpinBox {"
        "    background-color: #2D2F33;"
        "    color: #F5E6C8;"
        "    border: 1px solid #B89B5E;"
        "    border-radius: 6px;"
        "    padding: 6px;"
        "}"
        "QPushButton {"
        "    background-color: #2D2F33;"
        "    color: #F5E6C8;"
        "    border: 1px solid #B89B5E;"
        "    border-radius: 6px;"
        "    padding: 7px 22px;"
        "    min-width: 70px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #393B40;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #242529;"
        "}"
        );
}
// Destructor
AccountDashboard::~AccountDashboard()
{
    delete ui;
}


// Responsive resizing
void AccountDashboard::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    resizeWidgets();
}


// Arrange widgets according to window size
void AccountDashboard::resizeWidgets()
{
    int w = width();
    int h = height();


    // =============================
    // Main Dashboard Label
    // =============================
    ui->ADlabel->setGeometry(
        w * 0.05,
        h * 0.08,
        w * 0.90,
        50
        );

    ui->ADlabel->setAlignment(Qt::AlignCenter);


    // =============================
    // Button dimensions
    // =============================
    int buttonWidth = w * 0.30;
    int buttonHeight = 55;

    int gap = w * 0.08;


    // Horizontal positions
    int leftX =
        (w - (2 * buttonWidth + gap)) / 2;

    int rightX =
        leftX + buttonWidth + gap;


    // =============================
    // First row
    // =============================
    int firstY = h * 0.25;


    // Check Balance
    ui->chbalancebtn->setGeometry(
        leftX,
        firstY,
        buttonWidth,
        buttonHeight
        );


    // Deposit
    ui->depositbtn->setGeometry(
        rightX,
        firstY,
        buttonWidth,
        buttonHeight
        );


    // =============================
    // Second row
    // =============================
    int secondY = firstY + 80;


    // Withdraw
    ui->Withdrawbtn->setGeometry(
        leftX,
        secondY,
        buttonWidth,
        buttonHeight
        );


    // Account Details
    ui->accdetbtn->setGeometry(
        rightX,
        secondY,
        buttonWidth,
        buttonHeight
        );


    // =============================
    // Change PIN
    // =============================
    int changePinWidth = w * 0.30;

    ui->changepinbtn->setGeometry(
        (w - changePinWidth) / 2,
        secondY + 80,
        changePinWidth,
        buttonHeight
        );


    // =============================
    // Logout
    // =============================
    int logoutWidth = w * 0.22;

    ui->logoutbtn->setGeometry(
        (w - logoutWidth) / 2,
        h * 0.82,
        logoutWidth,
        48
        );
}


// =============================
// CHECK BALANCE
// =============================
void AccountDashboard::on_chbalancebtn_clicked()
{
    ifstream file(R"(D:\c ++\Bankinsystem project\output\Bank.txt)");

    if (!file)
    {
        showMessage(
            "Error",
            "Bank file could not be opened.",
            QMessageBox::Warning
            );
        return;
    }

    string fileAcc, name, filePin, balance;
    bool found = false;

    while (getline(file, fileAcc) &&
           getline(file, name) &&
           getline(file, filePin) &&
           getline(file, balance))
    {
        if (fileAcc == accountnumber.toStdString())
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        showMessage(
            "Balance",
            "Balance = Rs." + QString::fromStdString(balance),
            QMessageBox::Information
            );
    }
    else
    {
        showMessage(
            "Error",
            "Account details not found.",
            QMessageBox::Warning
            );
    }
}


// =============================
// DEPOSIT
// =============================

void AccountDashboard::on_depositbtn_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle("Deposit");
    dialog.setLabelText("Enter deposit amount:");
    dialog.setInputMode(QInputDialog::DoubleInput);
    dialog.setDoubleValue(0);
    dialog.setDoubleRange(0, 1000000);
    dialog.setDoubleDecimals(2);
    styleInputDialog(dialog);

    if (dialog.exec() != QDialog::Accepted)
        return;

    double amount = dialog.doubleValue();

    if (!qIsFinite(amount) || amount <= 0)
    {
        showMessage("Error", "Enter a valid positive amount.",
                    QMessageBox::Warning);
        return;
    }

    const QString filePath =
        QStringLiteral("D:/c ++/Bankinsystem project/output/Bank.txt");

    ifstream file(filePath.toLocal8Bit().constData());

    if (!file)
    {
        showMessage("Error", "Bank file could not be opened.",
                    QMessageBox::Warning);
        return;
    }

    vector<AccountRecord> records;
    string accno, name, pin, balance;
    int targetIndex = -1;

    while (getline(file, accno))
    {
        if (!getline(file, name) ||
            !getline(file, pin) ||
            !getline(file, balance))
        {
            showMessage("Data Error",
                        "Bank file contains an incomplete record.",
                        QMessageBox::Warning);
            return;
        }

        bool balanceOk = false;
        double currentBalance =
            QString::fromStdString(balance).trimmed()
                .toDouble(&balanceOk);

        if (!balanceOk || !qIsFinite(currentBalance) ||
            currentBalance < 0)
        {
            showMessage("Data Error",
                        "Bank file contains an invalid balance.",
                        QMessageBox::Warning);
            return;
        }

        records.push_back({accno, name, pin, balance});

        if (accno == accountnumber.toStdString())
        {
            if (targetIndex != -1)
            {
                showMessage("Data Error",
                            "Duplicate account records found.",
                            QMessageBox::Warning);
                return;
            }

            targetIndex = static_cast<int>(records.size()) - 1;
        }
    }

    if (file.bad())
    {
        showMessage("Read Error", "Could not read Bank.txt completely.",
                    QMessageBox::Critical);
        return;
    }

    file.close();

    if (targetIndex == -1)
    {
        showMessage("Error", "Account not found.",
                    QMessageBox::Warning);
        return;
    }

    AccountRecord &account = records[targetIndex];

    bool balanceOk = false;
    double currentBalance =
        QString::fromStdString(account.balance).toDouble(&balanceOk);

    if (!balanceOk || amount > 1e12 - currentBalance)
    {
        showMessage("Error", "The resulting balance is invalid or too large.",
                    QMessageBox::Warning);
        return;
    }

    account.balance =
        QString::number(currentBalance + amount, 'f', 2).toStdString();

    if (!saveBankData(filePath, records))
    {
        showMessage("Save Error", "Deposit could not be saved.",
                    QMessageBox::Critical);
        return;
    }

    showMessage("Deposit Successful",
                "₹" + QString::number(amount, 'f', 2) +
                    " deposited successfully.",
                QMessageBox::Information);
}

// =============================
// ACCOUNT DETAILS
// =============================
void AccountDashboard::on_accdetbtn_clicked()
{
    ifstream file(
        R"(D:\c ++\Bankinsystem project\output\Bank.txt)"
        );

    if (!file)
    {
        showMessage(
            "Error",
            "Bank file could not be opened.",
            QMessageBox::Warning
            );
        return;
    }

    string fileAcc, balance, pin, name;
    bool found = false;

    while (getline(file, fileAcc) &&
           getline(file, name) &&
           getline(file, pin) &&
           getline(file, balance))
    {
        if (fileAcc == accountnumber.toStdString())
        {
            found = true;
            break;
        }
    }

    file.close();

    if (found)
    {
        showMessage(
            "Account Details",
            "Account Number: " +
                QString::fromStdString(fileAcc) +
                "\nName: " +
                QString::fromStdString(name) +
                "\nBalance: Rs." +
                QString::fromStdString(balance),
            QMessageBox::Information
            );
    }
    else
    {
        showMessage(
            "Error",
            "Account details not found.",
            QMessageBox::Warning
            );
    }
}


// =============================
// LOGOUT
// =============================
void AccountDashboard::on_logoutbtn_clicked()
{
    close();
}


// =============================
// WITHDRAW
// =============================

void AccountDashboard::on_Withdrawbtn_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle("Withdraw");
    dialog.setLabelText("Enter withdrawal amount:");
    dialog.setInputMode(QInputDialog::DoubleInput);
    dialog.setDoubleValue(0);
    dialog.setDoubleRange(0, 1000000);
    dialog.setDoubleDecimals(2);
    styleInputDialog(dialog);

    if (dialog.exec() != QDialog::Accepted)
        return;

    double amount = dialog.doubleValue();

    if (!qIsFinite(amount) || amount <= 0)
    {
        showMessage("Error", "Enter a valid positive amount.",
                    QMessageBox::Warning);
        return;
    }

    const QString filePath =
        QStringLiteral("D:/c ++/Bankinsystem project/output/Bank.txt");

    ifstream file(filePath.toLocal8Bit().constData());

    if (!file)
    {
        showMessage("Error", "Bank file could not be opened.",
                    QMessageBox::Warning);
        return;
    }

    vector<AccountRecord> records;
    string accno, name, pin, balance;
    int targetIndex = -1;

    while (getline(file, accno))
    {
        if (!getline(file, name) ||
            !getline(file, pin) ||
            !getline(file, balance))
        {
            showMessage("Data Error",
                        "Bank file contains an incomplete record.",
                        QMessageBox::Warning);
            return;
        }

        bool balanceOk = false;
        double currentBalance =
            QString::fromStdString(balance).trimmed()
                .toDouble(&balanceOk);

        if (!balanceOk || !qIsFinite(currentBalance) ||
            currentBalance < 0)
        {
            showMessage("Data Error",
                        "Bank file contains an invalid balance.",
                        QMessageBox::Warning);
            return;
        }

        records.push_back({accno, name, pin, balance});

        if (accno == accountnumber.toStdString())
        {
            if (targetIndex != -1)
            {
                showMessage("Data Error",
                            "Duplicate account records found.",
                            QMessageBox::Warning);
                return;
            }

            targetIndex = static_cast<int>(records.size()) - 1;
        }
    }

    if (file.bad())
    {
        showMessage("Read Error", "Could not read Bank.txt completely.",
                    QMessageBox::Critical);
        return;
    }

    file.close();

    if (targetIndex == -1)
    {
        showMessage("Error", "Account not found.",
                    QMessageBox::Warning);
        return;
    }

    AccountRecord &account = records[targetIndex];

    bool balanceOk = false;
    double currentBalance =
        QString::fromStdString(account.balance).toDouble(&balanceOk);

    if (!balanceOk || amount > currentBalance)
    {
        showMessage("Insufficient Balance",
                    "Insufficient balance.",
                    QMessageBox::Warning);
        return;
    }

    account.balance =
        QString::number(currentBalance - amount, 'f', 2).toStdString();

    if (!saveBankData(filePath, records))
    {
        showMessage("Save Error", "Withdrawal could not be saved.",
                    QMessageBox::Critical);
        return;
    }

    showMessage("Withdrawal Successful",
                "₹" + QString::number(amount, 'f', 2) +
                    " withdrawn successfully.",
                QMessageBox::Information);
}

// =============================
// CHANGE PIN
// =============================


void AccountDashboard::on_changepinbtn_clicked()
{
    // 1. Ask for current PIN
    QInputDialog oldPinDialog(this);
    oldPinDialog.setWindowTitle("Change PIN");
    oldPinDialog.setLabelText("Enter current PIN:");
    oldPinDialog.setInputMode(QInputDialog::TextInput);
    oldPinDialog.setTextEchoMode(QLineEdit::Password);
    styleInputDialog(oldPinDialog);

    if (oldPinDialog.exec() != QDialog::Accepted)
        return;

    QString oldPin = oldPinDialog.textValue().trimmed();

    if (!QRegularExpression("^[0-9]{6}$").match(oldPin).hasMatch())
    {
        showMessage("Error", "Current PIN must contain exactly 6 digits.",
                    QMessageBox::Warning);
        return;
    }

    // 2. Read account records from file
    const char *filePath =
        R"(D:\c ++\Bankinsystem project\output\Bank.txt)";

    ifstream file(filePath);

    if (!file)
    {
        showMessage("Error", "Bank file could not be opened.",
                    QMessageBox::Warning);
        return;
    }

    struct AccountRecord
    {
        string accno;
        string name;
        string pin;
        string balance;
    };

    vector<AccountRecord> records;
    string accno, name, pin, balance;
    int targetIndex = -1;
    bool invalidData = false;

    while (getline(file, accno))
    {
        if (!getline(file, name) ||
            !getline(file, pin) ||
            !getline(file, balance))
        {
            invalidData = true;
            break;
        }

        QString qAccno = QString::fromStdString(accno).trimmed();
        QString qName = QString::fromStdString(name).trimmed();
        QString qPin = QString::fromStdString(pin).trimmed();

        if (qAccno.isEmpty() || qName.isEmpty() ||
            !QRegularExpression("^[0-9]{6}$").match(qPin).hasMatch())
        {
            invalidData = true;
            break;
        }

        bool balanceOk = false;
        double balanceValue =
            QString::fromStdString(balance).trimmed()
                .toDouble(&balanceOk);

        if (!balanceOk || !qIsFinite(balanceValue) || balanceValue < 0)
        {
            invalidData = true;
            break;
        }

        records.push_back({accno, name, pin, balance});

        if (qAccno == accountnumber.trimmed())
        {
            if (targetIndex != -1)
            {
                file.close();
                showMessage("Security Error",
                            "Duplicate account records found. PIN change cancelled.",
                            QMessageBox::Warning);
                return;
            }

            targetIndex = static_cast<int>(records.size()) - 1;
        }
    }

    if (file.bad())
        invalidData = true;

    file.close();

    if (invalidData)
    {
        showMessage("Data Error",
                    "Bank.txt contains invalid or incomplete records. No changes made.",
                    QMessageBox::Warning);
        return;
    }

    if (targetIndex == -1)
    {
        showMessage("Error", "Account not found.",
                    QMessageBox::Warning);
        return;
    }

    // 3. Verify current PIN BEFORE asking for a new PIN
    AccountRecord &account = records[targetIndex];

    QString storedPin = QString::fromStdString(account.pin).trimmed();

    if (storedPin != oldPin)
    {
        showMessage("Error",
                    "Current PIN is incorrect. PIN has not been changed.",
                    QMessageBox::Warning);
        return;
    }

    // 4. Ask for new PIN only after current PIN is verified
    QInputDialog newPinDialog(this);
    newPinDialog.setWindowTitle("Change PIN");
    newPinDialog.setLabelText("Enter new 6-digit PIN:");
    newPinDialog.setInputMode(QInputDialog::TextInput);
    newPinDialog.setTextEchoMode(QLineEdit::Password);
    styleInputDialog(newPinDialog);

    if (newPinDialog.exec() != QDialog::Accepted)
        return;

    QString newPin = newPinDialog.textValue().trimmed();

    if (!QRegularExpression("^[0-9]{6}$").match(newPin).hasMatch())
    {
        showMessage("Error", "New PIN must contain exactly 6 digits.",
                    QMessageBox::Warning);
        return;
    }

    if (newPin == storedPin)
    {
        showMessage("Error",
                    "New PIN must be different from the current PIN.",
                    QMessageBox::Warning);
        return;
    }

    // 5. Update PIN in memory
    account.pin = newPin.toStdString();

    // 6. Save all records
    ofstream outFile(filePath, ios::trunc);

    if (!outFile)
    {
        showMessage("Error", "Could not open Bank.txt for updating.",
                    QMessageBox::Warning);
        return;
    }

    for (const AccountRecord &record : records)
    {
        outFile << record.accno << '\n'
                << record.name << '\n'
                << record.pin << '\n'
                << record.balance << '\n';
    }

    outFile.close();

    if (!outFile)
    {
        showMessage("Error",
                    "An error occurred while saving Bank.txt. Check the file.",
                    QMessageBox::Critical);
        return;
    }

    showMessage("Success", "PIN changed successfully.",
                QMessageBox::Information);
}
