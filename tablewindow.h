#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include "point.h"

#include <QLabel>
#include <QTableWidget>
#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <qprinter.h>
#include <qtextformat.h>
#include <qtexttable.h>


class TableWindow :public QWidget
{
public:
    explicit TableWindow(QWidget *parent = nullptr);
    void setData(QVector<Point> points);
    QTextDocument* toQTextDocument();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTableWidget* tableWidget;

};

#endif // TABLEWINDOW_H
