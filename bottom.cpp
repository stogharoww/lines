#include "bottom.h"


Bottom::Bottom(QString name, qreal w, qreal h, qreal ax, qreal ay)
{
    //int id = QFontDatabase::addApplicationFont(":/textures/mttrrxx/Silver.ttf");
    //Silver = QFontDatabase::applicationFontFamilies(id).at(0);

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    //draw the rect
    setRect(ax,ay,w,h);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

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
    QPixmap scaled = original.scaled(targetSize.toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(original, this);
    qreal xOffset = rect().width()/2 - original.width()/2;
    qreal yOffset = rect().height()/2 - original.height()/2;

    pixmapItem->setPos(xOffset, yOffset);
}

void Bottom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    emit clicked();

}

void Bottom::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    //change color to cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void Bottom::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    //change color to dark cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
