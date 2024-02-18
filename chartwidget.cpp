#include "chartwidget.h"
#include "mathutils.h"

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(100, 100);
    this->pen.setWidth(2);
    this->pen.setBrush(QBrush("red"));

    this->rect().setWidth(100);
    this->rect().setHeight(100);

    spaceBetweenBars = 20;
    chartOuterMargin = 0;
    pointWidth = pen.widthF() * 4;
}

void ChartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setViewport(this->rect());
    painter.setWindow(this->rect());
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, false);

    // painter.drawPoints(points.data(), points.size());
    // painter.drawLines(lines);

    if (pointsToDraw.isEmpty())
        drawEmptyChart(&painter);
    else {
        drawXAxis(&painter);
        drawYAxis(&painter);
        drawPoints(&painter);
    }
    // drawPoints(&painter);
}

void ChartWidget::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}


void ChartWidget::setPoints(QVector<Point> points)
{
    this->points = points;
    pointWidth = pen.widthF() * 4;
    processNewPoints();

}

void ChartWidget::processNewPoints(){
    QVector<Point> scaledPoints;
    QVector<QPointF> pointsToDrawVector;
    QVector<QLineF> lines;
    // scaledPoints = MathUtils::scale(points, 100, 0);
    scaledPoints = points;
    try {
        Point currentPoint;
        Point previousPoint;
        for(int i = 1; i <= scaledPoints.size(); i++){
            previousPoint = scaledPoints[i-1];
            if ((i == points.size()) && previousPoint.isValid()){
                pointsToDrawVector.append(QPointF(previousPoint.getX(), previousPoint.getY()));
                continue;
            }
            currentPoint = scaledPoints[i];

            if (!currentPoint.isValid()){
                pointsToDrawVector.append(QPointF(previousPoint.getX(), previousPoint.getY()));
                i++;
                continue;
            } else if (!previousPoint.isValid()) {
                pointsToDrawVector.append(QPointF(currentPoint.getX(), currentPoint.getY()));
                i++;
                continue;
            }
            else {
                lines.append(QLineF(
                    QPointF(previousPoint.getX(), previousPoint.getY()),
                    QPointF(currentPoint.getX(), currentPoint.getY()))
                             );
            }
        }

    } catch (const std::exception& e) {
        QTextStream cerr(stderr);
        cerr << e.what();
    }

    this->pointsToDraw = pointsToDrawVector;
    this->lines = lines;

    update();
}


void ChartWidget::drawYAxis(QPainter *painter)
{
    QPen yAxisPen(QColor(qRgb(0, 0, 0)));

    QString maximumValue = QString::number(maximumHeight());
    QString minimumValue = QString::number(MathUtils::getMinY(points));
    QFontMetrics fm(font());
    double textWidth = fm.horizontalAdvance(maximumValue);
    double textHeight = fm.height();

    double yAxisX = chartOuterMargin + textWidth + 5;
    double yAxisY = chartOuterMargin + (textHeight / 2);
    double yAxisHeight = height() - yAxisY - xAxisHeight();

    painter->save();

    painter->setPen(yAxisPen);
    painter->drawLine(QPointF(yAxisX, yAxisY), QPointF(yAxisX, yAxisHeight));

    painter->drawLine(QPointF(yAxisX - 3, yAxisY), QPointF(yAxisX, yAxisY));
    painter->drawLine(QPointF(yAxisX - 3, yAxisHeight), QPointF(yAxisX, yAxisHeight));

    painter->drawText(QPointF(chartOuterMargin, chartOuterMargin + textHeight), maximumValue);
    painter->drawText(QPointF(chartOuterMargin, height() - chartOuterMargin - xAxisHeight()), minimumValue);

    painter->restore();
}

void ChartWidget::drawXAxis(QPainter *painter)
{
    QPen xAxisPen(QColor(qRgb(0, 0, 0)));

    QFontMetrics fm(font());
    double textHeight = fm.height();

    double xAxisX = chartOuterMargin + yAxisWidth();
    double xAxisY = height() - xAxisHeight() - chartOuterMargin - (textHeight/2);
    double xAxisWidth = xAxisX + maximumWidth() + spaceBetweenBars;
    painter->save();

    painter->setPen(xAxisPen);
    painter->drawLine(QPointF(xAxisX, xAxisY), QPointF(xAxisWidth, xAxisY));

    double xAxisMark = xAxisX + spaceBetweenBars;

    foreach(Point point, points) {
        xAxisMark += pointWidth /2;

        painter->drawLine(QPointF(xAxisMark, xAxisY), QPointF(xAxisMark, xAxisY + 3));

        QFontMetrics fm(font());
        double markTextWidth = fm.horizontalAdvance(QString::number(point.getX(), 'g', 2));
        double markTextHeight = fm.height();

        painter->drawText(QPointF(xAxisMark - (markTextWidth/2), xAxisY + markTextHeight + 5), QString::number(point.getX(), 'g', 2));

        xAxisMark += (pointWidth / 2) + spaceBetweenBars;
    }

    painter->restore();
}

void ChartWidget::drawPoints(QPainter *painter)
{
    // painter->save();
    // painter->setPen(this->pen);
    // painter->drawPoints(pointsToDraw);
    // painter->drawLines(lines);
    // painter->restore();

    double projectedX = chartOuterMargin + yAxisWidth() + spaceBetweenBars;

    QFontMetrics fm(font());
    qreal textHeight = fm.height();
    double h = height();
    double xHeight = xAxisHeight();
    double scaleH = height() -xHeight - chartOuterMargin - (textHeight/2);
    QVector<Point> points = MathUtils::scale(this->points, width(), scaleH);
    for (int i = 0, k = 1; i < points.size(); i++, k++){

        if (!points[i].isValid()){
            projectedX += pointWidth + spaceBetweenBars;
            continue;
        }

        projectedX += pointWidth / 2;
        painter->save();
        // double projectedY = h - xHeight - chartOuterMargin - (textHeight/2) - points[i].getY();
        double projectedY = h - xHeight - - chartOuterMargin - points[i].getY();
        // double projectedY = h - points[i].getY();
        if (projectedY < 0) projectedY=0;
        // height() - xAxisHeight() - chartOuterMargin - (textHeight/2);
        // double dpHeight = dataPointHeight(points[i].getY());
        // painter->drawPoint(QPointF(point.getX(), point.getX()));
        painter->drawPoint(QPointF(projectedX, projectedY));

        painter->restore();

        projectedX += (pointWidth / 2) + spaceBetweenBars;
    }

    // foreach(Point point, points) {
    //     projectedX += pointWidth / 2;

    //     painter->save();

    //     double dpHeight = dataPointHeight(point.getY());

    //     if (point.isValid()){
    //         painter->drawPoint(QPointF(projectedX - (pointWidth/2), height() - xAxisHeight() - chartOuterMargin - (textHeight/2)));

    //     }
    //     // QRectF()
    //     // painter->drawRect(QRectF(projectedX - (pointWidth/2), height() - xAxisHeight() - chartOuterMargin - (textHeight/2),
    //     //                          pointWidth, -dpHeight));

    //     painter->restore();

    //     projectedX += (pointWidth / 2) + spaceBetweenBars;
    // }

    // foreach(QPointF point, pointsToDraw) {
    //     painter->save();
    //     painter->setPen(this->pen);
    //     painter->drawPoint(point);
    //     painter->restore();
    // }
}

double ChartWidget::dataPointHeight(double y)
{
    QFontMetrics fm(font());
    qreal textHeight = fm.height();

    return y * ((height() - (2 * (chartOuterMargin + (textHeight / 2))) - xAxisHeight()) / maximumHeight());
}


void ChartWidget::drawEmptyChart(QPainter *painter)
{
    QString text("No datapoints available!");

    double centreX = width() / 2;
    double centreY = height() / 2;

    QFontMetricsF fontMetrics(font());
    double textWidth = fontMetrics.horizontalAdvance(text);
    double textHeight = fontMetrics.height();

    double textX = centreX - (textWidth / 2);
    double textY = centreY - (textHeight / 2);

    painter->drawText(QPointF(textX, textY), text);
}

double ChartWidget::maximumHeight()
{
    double height = 0;

    foreach(QPointF point, pointsToDraw) {
        if (point.y() > height)
            height = point.y();
    }

    return height;
}

double ChartWidget::maximumWidth()
{
    double width = 0;

    foreach(Point point, points) {
        width += pointWidth + spaceBetweenBars;
    }

    return width;
}

double ChartWidget::yAxisWidth()
{
    QString maximumValue = QString::number(maximumHeight());
    QFontMetrics fm(font());
    double textWidth = fm.horizontalAdvance(maximumValue);

    return textWidth + 5;
}

double ChartWidget::xAxisHeight()
{
    QFontMetrics fm(font());
    double textHeight = fm.height();

    return textHeight + 5;
}
