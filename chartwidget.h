#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <iostream>
#include <QPen>
#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QPaintEvent>
#include <QLineSeries>
#include <QChart>
#include <QChartView>


class ChartWidget : public QChartView
{
public:
    ChartWidget();
    void setCoordinates(std::map<double, double> coordinates);
};

#endif // CHARTWIDGET_H
