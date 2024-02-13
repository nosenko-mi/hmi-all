#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <MathUtils.h>
#include <QMessageBox>


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
    // clear previous result
    ui->resultTable->clear();

    // handle input
    if (!isInputCorrect()){
        return;
    }
    double left = ui->leftSpinBox->value();
    double right = ui->rightSpinBox->value();
    int n = ui->valuesAmountSpinBox->value();

    // calculate
    std::map<double, double> result;
    if (ui->f1RadioButton->isChecked()){
        result = MathUtils::calculateRange(left, right, n, &MathUtils::calculateF1);
    } else {
        result = MathUtils::calculateRange(left, right, n, &MathUtils::calculateF2);
    }

    // show result
    ui->resultTable->setRowCount(2);
    ui->resultTable->setColumnCount(result.size());

    int i = 0;
    for (const auto& [point, value] : result){
        ui->resultTable->setItem(0, i, new QTableWidgetItem(QString::number(point)));
        ui->resultTable->setItem(1, i, new QTableWidgetItem(QString::number(value)));
        i++;
    }

}

void MainWindow::handleClearButtonClick(){

    ui->leftSpinBox->clear();
    ui->rightSpinBox->clear();

    ui->resultTable->clear();
    ui->resultTable->setColumnCount(0);
    ui->resultTable->setRowCount(0);
}


void MainWindow::showMessageBox(QString message){

    // char messageBuffer [128];
    // std::sprintf (messageBuffer, "The result is: %.3f", result[0]);
    // QString message = messageBuffer;
    // QMessageBox::information(this, "Information", message); // Replace "this" with your parent widget

    QMessageBox::information(this, "Information", message); // Replace "this" with your parent widget
}

bool MainWindow::isInputCorrect(){
    if (ui->leftSpinBox->value() >= ui->rightSpinBox->value()){
        showMessageBox("Incorrect borders: left >= right");
        return false;
    }
    if (ui->valuesAmountSpinBox->value() < 2){
        showMessageBox("Incorrect amount: n < 2");
        return false;
    }
    return true;
}
