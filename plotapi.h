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
#include "generator.h"
#include "bottom.h"
#include <QFileDialog>



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


/*
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
*/

    void setMinMaxXY(double minX, double minY, double maxX, double maxY);

public slots:
    void bottomHomeClicked();
    void moveEvent(QPointF delta);
    void movingMouse(QPointF pos);
    void leaved(bool leav);
    void wheel(QPointF localPos, int delta);
    void btmPunktireClicked();
    void btmPointClicked();
    void btmLineClicked();
    void btmAddingPoints();
    void btmCleanAll();
    void btmReadFile();
    void btmSaveToPng();
    // редактирование точек
    void editPoints(QPointF pos, Qt::MouseButton button);
    void emptyFuncs();

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
    //Function* func;
    void updateFunctions();

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
    QRectF _baseRect;

    void backToHomeXY();


    bool fPoint = true;
    bool fLine = true;
    bool fPunktire = true;
    bool flagEdit = true;

    //bottoms
    Bottom *homeBtm;
    Bottom *punktireBtm;
    Bottom *pointsBtm;
    Bottom *lineBtm;
    Bottom *cleanAllBtm;
    Bottom *readFileBtm;
    Bottom *saveBtm;
    QVector<Bottom*> btms;
    void changeBtmColor(bool flag, Bottom &btm, QColor col = QColor(Qt::gray));
    void changeVisible(bool flag, int index);
    void applyButtonStates();

    Bottom *addingPointsBtm;


    QRectF _logicalRect;
    QRectF _pixelRect;

    Generator *_generator = nullptr;

    double _factor = 1;

    bool flagWheel = 0;



    QRectF logWheelRect(QRectF logicalRect);

    QVector<Point3D> CONTROL_POINTS
        {
            {1, 1.2, 0},
            {1.5, 1.39, 0},
            {3, 1.5, 0},
            {4.5, 1.39, 0},
            {5, 1.2, 0}
        };


    void readFile(const QString &filePath);
    void saveToPng(const QString &filePath);
};

