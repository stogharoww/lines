#pragma once
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QObject>
#include <QRectF>
#include <QBrush>
#include <QPen>
#include <QPointF>

class PlotInteraction : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit PlotInteraction(const QRectF& rect, QGraphicsItem *parent = nullptr);


signals:
    void requested(QPointF delta);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent  * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent  * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  * event);

private:
    bool dragging = false;
    QPointF lastPos;
};


