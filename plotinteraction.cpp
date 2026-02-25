#include "plotinteraction.h"



PlotInteraction::PlotInteraction(const QRectF &rect, QGraphicsItem *parent)
    : QObject(), QGraphicsRectItem(rect, parent)
{
    //setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    setBrush(Qt::NoBrush);
    setPen(Qt::NoPen);
    _rect = rect;
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
    if (!dragging){
        //_followMouse->updateP(event->pos());

        return;
    }
    //_followMouse->updateP(event->pos());

    QPointF delta = event->pos() - lastPos;
    lastPos = event->pos();
    emit requested(delta);
    movingPos = event->pos();
    //QPointF moved = movingPos - event->pos();

    //emit leaved(false);
    //emit moving(movingPos);

}

void PlotInteraction::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)
{
    if (event->button() == Qt::LeftButton){
        dragging = false;
    }
}

void PlotInteraction::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    movingPos = event->pos();
    //QPointF moved = movingPos - event->pos();

    //emit leaved(false);
    emit moving(movingPos);

    //_followMouse->updateP(event->pos());
}

void PlotInteraction::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit leaved(false);
}

void PlotInteraction::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit leaved(true);
}
/*
void PlotInteraction::mouseCircleEvent(QGraphicsSceneWheelEvent *event)
{
    int angle = event->delta();

    if (angle == 0){
        event->ignore();
        return;
    }

    const double STEP = 120;
    double steps = static_cast<double>(d) / STEP;

    const double SENSITIVY = 0.25;
    double zoomFactorPerStep = 1.15;
    double factor = std::pow(zoomFactorPerStep, steps * SENSITIVY);



}

*/
