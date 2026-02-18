#pragma once
#include <QGraphicsItem>


// Хранит данные об оси
class AxisItem : public QGraphicsItem
{
public:
    // Конструктор
    AxisItem(qreal x=10, qreal y=10);

    void setScaleXY(qreal xKoef, qreal yKoef){
        _xKoef = xKoef;
        _yKoef = yKoef;
    }
    void setNameX(QString nameX, QString nameY){
        _nameX = nameX;
        _nameY = nameY;
    }
    //длина в цифрах
    void setSize(qreal x, qreal y){
        _x = x;
        _y = y;
    }


    void setLogicalRange(qreal xMin, qreal xMax, qreal yMin, qreal yMax) {
        _xMin = xMin;
        _xMax = xMax;
        _yMin = yMin;
        _yMax = yMax;
        _xMinTmp = xMin;
        _xMaxTmp = xMax;
        _yMinTmp = yMin;
        _yMaxTmp = yMax;
        update(); // перерисовать
    }



    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const {
        return QRectF(0, -40, _width, _height);
    }
    void setNameGraph(QString text){
        _nameGraph = text;
    }


    void moveAxies(double dx, double dy);
private:
    QString _nameX = "X";
    QString _nameY = "Y";
    qreal _width, _height;
    qreal _xKoef, _yKoef;
    int tickCountX;
    int tickCountY;
    qreal _x, _y;
    qreal _xMin, _xMax, _yMin, _yMax;
    QString _nameGraph = "График";
    double _range = 1;
    qreal _xMinTmp, _xMaxTmp, _yMinTmp, _yMaxTmp;
    double _dx = 0;
    double _dy = 0;

    QString formatTickValue(double value, double range);


};
