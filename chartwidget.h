#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include "point.h"

#include <iostream>
#include <QPen>
#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QPaintEvent>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <Qline>

class ChartWidget : public QWidget
{
public:
    ChartWidget(QWidget *parent = 0);
    void setPoints(QVector<Point> points);

public slots:
    void setPen(const QPen &pen);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QVector<Point> points;
    QVector<QPointF> pointsToDraw;
    QVector<QLineF> lines;

    double maximumHeight();
    double maximumWidth();

    double yAxisWidth();
    double xAxisHeight();

    double spaceBetweenBars;
    double chartOuterMargin;

    double pointWidth;

    void drawEmptyChart(QPainter *painter);
    void drawYAxis(QPainter *painter);
    void drawXAxis(QPainter *painter);
    void drawPoints(QPainter *painter);
    void processNewPoints();
    double dataPointHeight(double y);
};

#endif // CHARTWIDGET_H
