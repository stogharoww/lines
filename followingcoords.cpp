#include "followingcoords.h"
#include <QDebug>



FollowingCoords::FollowingCoords()
{

}

void FollowingCoords::paint(QPainter *painter)
{




}

void FollowingCoords::updateP(QPointF pos)
{
    qDebug() << pos;
    //_pos = pos;
}

void FollowingCoords::moving(bool move)
{
    _moving = move;
}
