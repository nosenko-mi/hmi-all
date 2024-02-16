#ifndef RENDERAREA_H
#define RENDERAREA_H
#include <iostream>
#include <QPen>
#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QPaintEvent>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QScatterSeries>
#include<QDebug>

class RenderArea : public QChartView
{
    Q_OBJECT

public:
    // explicit RenderArea(QWidget *parent = nullptr);
    RenderArea();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setCoordinates(std::map<double, double> coordinates);


public slots:
    void setPen(const QPen &pen);
    void setPenColor(const QColor color);
    void setPenStyle(const Qt::PenStyle style);
    void setPenSize(int width);

private:
    QChart* chart;
    QLineSeries* series ;
    QPen pen;
};

#endif // RENDERAREA_H
