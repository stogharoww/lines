#include "bottom.h"


Bottom::Bottom(QString name, qreal w, qreal h, qreal ax, qreal ay)
{
    //int id = QFontDatabase::addApplicationFont(":/textures/mttrrxx/Silver.ttf");
    //Silver = QFontDatabase::applicationFontFamilies(id).at(0);

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    //draw the rect
    setRect(ax,ay,w,h);
    brush.setStyle(Qt::SolidPattern);
    setColor(_color);

    //draw the text
    text = new QGraphicsTextItem(name, this);
    //QFont buttonFont(Silver, 20);
    //text->setFont(buttonFont);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    //allow responding to hover events
    setAcceptHoverEvents(true);
}

void Bottom::setPuxmap(QString data)
{
    QPixmap original(data);

    QSizeF targetSize = rect().size();
    QPixmap scaled = original.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(scaled, this);
    qreal xOffset = rect().width()/2 - scaled.width()/2;
    qreal yOffset = rect().height()/2 - scaled.height()/2;

    pixmapItem->setPos(xOffset, yOffset);
}

void Bottom::setColor(QColor col)
{
    _color = col;
    brush.setColor(_color);
    setBrush(brush);
}

void Bottom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    brush.setColor(_color);
    setBrush(brush);
    emit clicked();

}

void Bottom::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    //change color to cyan
    brush.setColor(_color.lighter(150));
    setBrush(brush);
}

void Bottom::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    //change color to dark cyan
    brush.setColor(_color);
    setBrush(brush);
}
