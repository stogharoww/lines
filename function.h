#pragma once
#include <QGraphicsItem>
#include <QVector>
#include <QRectF>
#include "numpyc.h"

// Отображает график функции по точкам
class Function : public QGraphicsItem
{
public:
    Function(const NumpyC& x, const NumpyC& y);

    void setViewport(const QRectF& logicalRect, const QRectF& pixelRect);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;


private:
    QVector<QPointF> _points;       // Пиксельные координаты
    QRectF _logicalRect;            // Логические координаты
    QRectF _pixelRect;              // Пиксельная область
    double _scaleX = 1.0;
    double _scaleY = 1.0;
    double _offsetX = 0.0;
    double _offsetY = 0.0;
    NumpyC _rawX;
    NumpyC _rawY;
    QRectF _movedRect;


    void rebuildPoints(const NumpyC& x, const NumpyC& y);
};
