#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include "function.h"
#include "axisitem.h"
#include <QRectF>
#include "plotinteraction.h"
#include <QPointF>




class PlotAPI : public QGraphicsView
{
    Q_OBJECT
public:
    PlotAPI();
    void displayMainMenu();
    double takeData() const; //получить данные

    // <summary>что делает</summary>
    // <param_name=event>Событие изменения размеров окна</param_name=event>

    void resizeEvent(QResizeEvent* event) override;
    void refresh(); //перерисовка в зависимости от размеров окна
    /**
     * @brief showAxis показывает оси Х и Y
     */
    void showAxis();
    void bottomClicked();

/*
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
*/
    void setMinMaxXY(double minX, double minY, double maxX, double maxY);

    void moveEvent(QPointF delta);

    void movingMouse(QPointF pos);

    void leaved(bool leav);

private:

    //void centratePlot();
    QGraphicsView *view;
    QGraphicsScene *scene;
    int weight;
    int height;
    bool dragging = false; //перетаскивание
    QPoint lastMousePos; //последнее место где была мышка для перетаскивания графика
    double _minX = 0;
    double _minY = 0;
    double _maxX = 0;
    double _maxY = 0;
    double rectWeight;
    double rectHeight;
    Function* func;
    AxisItem *axies;
    QRectF graphRect;
    PlotInteraction *interaction;
    double _start_minX;
    double _start_minY;
    double _start_maxX;
    double _start_maxY;
    QGraphicsRectItem * _rectMoving;
    QGraphicsTextItem * _textItem;
    QGraphicsRectItem *_rect;

    void backToHomeXY();

    void functionAndMove();

};

