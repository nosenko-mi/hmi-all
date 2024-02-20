#include "tablewindow.h"

#include <QPainter>
#include <QVBoxLayout>

TableWindow::TableWindow(QWidget *parent) : QWidget(parent)
{
    tableWidget = new QTableWidget(this); // Replace with your actual content widget

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    setLayout(layout);
}

void TableWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
}

void TableWindow::setData(QVector<Point> points){

    tableWidget->clear();
    tableWidget->setRowCount(2);
    tableWidget->setColumnCount(points.size());
    int i = 0;
    foreach(Point p, points){
        tableWidget->setItem(0, i, new QTableWidgetItem(QString::number(p.getX())));
        tableWidget->setItem(1, i, new QTableWidgetItem(QString::number(p.getY())));
        i++;
    }

    update();

}
