#pragma once
#include <QGraphicsRectItem>
#include <QString>
#include "function.h"
#include <QVector>

class Legend: public QGraphicsRectItem
{
public:
    Legend();
    void addLegend();
    void changeText(QString string = "???");
    void repaint();

private:
    //QVector<Function> vec;
};


