#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <MathUtils.h>
#include <QMessageBox>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Connect button signal to appropriate slot
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButtonClick);
    connect(ui->clearButton, &QPushButton::released, this, &MainWindow::handleClearButtonClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick(){
    // handle input
    double input = ui->doubleSpinBox->value();
    QString radioButtonText;
    // calculate
    double y = -1.0;
    if (ui->f1RadioButton->isChecked()){
        radioButtonText = ui->f1RadioButton->text();
        y = MathUtils::calulateF1(input);
        QString value = QString::number(y);
        ui->f1ResultLabel->setText(value);
    } else {
        radioButtonText = ui->f2RadioButton->text();
        y = MathUtils::calulateF2(input);
        QString value = QString::number(y);
        ui->f2ResultLabel->setText(value);
    }
    // show result
    char messageBuffer [128];
    std::sprintf (messageBuffer, "\nx= %.3f\ny = %.3f", input, y);
    QString message;
    message.append(radioButtonText);
    message.append(messageBuffer);
    QMessageBox::information(this, "Result", message);
}

void MainWindow::handleClearButtonClick(){

    ui->doubleSpinBox->clear();
    ui->f1ResultLabel->clear();
    ui->f2ResultLabel->clear();

}
