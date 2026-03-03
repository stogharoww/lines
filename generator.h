#pragma once
#include <QVector>
#include "function.h"
#include "numpyc.h"
#include <Curve.h>
#include <QRectF>
#include <QPointF>
#include <QObject>




// генерирует функции по точкам
class Generator: public QObject
{
    Q_OBJECT
public:
    Generator();
    // генератор с уже подготовленными logicalRect и pixelRect
    Generator(QRectF logicalRect, QRectF pixelRect);

    ~Generator(); // нужно удалить NumpyC

    // изменение и настройка viewPort для функций
    void setViewport(QRectF logicalRect, QRectF pixelRect);


    // устанавливаем контрольные точки
    void setControlPoints(const QVector<Point3D>& pts);
    void setControlPoints(const QVector<QPointF>& pts);

    // добавляем контрольные точки
    void addControlPoints(const QVector<Point3D>& pts);
    void addControlPoints(const Point3D& point);
    void addControlPoints(const QPointF& point);
    void addControlPoints(const QVector<QPointF>& pts);

    void removeControlPoints(const QPointF& point, double r);

    // устанавливаем веса
    void setWeights(const QVector<double>& w);

    // устанавливаем degree
    void setDegree(int d);

    // устанавливаем curve_num_points
    void setCurveNumPoints(int n);

    // пересчёт кривой после изменения точек // весов
    void updateCurve();



    // удаляет всё что сделал генератор (для полной очистки)
    void clear();







    // возвращает все функции в генераторе
    const QVector<Function*>& getFunc();

    // очищает все функции в генераторе
    void cleanFunc();

    // генерирует функции, основная функция генератора. Перед этим нужно установить точки и настроить что будем генерировать
    void run();

    // пересчёт в реальном времени: пересчитать Curve, обновить numpy, пересоздать func
    void rebuild();

    // возвращает контрольные точки
    QVector<QPointF> getControlPoints();


    // возвращает логический диапазон из функций
    void getGraphicDiapasone(qreal& minX, qreal& maxX, qreal& minY, qreal& maxY);

    // считает logicalRect
    QRectF logicalRectPls();


signals:
    void empty();




private:
    QVector<Function*> _allFunc;
    NumpyC *_npCurvePointsX;
    NumpyC *_npCurvePointsY;

    NumpyC *_npControlPointsX;
    NumpyC *_npControlPointsY;

    NumpyC *_npPunctirePointsX;
    NumpyC *_npPunctirePointsY;


    QRectF _logicalRect;
    QRectF _pixelRect;


    // добавляет функцию в генератор
    void addFunc(Function *func);

    QVector<Point3D> _CONTROL_POINTS;
    QVector<double> _WEIGHTS;
    // меняет WEIGHTS на вектор, размер которого равен CONTROL_POINTS и заполненный 1
    void weightsUpdate();

    int _CURVE_NUM_POINTS = 2000;
    int _DEGREE = 2;

    Curve _originalCurve;

    QVector<QPointF> _points;
    // переформатирует points в Point3D
    QVector<Point3D> pointsToPoints3D();
    Point3D pointToPoints3D(QPointF point);
    QPointF point3DToPoint(Point3D point);

    // переформатирует Point3D в QPointF
    QVector<QPointF> points3DToQPointF();


    Function *_funcCurve;
    Function *_funcControl;
    Function *_funcPunktire;
    // построение функций
    void buildFunctions();

    // обновляет viewPort функций
    void updateFunctions();

    // заполняет numpy из curve
    void fillCurveNumpy();

    // заполняет numpy координатами контрольных точек
    void fillControlNumpy();

    // пунктирчик
    void fillPunctireNumpy();
};


