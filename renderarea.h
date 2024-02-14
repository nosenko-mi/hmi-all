#ifndef RENDERAREA_H
#define RENDERAREA_H
#include <iostream>
#include <QPen>
#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QPaintEvent>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);
    RenderArea();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void setCoordinates(std::map<double, double> coordinates);


public slots:
    void setPen(const QPen &pen);
    // void setPenColor(const QPen &pen);
    // void setPenStyle(const QPen &pen);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QPixmap pixmap;
    std::map<double, double> coordinates;
};

#endif // RENDERAREA_H
