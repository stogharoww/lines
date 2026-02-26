#include "axisitem.h"
#include <QPen>
#include <QPainter>
#include <QFontMetrics>
#include <numpyc.h>
#include <QGraphicsTextItem>
#include <QDebug>

AxisItem::AxisItem(qreal _x, qreal _y)
{
    //QGraphicsLineItem *lineX = new QGraphicsLineItem();
    _width = _x;
    _height = _y;
}

QString AxisItem::formatTickValue(double value, double range)
{
    _range = range;

    if (qAbs(value) < 1e-10) return "0";

    // Если диапазон большой — округляем до целого
    if (range > 10)
        return QString::number(qRound(value));

    // Если диапазон средний — 1 знак после запятой
    if (range > 1)
        return QString::number(value, 'f', 1);

    // Если диапазон маленький — 3 знака
    return QString::number(value, 'f', 3);
}



void AxisItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPen axisPen(QColor(211, 211, 211), 2);
    painter->setPen(axisPen);
    QPen gridPen(Qt::gray, 1);

    // Центр осей
    qreal centerX = _xMin;
    qreal centerY = _yMin;

    // Масштабы логика → пиксели
    double scaleX = _width / (_xMax - _xMin);
    double scaleY = _height / (_yMax - _yMin);

    // Плавное смещение сетки (Δлогики → пиксели)
    double pixelShiftX = (_xMin - _xMinTmp) * scaleX;
    double pixelShiftY = (_yMin - _yMinTmp) * scaleY;

    // Ось X с стрелкой
    painter->drawLine(0, _height, _width + 15, _height);
    painter->drawLine(_width + 15, _height, _width + 7, _height - 5);
    painter->drawLine(_width + 15, _height, _width + 7, _height + 5);

    // Ось Y с стрелкой
    painter->drawLine(0, _height, 0, -15);
    painter->drawLine(0, -15, -5, -7);
    painter->drawLine(0, -15, +5, -7);


    // Деления по X
    tickCountX = (_width) / 60;
    qreal tickSpacingX = _width / tickCountX;
    vecX = NumpyC::linspace(_xMin, _xMax, tickCountX+1);

    for (int i = 0; i <= tickCountX; i++) {
        painter->setPen(axisPen);

        qreal x = i * tickSpacingX + pixelShiftX;
        if (x < 0 || x > _width)
            continue;
        painter->drawLine(x, _height - 5, x, _height + 5);

        qreal value = vecX[i];
        QString strVal = formatTickValue(value, _xMax - _xMin);
        painter->drawText(x, _height + 20, strVal);

        //green lines:
        painter->setPen(gridPen);
        painter->drawLine(x, _height, x, 0);
    }

    // Деления по Y
    tickCountY = (_height) / 50;
    qreal tickSpacingY = _height / tickCountY;
    vecY = NumpyC::linspace(_yMin, _yMax, tickCountY+1);

    for (int i = 0; i <= tickCountY; ++i) {
        painter->setPen(axisPen);

        int j = tickCountY - i; //обратный порядок
        qreal y = j * tickSpacingY - pixelShiftY;
        if (y < 0 || y > _height)
            continue;
        painter->drawLine(0 - 5, y, 0 + 5, y);

        qreal value = vecY[i];
        QString strVal = formatTickValue(value, _yMax - _yMin);
        painter->drawText(0  - 35, y, strVal);

        //green lines:
        painter->setPen(gridPen);
        painter->drawLine(0, y, _width, y);
    }


    QFont labelFont = painter->font();
    labelFont.setBold(true);
    painter->setFont(labelFont);
    painter->setPen(axisPen);

    // Подпись X
    painter->drawText(_width + 25, _height + 5, _nameX);

    // Подпись Y
    painter->drawText(-10, -20, _nameY);

    // Значения отцентровки подбирались вручную
    QFont font = painter->font();
    font.setPointSize(16);
    painter->setFont(font);
    QRectF rect = boundingRect();
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignTop, _nameGraph);
}



void AxisItem::moveAxies(double dx, double dy)
{
    // Плавное движение (логика)
    _xMinTmp += dx;
    _xMaxTmp += dx;
    _yMinTmp += dy;
    _yMaxTmp += dy;

    // Логический шаг между делениями
    double logicalStepX = (_xMax - _xMin) / tickCountX;
    double logicalStepY = (_yMax - _yMin) / tickCountY;

    double deltaY = _yMinTmp - _yMin;
    double deltaX = _xMinTmp - _xMin;


    if (abs(deltaX) >= logicalStepX) {
        int steps = deltaX / logicalStepX;
        _xMin += steps * logicalStepX;
        _xMax += steps * logicalStepX;
    }


    if (abs(deltaY) >= logicalStepY) {
        int steps = deltaY / logicalStepY;
        _yMin += steps * logicalStepY;
        _yMax += steps * logicalStepY;
    }

    update();
}

NumpyC AxisItem::getX()
{
    return vecX;
}

NumpyC AxisItem::getY()
{
    return vecY;
}
