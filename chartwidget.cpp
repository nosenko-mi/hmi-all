#include "chartwidget.h"

ChartWidget::ChartWidget() {
    this->resize(256, 256);

    QLineSeries* series = new QLineSeries;
    series->append(0, 25);
    series->append(41, 21);

    QPen pen = series->pen();
    pen.setWidth(4);
    // pen.setStyle('dot');
    pen.setBrush(QBrush("red")); // or just pen.setColor("red");
    series->setPen(pen);

    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QChartView* chartView = new QChartView(chart);

    chartView->setRenderHint(QPainter::Antialiasing);
    show();

}


void ChartWidget::setCoordinates(std::map<double, double> coordinates){

    // std::vector<QLineSeries*> serieses;
    // QLineSeries* series = new QLineSeries;
    // serieses.push_back(series);
    // for (const auto&[x, y] : coordinates){
    //     if (std::isnan(x)|| std::isnan(y)){
    //         serieses.push_back(series);
    //         series = new QLineSeries;
    //     }
    //     series->append(x, y);
    // }

    // for (auto s : serieses){
    //     chart->addSeries(s);
    // }

    // chart->legend()->hide();
    // chart->createDefaultAxes();
    // this->setRenderHint(QPainter::Antialiasing);




}
