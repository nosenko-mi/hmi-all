#include "chartwidget.h"
#include "fileutils.h"
#include "mainwindow.h"
#include "renderarea.h"
#include "ui_mainwindow.h"

#include <MathUtils.h>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QPrinter>
#include <QTableWidget>
#include <QTextTableCell>

const int IdRole = Qt::UserRole;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    // ui->plotWidget->layout()->addWidget(renderArea);

    // ChartWidget* chartWidget = new ChartWidget();
    // ui->plotWidget->layout()->addWidget(chartWidget);


}

void MainWindow::init(){

    renderArea = new RenderArea();
    chartWidget = new ChartWidget();
    // ui->plotWidget->setLayout(new QVBoxLayout);
    // ui->plotWidget->layout()->addWidget(chartWidget);

    chartWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    QScrollArea* chartContainer = new QScrollArea();
    chartContainer->setLayout(new QVBoxLayout());
    chartContainer->setWidget(chartWidget);
    chartContainer->setWidgetResizable(true);
    chartContainer->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // QMdiSubWindow *chartSubWindow = new QMdiSubWindow(chartContainer);
    QMdiSubWindow *chartSubWindow = ui->mdiArea->addSubWindow(chartContainer);
    chartSubWindow->setWindowTitle("Chart Window");
    // chartSubWindow->setParent(ui->mdiArea);
    // ui->mdiArea->addSubWindow(chartSubWindow);
    // ui->mdiArea->setWindowTitle("Chart Window");
    // ui->mdiArea->show();

    // resultTable = new QTableWidget();
    // QMdiSubWindow *tableSubWindow = ui->mdiArea->addSubWindow(resultTable);
    // tableSubWindow->setWindowTitle("Table Window");
    // ui->mdiArea->show();

    tableWindow = new TableWindow();
    // tableWindow->setWindowTitle("Table Window");
    QMdiSubWindow *tableSubWindow = ui->mdiArea->addSubWindow(tableWindow);
    tableSubWindow->setWindowTitle("Table Window");
    ui->mdiArea->show();

    // QScrollArea* chartContainer = new QScrollArea();
    // chartContainer->setLayout(new QVBoxLayout());
    // chartContainer->layout()->addWidget(chartWidget);
    // ui->mdiArea->addSubWindow(chartContainer);
    // ui->mdiArea->setWindowTitle("Chart Window");
    // ui->mdiArea->show();

    // ui->scrollArea->setWidget(chartWidget);
    // ui->scrollArea->setWidgetResizable(true);
    // ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->penStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    ui->penStyleComboBox->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    ui->penStyleComboBox->addItem(tr("Dot"),  static_cast<int>(Qt::DotLine));

    ui->penColorComboBox->addItem(tr("Red"), QColor("red"));
    ui->penColorComboBox->addItem(tr("Green"), QColor("green"));
    ui->penColorComboBox->addItem(tr("Blue"), QColor("blue"));

    // Connect button signal to appropriate slot
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButtonClick);
    connect(ui->clearButton, &QPushButton::released, this, &MainWindow::handleClearButtonClick);
    // connect(ui->penStyleComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::handleStyleChange);
    // connect(ui->penColorComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::handleColorChange);
    // connect(ui->penWidthSpinBox, &QSpinBox::valueChanged, this, &MainWindow::handleWidthChange);
    connect(ui->penWidthSpinBox, &QSpinBox::valueChanged, this, &MainWindow::penChanged);
    connect(ui->penStyleComboBox, &QComboBox::activated, this, &MainWindow::penChanged);
    connect(ui->penColorComboBox, &QComboBox::activated, this, &MainWindow::penChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick(){
    // clear previous result
    qDebug() << "chartWidget: " << chartWidget->width() << chartWidget->height() << chartWidget->sizeHint().width() << "\n";
    // qDebug() << "scrollArea: " << ui->scrollArea->width() << ui->scrollArea->height() << "\n";
    // handle input
    if (!isInputCorrect()){
        return;
    }
    double left = ui->leftSpinBox->value();
    double right = ui->rightSpinBox->value();
    int n = ui->valuesAmountSpinBox->value();

    // calculate
    QVector<Point> result;
    if (ui->f1RadioButton->isChecked()){
        result = MathUtils::calculateRangeToPoints(left, right, n, &MathUtils::calculateF1);
    } else {
        // result = MathUtils::calculateRange(left, right, n, &MathUtils::calculateF2);
        result = MathUtils::calculateRangeToPoints(left, right, n, &MathUtils::calculateF2);
    }

    // renderArea->setCoordinates(result);
    chartWidget->setPoints(result);

    tableWindow->setData(result);
    points = result;

    // resultTable->clear();
    // resultTable->setRowCount(2);
    // resultTable->setColumnCount(result.size());
    // int i = 0;

    // foreach(Point p, result){
    //     resultTable->setItem(0, i, new QTableWidgetItem(QString::number(p.getX())));
    //     resultTable->setItem(1, i, new QTableWidgetItem(QString::number(p.getY())));
    //     i++;
    // }
}

void MainWindow::penChanged()
{
    int width = ui->penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(ui->penStyleComboBox->itemData(ui->penStyleComboBox->currentIndex(), IdRole).toInt());
    // QColor color = QColor(ui->penColorComboBox->itemData(ui->penColorComboBox->currentIndex(), IdRole).toInt());
    QColor color = ui->penColorComboBox->itemData(ui->penColorComboBox->currentIndex()).value<QColor>();
    renderArea->setPen(QPen(color, width, style));
    chartWidget->setPen(QPen(color, width, style));
}

void MainWindow::handleStyleChange(int index){
    if (index != -1) { // Check if an item is selected
        int penStyleValue = ui->penStyleComboBox->itemData(index, Qt::UserRole + 1).toInt();
        Qt::PenStyle style = static_cast<Qt::PenStyle>(penStyleValue);
        renderArea->setPenStyle(style);
    } else {
    }

};

void MainWindow::handleColorChange(int index){
    int selectedIndex = ui->penColorComboBox->currentIndex();
    if (selectedIndex != -1) {
        QColor color = ui->penColorComboBox->itemData(index).value<QColor>();
        renderArea->setPenColor(color);
    } else {
    }

};
void MainWindow::handleWidthChange(int value){
    renderArea->setPenSize(value);
};

void MainWindow::open(){

}

void MainWindow::save(){

}

void MainWindow::print(){

}


void MainWindow::handleClearButtonClick(){

    ui->leftSpinBox->clear();
    ui->rightSpinBox->clear();

    // ui->resultTable->clear();
    // ui->resultTable->setColumnCount(0);
    // ui->resultTable->setRowCount(0);
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

void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "open";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Text Files (*.txt)"));
    points = FileUtils::openPointsFromFile(fileName);

    // parse document

    // display table
    tableWindow->setData(points);
    // draw chart
    chartWidget->setPoints(points);

}


void MainWindow::on_actionSave_triggered()
{
    qDebug() << "save";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("Text Files (*.txt)"));
    int result = FileUtils::savePointsToFile(fileName, points);
    if (result == -1){
        // show error
    }
}


void MainWindow::on_actionPrint_triggered()
{
    qDebug() << "print";

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFileName("print.pdf");

    QTextDocument* doc = tableWindow->toQTextDocument();

    //Print to PDF
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("testqtextdoc.pdf");
    doc->print(&printer);


    // printer.setOutputFormat(QPrinter::PdfFormat);
    // printer.setPaperSize(QPrinter::A4);

    // QPrintDialog printDialog(&printer, this);
    // if (printDialog.exec() == QDialog::Accepted) {
    //     // print ...
    //     qDebug() << "accepted";
    // }

    // QPainter painter;
    // painter.begin(&printer);
    // const auto pageLayout = printer.pageLayout();
    // const auto pageRect = pageLayout.paintRectPixels(printer.resolution());
    // const auto paperRect = pageLayout.fullRectPixels(printer.resolution());
    // double xscale = pageRect.width() / double(chartWidget->width());
    // double yscale = pageRect.height() / double(chartWidget->height());
    // double scale = qMin(xscale, yscale);
    // painter.translate(pageRect.x() + paperRect.width() / 2.,
    //                   pageRect.y() + paperRect.height() / 2.);
    // painter.scale(scale, scale);
    // painter.translate(-chartWidget->width() / 2., -chartWidget->height() / 2.);

    // chartWidget->render(&painter);


}

