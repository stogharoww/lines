#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QBrush>
#include <QGraphicsTextItem>
#include <QFontDatabase>
#include <QGraphicsPixmapItem>


class Bottom: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    /**
     * @brief Bottom конструктор кнопки
     * @param name текст на кнопке
     * @param w ширина
     * @param h длина
     */
    Bottom(QString name="", qreal w=200, qreal h=400, qreal ax=0, qreal ay=0);
    /**
     * @brief setPuxmap рисует картинку внутри кнопки
     * @param data путь до картинки
     */
    void setPuxmap(QString data);

signals:
    void clicked();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    QGraphicsTextItem *text;

};

