#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include "point.h"

#include <QLabel>
#include <QTableWidget>
#include <QWidget>


class TableWindow :public QWidget
{
public:
    explicit TableWindow(QWidget *parent = nullptr);
    void setData(QVector<Point> points);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTableWidget* tableWidget;

};

#endif // TABLEWINDOW_H
