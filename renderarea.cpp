#include "renderarea.h"




RenderArea::RenderArea()
{
    this->resize(256, 256);

    this->pen.setWidth(2);
    this->pen.setBrush(QBrush("red"));
}

void RenderArea::setCoordinates(std::map<double,double> coordinates){

    std::vector<QLineSeries*> serieses;
    QLineSeries* series = new QLineSeries;
    try {
        for (const auto&[x, y] : coordinates){
            if (std::isnan(x)|| std::isnan(y) || std::isinf(x) || std::isinf(y)){
                if (series->points().size() < 1) continue;
                serieses.push_back(series);
                // qDebug() << series->points().length();
                series = new QLineSeries;
                continue;
            }
            series->append(x, y);
        }
        serieses.push_back(series);
    } catch (const std::exception& e) {
        QTextStream cerr(stderr);
        cerr << e.what();
    }

    this->chart = new QChart();
    QScatterSeries* scatter = new QScatterSeries();
    for (QLineSeries* s : serieses){
        if (s->points().length() == 1){
            scatter->append(s->at(0));
            continue;
        } else if (s->points().length() > 1){
            this->chart->addSeries(s);
        }

    }
    scatter->setMarkerSize(this->pen.widthF()*4);
    scatter->setColor(this->pen.color());
    this->chart->addSeries(scatter);

    series->setPen(this->pen);
    scatter->setPen(this->pen);

    this->chart->legend()->hide();
    this->chart->createDefaultAxes();
    this->setRenderHint(QPainter::Antialiasing);
    this->setChart(chart);
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

void RenderArea::setPenStyle(const Qt::PenStyle style)
{
    this->pen.setStyle(style);
    update();
}

void RenderArea::setPenColor(const QColor color)
{
    this->pen.setColor(color);
    update();
}

void RenderArea::setPenSize(int width)
{
    this->pen.setWidth(width);
}
