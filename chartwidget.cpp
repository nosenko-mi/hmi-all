#include "chartwidget.h"
#include "mathutils.h"

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(100, 100);
    this->pen.setWidth(2);
    this->pen.setBrush(QBrush("red"));

    spaceBetweenBars = 5;
    chartOuterMargin = 10;
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
    drawPoints(&painter);
}

void ChartWidget::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}


void ChartWidget::setPoints(QVector<Point> points)
{
    this->points = points;
    processNewPoints();
    /* std::vector<QPointF> pointsVector;
    std::vector<QPointF> pointsToDrawVector;
    pointsVector = MathUtils::scale(points, 100, 0);
    try {
        // for (const auto&[x, y] : coordinates){
        //     pointsVector.push_back(QPointF(x, y));
        // }

        QPointF currentPoint;
        QPointF previousPoint;
        for(int i = 1; i <= pointsVector.size(); i++){
            previousPoint = pointsVector[i-1];
            if ((i == pointsVector.size()) &&
                (!std::isnan(previousPoint.y()) || !std::isinf(previousPoint.y()))){
                pointsToDrawVector.push_back(previousPoint);
                continue;
            }
            currentPoint = pointsVector[i];

            if (std::isnan(currentPoint.y()) || std::isinf(currentPoint.y())){
                pointsToDrawVector.push_back(previousPoint);
                i++;
                continue;
            } else if (std::isnan(previousPoint.y()) || std::isinf(previousPoint.y())) {
                pointsToDrawVector.push_back(currentPoint);
                i++;
                continue;
            }
            else {
                lines.append(QLineF(previousPoint, currentPoint));
            }
        }

    } catch (const std::exception& e) {
        QTextStream cerr(stderr);
        cerr << e.what();
    }

    this->points = pointsToDrawVector;
    this->lines = lines;

    update();
 */

}

void ChartWidget::processNewPoints(){
    QVector<Point> scaledPoints;
    QVector<QPointF> pointsToDrawVector;
    QVector<QLineF> lines;
    scaledPoints = MathUtils::scale(points, 100, 0);
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
    painter->drawText(QPointF(chartOuterMargin, height() - chartOuterMargin - xAxisHeight()), "0");

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

    foreach(QPointF point, pointsToDraw) {
        xAxisMark += this->pen.widthF()/2;

        painter->drawLine(QPointF(xAxisMark, xAxisY), QPointF(xAxisMark, xAxisY + 3));

        QFontMetrics fm(font());
        double markTextWidth = fm.horizontalAdvance(QString::number(point.x()));
        double markTextHeight = fm.height();

        painter->drawText(QPointF(xAxisMark - (markTextWidth/2), xAxisY + markTextHeight + 5), QString::number(point.x()));

        xAxisMark += (this->pen.widthF() / 2) + spaceBetweenBars;
    }

    painter->restore();
}

void ChartWidget::drawPoints(QPainter *painter)
{
    painter->save();
    painter->setPen(this->pen);
    painter->drawPoints(pointsToDraw);
    painter->drawLines(lines);
    painter->restore();

    // foreach(QPointF point, pointsToDraw) {
    //     painter->save();
    //     painter->setPen(this->pen);
    //     painter->drawPoint(point);
    //     painter->restore();
    // }
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

    foreach(QPointF point, pointsToDraw) {
        width += this->pen.widthF() + spaceBetweenBars;
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
