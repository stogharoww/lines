#pragma once
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QObject>
#include <QRectF>
#include <QBrush>
#include <QPen>
#include <QPointF>
#include <QGraphicsSceneWheelEvent>
//#include "followingcoords.h"

class PlotInteraction : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit PlotInteraction(const QRectF& rect, QGraphicsItem *parent = nullptr);


signals:
    void requested(QPointF delta);
    void moving(QPointF pos);
    void leaved(bool leave);

    void wheel(QPointF localPos, int delta);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent  * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent  * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  * event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    //void mouseCircleEvent(QGraphicsSceneWheelEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);


private:
    bool dragging = false;
    QPointF lastPos;
    QPointF movingPos;
    QRectF _rect;

};


