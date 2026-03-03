#include "generator.h"
#include <QDebug>

Generator::Generator() :
    _logicalRect(0, 0, 1, 1),
    _pixelRect(0, 0, 1, 1),
    _npCurvePointsX(nullptr),
    _npCurvePointsY(nullptr),
    _npControlPointsX(nullptr),
    _npControlPointsY(nullptr),
    _funcCurve(nullptr),
    _funcControl(nullptr),
    _npPunctirePointsX(nullptr),
    _npPunctirePointsY(nullptr)
{
}


Generator::Generator(QRectF logicalRect, QRectF pixelRect) :
    Generator()
{
    _logicalRect = logicalRect;
    _pixelRect = pixelRect;
}

Generator::~Generator()
{
    //cleanFunc();
    delete _npCurvePointsX;
    delete _npCurvePointsY;
    delete _npControlPointsX;
    delete _npControlPointsY;
}


void Generator::setViewport(QRectF logicalRect, QRectF pixelRect)
{
    _logicalRect = logicalRect;
    _pixelRect = pixelRect;
    updateFunctions();
}




void Generator::setControlPoints(const QVector<Point3D> &points)
{
    _CONTROL_POINTS = points;
    weightsUpdate();
    updateCurve();
}

void Generator::setControlPoints(const QVector<QPointF> &points)
{
    _points = points;
    QVector<Point3D> control_points = pointsToPoints3D();
    _CONTROL_POINTS = control_points;
    weightsUpdate();
    updateCurve();
}




void Generator::addControlPoints(const QVector<Point3D> &points)
{
    _CONTROL_POINTS += points;
    weightsUpdate();
    rebuild();
}

void Generator::addControlPoints(const Point3D &point)
{
    _CONTROL_POINTS.append(point);
    weightsUpdate();
    rebuild();
}

void Generator::addControlPoints(const QPointF &point)
{
    _CONTROL_POINTS.append(pointToPoints3D(point));
    weightsUpdate();
    rebuild();
}

void Generator::addControlPoints(const QVector<QPointF> &pts)
{
    _points += pts;
    QVector<Point3D> control_points = pointsToPoints3D();
    _CONTROL_POINTS = control_points;
    weightsUpdate();
    rebuild();
}

void Generator::setWeights(const QVector<double> &w)
{
    if (w.size() != _WEIGHTS.size()){
        qDebug() << "Generator::setWeights: w != CONTROL_POINTS";
        return;
    }
    else{
        _WEIGHTS = w;
    }
}

void Generator::setDegree(int d)
{
    _DEGREE = d;
    rebuild();
}

void Generator::setCurveNumPoints(int n)
{
    _CURVE_NUM_POINTS = n;
    rebuild();
}

void Generator::updateCurve()
{
    if (_WEIGHTS.size() != _CONTROL_POINTS.size())
        weightsUpdate();

    std::vector<Point3D> pts(_CONTROL_POINTS.begin(), _CONTROL_POINTS.end());
    std::vector<double> w(_WEIGHTS.begin(), _WEIGHTS.end());

    _originalCurve = Curve(pts, w, _DEGREE, _CURVE_NUM_POINTS);
}

void Generator::clear()
{
    _allFunc.clear();
    _CONTROL_POINTS.clear();
    _WEIGHTS.clear();
    _points.clear();
}

const QVector<Function *> &Generator::getFunc()
{
    return _allFunc;
}

void Generator::cleanFunc()
{
    /*
    for (auto f : _allFunc)
        delete f;
    _allFunc.clear();
*/
}

void Generator::run()
{
    if (_CONTROL_POINTS.isEmpty()){
        qDebug() << "Generator::run: _CONTROL_POINTS is empty";
        return;
    }

    updateCurve();

    fillCurveNumpy();
    fillControlNumpy();
    fillPunctireNumpy();

    buildFunctions();
}

void Generator::rebuild()
{
    cleanFunc();
    updateCurve();
    fillCurveNumpy();
    fillControlNumpy();
    fillPunctireNumpy();
    buildFunctions();
}

void Generator::getGraphicDiapasone(qreal &minX, qreal &maxX, qreal &minY, qreal &maxY)
{
    const auto& pts = _originalCurve.getCurvePoints();
    const auto& ptsControl = _originalCurve.getControlPoints();
    if (pts.empty()) return;

    minX = maxX = pts[0].x;
    minY = maxY = pts[0].y;

    for (const auto& p : pts){
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }
    for (const auto& p : ptsControl){
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }

    qreal dx = (maxX - minX) * 0.01;
    qreal dy = (maxY - minY) * 0.01;

    minX -= dx;
    maxX += dx;
    minY -= dy;
    maxY += dy;

}

QRectF Generator::logicalRectPls()
{
    qreal minX = 0, maxX = 0, minY = 0, maxY = 0;
    getGraphicDiapasone(minX, maxX, minY, maxY);
    if (maxX == minX || maxY == minY) return QRectF(0, 0, 1, 1);
    return QRectF(minX, minY, maxX - minX, maxY - minY);
}


void Generator::addFunc(Function *func)
{
    _allFunc.append(func);
}



void Generator::weightsUpdate()
{
    QVector<double> weighs(_CONTROL_POINTS.size(), 1);
    _WEIGHTS = weighs;
}







QVector<Point3D> Generator::pointsToPoints3D()
{
    QVector<Point3D> points3D;
    points3D.reserve(_points.size());

    for (const auto &point : _points)
        points3D.append(Point3D(point.x(), point.y(), 0));

    return points3D;
}

Point3D Generator::pointToPoints3D(QPointF point)
{
    return Point3D(point.x(), point.y(), 0);
}

QVector<QPointF> Generator::points3DToQPointF()
{
    QVector<QPointF> pointsF;
    pointsF.reserve(_CONTROL_POINTS.size());

    for (const auto &p : _CONTROL_POINTS)
        pointsF.append(QPointF(p.x, p.y));

    return pointsF;
}

void Generator::buildFunctions()
{

    delete _funcCurve;
    delete _funcControl;


    _funcCurve = new Function(*_npCurvePointsX, *_npCurvePointsY);
    _funcControl = new Function(*_npControlPointsX, *_npControlPointsY);
    _funcPunktire = new Function(*_npPunctirePointsX, *_npPunctirePointsY);

    addFunc(_funcCurve);
    addFunc(_funcControl);
    addFunc(_funcPunktire);

    for (auto &f : _allFunc){
        f->setViewport(_logicalRect, _pixelRect);
    }


    _funcControl->pointed();
    _funcPunktire->punctire();

}

void Generator::updateFunctions()
{
    for (auto f : _allFunc){
        f->setViewport(_logicalRect, _pixelRect);
    }
}

void Generator::fillCurveNumpy()
{
    delete _npCurvePointsX;
    delete _npCurvePointsY;
    _npCurvePointsX = new NumpyC();
    _npCurvePointsY = new NumpyC();

    _npCurvePointsX->reserve(_CURVE_NUM_POINTS);
    _npCurvePointsY->reserve(_CURVE_NUM_POINTS);

    for (const auto &curvePoint : _originalCurve.getCurvePoints()) {
        _npCurvePointsX->pushBack(curvePoint.x);
        _npCurvePointsY->pushBack(curvePoint.y);
    }
}

void Generator::fillControlNumpy()
{
    delete _npControlPointsX;
    delete _npControlPointsY;
    _npControlPointsX = new NumpyC();
    _npControlPointsY = new NumpyC();




    _npControlPointsX->reserve(_CONTROL_POINTS.size());
    _npControlPointsY->reserve(_CONTROL_POINTS.size());

    for (const auto &controlPoint : _originalCurve.getControlPoints()){
        _npControlPointsX->pushBack(controlPoint.x);
        _npControlPointsY->pushBack(controlPoint.y);
    }
}

void Generator::fillPunctireNumpy()
{
    delete _npPunctirePointsX;
    delete _npPunctirePointsY;
    _npPunctirePointsX = new NumpyC();
    _npPunctirePointsY = new NumpyC();
    NumpyC tmpX;
    NumpyC tmpY;

    double k = _CURVE_NUM_POINTS / 10;

    for (int i = 1; i < _npControlPointsX->size(); i++){
        tmpX.arange((*_npControlPointsX)[i - 1], (*_npControlPointsX)[i], k);
        tmpY.arange((*_npControlPointsY)[i - 1], (*_npControlPointsY)[i], k);
        _npPunctirePointsX->push_back(tmpX);
        _npPunctirePointsY->push_back(tmpY);
    }
}

