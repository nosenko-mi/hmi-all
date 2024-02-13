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
    double input = ui->leftSpinBox->value();
    // calculate
    double y = -1.0;
    if (ui->f1RadioButton->isChecked()){
        y = MathUtils::calulateF1(input);
    } else {
        y = MathUtils::calulateF2(input);
    }
    // show result
    char messageBuffer [128];
    std::sprintf (messageBuffer, "The result is: %.3f", y);
    QString message = messageBuffer;
    QMessageBox::information(this, "Information", message); // Replace "this" with your parent widget
}

void MainWindow::handleClearButtonClick(){

    ui->leftSpinBox->clear();
}
