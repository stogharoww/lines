#include "function.h"
#include <QPainter>
#include <QtMath>

Function::Function(const NumpyC& x, const NumpyC& y)
{
    _logicalRect = QRectF(0, 0, 100, 100);
    _pixelRect = QRectF(0, 0, 100, 100);
    _rawX = x;
    _rawY = y;
    rebuildPoints(x, y);

    rebuildPoints(x, y);
}

void Function::setViewport(const QRectF& logicalRect, const QRectF& pixelRect)
{
    _logicalRect = logicalRect;
    _pixelRect = pixelRect;

    double w = logicalRect.width();
    double h = logicalRect.height();

    if (w < 1e-6) w = 1.0;
    if (h < 1e-6) h = 1.0;

    _scaleX = qRound((pixelRect.width() / w) * 1000) / 1000.0;
    _scaleY = qRound((pixelRect.height() / h) * 1000) / 1000.0;

    _offsetX = pixelRect.left() - logicalRect.left() * _scaleX;
    _offsetY = pixelRect.bottom() + logicalRect.top() * _scaleY;

    rebuildPoints(_rawX, _rawY);
    update();
}


QRectF Function::boundingRect() const
{
    return QRectF(_pixelRect.left() - 50, _pixelRect.top() - 50,
                  _pixelRect.width() + 100, _pixelRect.height() + 100);
}






void Function::rebuildPoints(const NumpyC& x, const NumpyC& y)
{
    _points.clear();
    int count = qMin(x.size(), y.size());

    for (int i = 0; i < count; ++i) {
        double xv = x[i];
        double yv = y[i];

        if (!qIsFinite(xv) || !qIsFinite(yv)) continue;

        double px = _offsetX + xv * _scaleX;
        double py = _offsetY - yv * _scaleY;

        // Защита от выхода за границы
        if (px < -1000 || px > 10000) continue;
        if (py < -1000 || py > 10000) continue;

        _points.append(QPointF(px, py));
    }
}

void Function::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (_points.size() < 2) return;

    QPen pen(Qt::blue, 2);
    painter->setPen(pen);

    for (int i = 1; i < _points.size(); ++i) {
        if (_pixelRect.contains(_points[i]))
            painter->drawLine(_points[i - 1], _points[i]);
    }
}

