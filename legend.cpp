#include <QPainter>
#include "legend.h"
#include <QString>
//#include <plotapi.h>

Legend::Legend()
{
}


void Legend::addLegend(const QString &name, const QColor &color)
{
    QString redName = " - " + name;
    _names.append(redName);
    _colors.append(color);
    //prepareGeometryChange();
    update();
}


QRectF Legend::boundingRect() const
{
    return _rect;
}

void Legend::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    _rect = QRectF(0, 0, 200, _names.size() * 20 + 5);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRect(_rect);

    for (int i = 0; i < _names.size(); i++)
    {
        painter->setBrush(_colors[i]);
        painter->drawRect(5, 5 + i * 20, 10, 10);
        painter->setPen(Qt::black);
        painter->drawText(20, 15 + i * 20, _names[i]);
    }
}


/*
void Legend::changeText(QString string)
{

}

void Legend::repaint()
{

}*/
