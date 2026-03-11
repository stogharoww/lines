#pragma once
#include <QGraphicsRectItem>
#include <QString>
#include <QVector>
#include <QRectF>

class Legend: public QGraphicsRectItem
{
public:
    Legend();
    void addLegend(const QString &name, const QColor &color);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    //void changeText(QString string = "???");
    //void repaint();


private:
    QVector<QString> _names;
    QVector<QColor> _colors;
    QRectF _rect;



};
