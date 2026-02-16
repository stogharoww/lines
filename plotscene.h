#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <plotitem.h>
#include <axisitem.h>



class PlotScene : public QGraphicsScene
{
public:
    PlotScene();
    void viewChange(QGraphicsScene *scene); //смена графика

    void addPlotItem(PlotItem *item); //добавить элемент
    void removePlotItem(PlotItem *item); //убрать элемент

    void setAxes(AxisItem *oxy); //оси


};


