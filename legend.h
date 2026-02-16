/*
#pragma once
#include <QGraphicsRectItem>
#include <QString>
#include "function.h"
#include <QVector>

class Legend: public QGraphicsRectItem
{
public:
    Legend();
    void addLegend(const Function &func){
        vec.push_back(func);
    };
    void changeText(QString string = "???");
    void repaint();

private:
    QVector<Function> vec;
};

*/
