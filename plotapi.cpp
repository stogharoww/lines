#include "plotapi.h"
#include <QGraphicsRectItem>
#include <cmath>
#include <QtMath>
#include <bottom.h>
#include <axisitem.h>
#include <function.h>
#include <numpyc.h>
#include <QPen>
#include <algorithm>
#include <Curve.h>

/**
 * @brief PlotAPI::PlotAPI Инициализирует окно со всей отрисовкой
 */
PlotAPI::PlotAPI()
{
    //первоначальная настройка окна:
    scene = new QGraphicsScene(this);


    resize(800, 400);
    setScene(scene);

    //получить размеры видимой области:
    QSize size = viewport()->size();
    weight = size.width();
    height = size.height();

    scene->setSceneRect(0, 0, weight, height);
    //view->setMouseTracking(true);
    displayMainMenu();


}




void PlotAPI::setMinMaxXY(double minX, double minY, double maxX, double maxY)
{
    _minX = minX;
    _minY = minY;
    _maxX = maxX;
    _maxY = maxY;

    _start_minX = minX;
    _start_minY = minY;
    _start_maxX = maxX;
    _start_maxY = maxY;
}





/**
 * @brief PlotAPI::displayMainMenu
 * Отрисовывает графики, оси и прочее
 */
void PlotAPI::displayMainMenu()
{
    _rect = new QGraphicsRectItem();

    QBrush brush(QColor(250, 250, 210));
    QBrush innerB(QColor(250, 0, 0));
    rectWeight = weight/1.5;
    rectHeight = height/1.5;
    _rect->setRect(0,0,rectWeight, rectHeight);

/*
    //отрисовка функции:
    NumpyC *npX = new NumpyC();
    int minX = -20, maxX = 10;
    npX->arange(minX, maxX, 1000);
    NumpyC *npY = new NumpyC(NumpyC::pow((*npX), 2));

    //double minY = npY->min();
    //double maxY = npY->max();
    //if (maxY > 1000) maxY = 1000;
    //if (minY < -1000) minY = -1000;
    //QPen pen = QPen(Qt::blue, 2);
    //example 1

    NumpyC *npXSPLINE = new NumpyC();
    double minXX = 10.001, maxXX = 50;
    npXSPLINE->arange(minXX, maxXX, 1000);
    NumpyC *npYtmp = new NumpyC();
    NumpyC *npYSPLINE = new NumpyC(NumpyC::cos(*npXSPLINE) * 50);
    double minYtmp = npYSPLINE->min(), maxYtmp = npY->max();
    npYtmp->arange(minYtmp, maxYtmp, 1000);
    NumpyC npYres;
    NumpyC npXres;
    npYres = *npY + *npYtmp + *npYSPLINE;
    npXres = *npX + *npXSPLINE;
    Function *func = new Function(npXres, npYres);
    minX = npXres.min(), maxX = npXres.max();
    double minY = npYres.min(), maxY = npYres.max();
    func->setHeight(rectWeight, rectHeight); //смещение наверх и прочее
    func->setViewport(QRectF(minX, minY, maxX - minX, maxY - minY),
                      QRectF(0, 0, rectWeight, rectHeight));
*/

    const std::vector<Point3D> CONTROL_POINTS
        {
            {1, 1.2, 0},
            {1.5, 1.39, 0},
            {3, 1.5, 0},
            {4.5, 1.39, 0},
            {5, 1.2, 0}
        };

    const std::vector<double> WEIGHTS(CONTROL_POINTS.size(), 1);   // Весовые коэффициенты контрольных точек
    const int CURVE_NUM_POINTS = 61;   // Кол-во точек, из которых будет состоять кривая
    const int DEGREE = 2;   // Степень кривой

    Curve originalCurve(CONTROL_POINTS, WEIGHTS, DEGREE, CURVE_NUM_POINTS);

    // === Парабола: x² на [-20, 9.5] ===
    NumpyC* npX1 = new NumpyC();
    npX1->arange(-20, 9.5, 800);
    NumpyC* npY1 = new NumpyC(NumpyC::pow(*npX1, 2));
    //NumpyC* npY1C = new NumpyC(NumpyC::sin(*npX1) * 50);
    //*npY1 = *npY1 + *npY1C;

    // === Синусоида: cos(x)*50 на [10.5, 50] ===
    NumpyC* npX2 = new NumpyC();
    npX2->arange(10.5, 50, 1000);
    NumpyC* npY2 = new NumpyC(NumpyC::cos(*npX2) * 50);

    // === Кубический сплайн на [9.5, 10.5] ===
    double x0 = 9.5, x1 = 10.5;
    double y0 = x0 * x0;                     // значение параболы
    double y1 = std::cos(x1) * 50;           // значение синусоиды
    double dy0 = 2 * x0;                     // производная параболы
    double dy1 = -std::sin(x1) * 50;         // производная синусоиды

    double h = x1 - x0;
    double a = y0;
    double b = dy0;
    double c = (3*(y1 - y0)/h - 2*dy0 - dy1) / h;
    double d = (2*(y0 - y1)/h + dy0 + dy1) / (h*h);

    // === Генерация X и Y по сплайну ===
    NumpyC blendX;
    blendX.arange(x0, x1, 200);
    NumpyC blendY = blendX.map([=](double x) {
        double dx = x - x0;
        return a + b*dx + c*dx*dx + d*dx*dx*dx;
    });

    // === Объединение всех участков ===
    NumpyC npXres = npX1->copy();
    npXres.push_back(blendX);
    npXres.push_back(*npX2);

    NumpyC npYres = npY1->copy();
    npYres.push_back(blendY);
    npYres.push_back(*npY2);

    // === Вычисление логических границ ===
    double minX, maxX, minY, maxY;

    if (_minX == _maxX){ // 1 запуск с инициализацией _logicalRect

        minX = npXres.min();
        maxX = npXres.max();
        minY = std::floor(npYres.min() / 100.0) * 100.0;
        maxY = std::ceil(npYres.max() / 100.0) * 100.0;

        _logicalRect = QRectF(minX, minY, maxX - minX, maxY - minY);
        _baseRect = _logicalRect;
        setMinMaxXY(minX, minY, maxX, maxY);

    }
    else {
        // используем уже существующий _logicalRect
        minX = _logicalRect.left();
        maxX = _logicalRect.right();
        minY = _logicalRect.top();
        maxY = _logicalRect.bottom();
    }
    // === Отрисовка ===
    func = new Function(npXres, npYres);
    //func->setHeight(rectWeight, rectHeight); //смещение наверх и прочее



    _pixelRect = QRectF(0, 0, rectWeight, rectHeight);
    func->setViewport(_logicalRect, _pixelRect);






    //double scaleX = rectWeight / (maxX - minX);
    //double scaleY = rectHeight / (maxY - minY);
    //func->setMins(minX, minY);
    //func->setScale(scaleX, -scaleY); // инверсия Y
    //func->setOffset(0, rectHeight);  // смещение вверх



    func->setParentItem(_rect);

    //оси:
    double x, y;
    x = (weight - rectWeight) / 2;
    y = (height - rectHeight) / 2;
    _rect->setPos(x, y);
    axies = new AxisItem(rectWeight, rectHeight);
    axies->setZValue(2); //наложение поверх всего
    axies->setSize(rectWeight, rectHeight); // физический размер
    axies->setLogicalRange(minX, maxX, minY, maxY);    // логический диапазон
    axies->setNameX("Ось Х", "Ось Y");
    axies->setNameGraph("Парабола и потом синус");
    scene->addItem(axies);
    axies->setPos(x, y);
    _rect->setBrush(brush);


    setMinMaxXY(minX, minY, maxX, maxY);


    graphRect = QRectF(x, y, rectWeight, rectHeight);

    scene->addItem(_rect);
    QString firstBtm = "Bottom кнопка";
    Bottom *testBottom = new Bottom("", 40, 40);
    testBottom->setPuxmap("://res/icons8-home-30.png");
    scene->addItem(testBottom);
    connect(testBottom, &Bottom::clicked, this, &PlotAPI::bottomClicked);

    interaction = new PlotInteraction(graphRect);
    interaction->setZValue(105);
    scene->addItem(interaction);

    connect(interaction, &PlotInteraction::requested, this, &PlotAPI::moveEvent);

    _rectMoving = new QGraphicsRectItem();
    _rectMoving->setZValue(100);
    _textItem = new QGraphicsTextItem("Text", _rectMoving);
    //_textItem->setZValue(101);




    connect(interaction, &PlotInteraction::moving, this, &PlotAPI::movingMouse);
    connect(interaction, &PlotInteraction::leaved, this, &PlotAPI::leaved);
    connect(interaction, &PlotInteraction::wheel, this, &PlotAPI::wheel);

}



void PlotAPI::moveEvent(QPointF delta)
{
    double dx = -delta.x() * (_maxX - _minX) / rectWeight;
    double dy = delta.y() * (_maxY - _minY) / rectHeight;

    _minX += dx;
    _maxX += dx;
    _minY += dy;;
    _maxY += dy;;

    _logicalRect.setRect(_minX, _minY, _maxX - _minX, _maxY - _minY);
    //_logicalRect = logWheelRect(_logicalRect);
    func->setViewport(_logicalRect,
                      _pixelRect);


    axies->moveAxies(dx, dy);

    scene->update();
}

void PlotAPI::movingMouse(QPointF pos)
{
    // позиция квадрата
    QBrush brushRect(QColor(0, 0, 0, 180));
    _rectMoving->setBrush(brushRect);
    _rectMoving->setRect(0, 0, -100, -20);
    _rectMoving->setPos(pos);

    // позиция текста
    QRectF tr = _textItem->boundingRect();
    QRectF rr = _rectMoving->rect();
    qreal xR = rr.left() + (rr.width() - tr.width()) / 2.0;
    qreal yR = rr.top() + (rr.height() - tr.height()) / 2.0;

    _textItem->setPos(xR, yR);

    scene->update();
    //scene->addItem(_rectMoving);
    /*
    _rectMoving = new QGraphicsRectItem();
    int x = pos.x();
    int y = pos.y();
    QBrush brush(QColor(0, 0, 0));
    _rectMoving->setBrush(brush);
    _rectMoving->setRect(x, y, 50, 20);
    scene->addItem(_rectMoving);
*/


    //текст
    QPointF posInFunc = func->mapFromScene(interaction->mapToScene(pos));
    QPointF logicalPos = func->pixelToLogical(posInFunc);
    QString text = QString("x: %1, y: %2")
                       .arg(logicalPos.x(), 0, 'f', 2)
                       .arg(logicalPos.y(), 0, 'f', 2);

    _textItem->setPlainText(text);




}

void PlotAPI::leaved(bool leav)
{
    if (!leav){
        scene->addItem(_rectMoving);
        //scene->addItem(_textItem);
    }
    if (leav){
        //qDebug() << "leaved";

        scene->removeItem(_rectMoving);
        //scene->removeItem(_textItem);
        scene->update();
    }
}

void PlotAPI::wheel(QPointF localPos, int delta)
{
    // масштабируем функцию
    flagWheel = 1;

    double k = 0.1;
    _factor -= k * delta / 120;
    _factor = std::max(0.001, _factor);

    _factor = std::min(_factor, 2.0);
    qDebug() << _factor;

    QPointF scenePos = interaction->mapToScene(localPos);
    QPointF posInFunc = func->mapFromScene(scenePos);
    QPointF logicalPos = func->pixelToLogical(posInFunc);

    QRectF r = _logicalRect;

    double newW = _baseRect.width() * _factor;
    double newH = _baseRect.height() * _factor;

    double dx = logicalPos.x() - r.left();
    double dy = logicalPos.y() - r.top();

    double kx = dx / r.width();
    double ky = dy / r.height();

    double newLeft = logicalPos.x() - newW * kx;
    double newTop = logicalPos.y() - newH * ky;
    QRectF newRect = QRectF(newLeft, newTop, newW, newH);
    if (newRect.width() < 10) return;
    if (newRect.height() < 10) return;

    _logicalRect = newRect;







    //QRectF newRect = logWheelRect(_logicalRect);
    //if (newRect.width() < 10) return;
    //if (newRect.height() < 10) return;

    //_logicalRect = newRect;

    _minX = _logicalRect.left();
    _maxX = _logicalRect.right();
    _minY = _logicalRect.top();
    _maxY = _logicalRect.bottom();


    func->setViewport(_logicalRect, _pixelRect);

    // применяем масштабирование на оси
    axies->setLogicalRange(_logicalRect.left(), _logicalRect.right(), _logicalRect.top(), _logicalRect.bottom());



    scene->update();

}

void PlotAPI::backToHomeXY()
{
    _minX = _start_minX;
    _minY = _start_minY;
    _maxX = _start_maxX;
    _maxY = _start_maxY;
}

void PlotAPI::functionAndMove()
{

}

QRectF PlotAPI::logWheelRect(QRectF logicalRect)
{
    QRectF rect = logicalRect;
    QPointF center = rect.center();
    QSizeF newSize = rect.size() * _factor;


    QRectF newRect(center - QPointF(newSize.width() / 2, newSize.height() / 2), newSize);

    return newRect;
}


void PlotAPI::bottomClicked(){
    /*
    resize(800, 400);
    //возвращаем график к точке 0:0
    _logicalRect = _baseRect;
    backToHomeXY();
    _factor = 1;
    flagWheel = 0;

    _pixelRect.setRect(0, 0, rectWeight, rectHeight);

    func->setViewport(_logicalRect, _pixelRect);


    axies->setLogicalRange(_minX, _maxX, _minY, _maxY);
    axies->moveAxies(0, 0);


    scene->update();
*/

    resize(800, 400);
    scene->clear();

    _minX = 0;
    _maxX = 0;
    _factor = 1;
    flagWheel = 0;

    displayMainMenu();


}



/*
void PlotAPI::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (!graphRect.contains(pos)) return;

    if (event->button() == Qt::LeftButton){
        dragging = true;
        lastMousePos = event->pos();
    }
}

void PlotAPI::mouseMoveEvent(QMouseEvent *event)
{
    if (!dragging) return;
    QPoint pos = event->pos();
    if (!graphRect.contains(pos)) return;

    QPoint delta = event->pos() - lastMousePos;
    lastMousePos = event->pos();

    double dx = -delta.x() * (_maxX - _minX) / rectWeight;
    double dy = delta.y() * (_maxY - _minY) / rectHeight;

    _minX += dx;
    _maxX += dx;
    _minY += dy;;
    _maxY += dy;;


    func->setViewport(QRectF(_minX, _minY, _maxX - _minX, _maxY - _minY),
                      QRectF(0, 0, rectWeight, rectHeight));


    axies->setLogicalRange(_minX, _maxX, _minY, _maxY);

    scene->update();

}

void PlotAPI::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (!graphRect.contains(pos)) return;
    if (event->button() == Qt::LeftButton){
        dragging = false;
    }
}

*/




double PlotAPI::takeData() const
{
    return weight;
}


/**
 * @brief PlotAPI::resizeEvent считает новые размеры окна и вызывает перерисовку
 * @param event событие изменения размеров окна QWidget (QGraphicsView)
 */
void PlotAPI::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    QSize newSize = viewport()->size();
    weight = newSize.width();
    height = newSize.height();
    //_logicalRect = logWheelRect(_logicalRect);

    refresh();
}
/**
 * @brief PlotAPI::refresh перерисовывает окно с новыми weight и height
 */
void PlotAPI::refresh()
{

    scene->clear();
    scene->update();
    scene->setSceneRect(0, 0, weight, height);
    displayMainMenu();
    //_logicalRect = logWheelRect(_logicalRect);
    func->setViewport(_logicalRect, _pixelRect);
    axies->setLogicalRange(_logicalRect.left(), _logicalRect.right(),
                           _logicalRect.top(), _logicalRect.bottom());
    scene->update();
    //fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);





}
