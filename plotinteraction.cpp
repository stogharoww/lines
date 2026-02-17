#include "plotinteraction.h"


PlotInteraction::PlotInteraction(const QRectF &rect, QGraphicsItem *parent)
    : QObject(), QGraphicsRectItem(rect, parent)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    setBrush(Qt::NoBrush);
    setPen(Qt::NoPen);
}

void PlotInteraction::mousePressEvent(QGraphicsSceneMouseEvent  *event)
{
    if (event->button() == Qt::LeftButton){
        dragging = true;
        lastPos = event->pos();
    }
}

void PlotInteraction::mouseMoveEvent(QGraphicsSceneMouseEvent  *event)
{
    if (!dragging)
        return;

    QPointF delta = event->pos() - lastPos;
    lastPos = event->pos();
    emit requested(delta);

}

void PlotInteraction::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)
{
    if (event->button() == Qt::LeftButton){
        dragging = false;
    }
}

