#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QPoint>
#include <QGraphicsRectItem>
#include <QBrush>


class FollowingCoords
{
public:
    FollowingCoords();
    void paint(QPainter *painter);
    void updateP(QPointF pos);

    void moving(bool move);


private:
    QPointF _pos;
    QPointF _startPos;
    int _x = 0;
    int _y = 0;
    bool _moving = 0;
};

