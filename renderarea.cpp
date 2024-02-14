#include "renderarea.h"


RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    this->resize(256, 256);
}

void RenderArea::setCoordinates(std::map<double,double> coordinates){
    this->coordinates = coordinates;
    this->update();
}

void RenderArea::paintEvent(QPaintEvent *)
{
    std::cout<<"draw";
    QPainter painter = QPainter(this);
    std::vector<QPoint> points;
    for (const auto&[x, y] : coordinates){
        points.push_back(QPoint(x, y));
    }

    painter.setPen(palette().dark().color());
    for (int i = 1; i < points.size(); i++){
        painter.drawLine(points[i-1], points[i]);
    }
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

void RenderArea::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}
