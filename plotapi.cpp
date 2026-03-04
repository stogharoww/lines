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
#include <QMessageBox>
#include <QRegularExpression>



/**
 * @brief PlotAPI::PlotAPI Инициализирует окно со всей отрисовкой
 */
PlotAPI::PlotAPI()
{
    //первоначальная настройка окна:
    scene = new QGraphicsScene(this);


    resize(800, 400);
    setScene(scene);

    //тёмная тема приложения
    setStyleSheet(R"(
        QGraphicsView {
            background-color: #1e1e1e;
            color: #dddddd;
            border: none;
        }
    )");



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


    // отрисовка функций
    double x, y;
    x = (weight - rectWeight) / 2;
    y = (height - rectHeight) / 2;
    _rect->setPos(x, y);


    if (_generator) delete _generator;
    _generator = new Generator();
    _generator->setControlPoints(CONTROL_POINTS);

    _pixelRect = QRectF(0, 0, rectWeight, rectHeight);


    // вычисление логических координат
    qreal minX, maxX, minY, maxY;


    if (_minX == _maxX){

        _logicalRect = _generator->logicalRectPls();
        minX = _logicalRect.left();
        maxX = _logicalRect.right();
        minY = _logicalRect.top();
        maxY = _logicalRect.bottom();
        setMinMaxXY(minX, minY, maxX, maxY);
        _baseRect = _logicalRect;


    }
    else{
        minX = _logicalRect.left();
        maxX = _logicalRect.right();
        minY = _logicalRect.top();
        maxY = _logicalRect.bottom();
    }

    _generator->setViewport(_logicalRect, _pixelRect);
    _generator->run();

    updateFunctions();




    //оси:

    axies = new AxisItem(rectWeight, rectHeight);
    axies->setZValue(2); //наложение поверх всего
    axies->setSize(rectWeight, rectHeight); // физический размер
    axies->setLogicalRange(minX, maxX, minY, maxY);    // логический диапазон
    axies->setNameX("Ось Х", "Ось Y");
    axies->setNameGraph("График контрольных точек");
    scene->addItem(axies);
    axies->setPos(x, y);
    _rect->setBrush(brush);


    setMinMaxXY(minX, minY, maxX, maxY);


    graphRect = QRectF(x, y, rectWeight, rectHeight);


    scene->addItem(_rect);
    // кнопочки
    //QString firstBtm = "Bottom кнопка";

    //home:
    Bottom *homeBtm = new Bottom("", 40, 40);
    homeBtm->setPuxmap("://res/icons8-home-30.png");
    scene->addItem(homeBtm);
    connect(homeBtm, &Bottom::clicked, this, &PlotAPI::bottomHomeClicked);

    // скрыть / показать пунктир
    punktireBtm = new Bottom("", 40, 40);
    punktireBtm->setPos(40, 0);
    punktireBtm->setPuxmap("://res/punktire.png");
    scene->addItem(punktireBtm);
    connect(punktireBtm, &Bottom::clicked, this, &PlotAPI::btmPunktireClicked);

    // скрыть / показать точки
    pointsBtm = new Bottom("", 40, 40);
    pointsBtm->setPos(0, 40);
    pointsBtm->setPuxmap("://res/point.png");
    scene->addItem(pointsBtm);
    connect(pointsBtm, &Bottom::clicked, this, &PlotAPI::btmPointClicked);

    // скрыть / показать функцию
    lineBtm = new Bottom("", 40, 40);
    lineBtm->setPos(40, 40);
    lineBtm->setPuxmap("://res/line.png");
    scene->addItem(lineBtm);
    connect(lineBtm, &Bottom::clicked, this, &PlotAPI::btmLineClicked);

    // вкл/выкл режим редактирования точек
    addingPointsBtm = new Bottom("", 40, 40);
    addingPointsBtm->setPos(0, 80);
    addingPointsBtm->setPuxmap("://res/edit.png");
    scene->addItem(addingPointsBtm);
    connect(addingPointsBtm, &Bottom::clicked, this, &PlotAPI::btmAddingPoints);

    // очистить всё
    cleanAllBtm = new Bottom("", 40, 40);
    cleanAllBtm->setPos(40, 80);
    cleanAllBtm->setPuxmap("://res/cleanAll.png");
    scene->addItem(cleanAllBtm);
    connect(cleanAllBtm, &Bottom::clicked, this, &PlotAPI::btmCleanAll);

    // взять точки из файла

    readFileBtm = new Bottom("", 40, 40);
    readFileBtm->setPos(0, 120);
    readFileBtm->setPuxmap("://res/read.png");
    scene->addItem(readFileBtm);
    connect(readFileBtm, &Bottom::clicked, this, &PlotAPI::btmReadFile);

    // интерактив
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
    connect(interaction, &PlotInteraction::clicked, this, &PlotAPI::editPoints);

    connect(_generator, &Generator::empty, this, &PlotAPI::emptyFuncs);
    applyButtonStates();
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
    _generator->setViewport(_logicalRect, _pixelRect);


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

    //текст
    auto funcs = _generator->getFunc();
    if (funcs.isEmpty()) return;
    Function* mainFunc = funcs[0];
    QPointF posInFunc = _rect->mapFromScene(interaction->mapToScene(pos));
    QPointF logicalPos = mainFunc->pixelToLogical(posInFunc);
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

    double zoomStep = 1.1;

    if (delta > 0)
        _factor /= zoomStep;
    else
        _factor *= zoomStep;

    _factor = std::max(_factor, 0.0355841);
    _factor = std::min(_factor, 240463.0);

    //_factor = std::min(_factor, 2.0);
    qDebug() << _factor;

    auto funcs = _generator->getFunc();
    if (funcs.isEmpty()) return;
    Function* mainFunc = funcs[0];
    QPointF scenePos = interaction->mapToScene(localPos);
    QPointF posInFunc = _rect->mapFromScene(scenePos);
    QPointF logicalPos = mainFunc->pixelToLogical(posInFunc);

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
    //if (newRect.width() < 10) return;
    //if (newRect.height() < 10) return;

    _logicalRect = newRect;

    _minX = _logicalRect.left();
    _maxX = _logicalRect.right();
    _minY = _logicalRect.top();
    _maxY = _logicalRect.bottom();


    _generator->setViewport(_logicalRect, _pixelRect);

    // применяем масштабирование на оси
    axies->setLogicalRange(_logicalRect.left(), _logicalRect.right(), _logicalRect.top(), _logicalRect.bottom());


    scene->update();

}

void PlotAPI::btmPunktireClicked()
{
    changeBtmColor(fPunktire, *punktireBtm);
    changeVisible(fPunktire, 1);
    fPunktire = !fPunktire;
}

void PlotAPI::btmPointClicked()
{
    changeBtmColor(fPoint, *pointsBtm);
    changeVisible(fPoint, 2);
    fPoint = !fPoint;
}

void PlotAPI::btmLineClicked()
{
    changeBtmColor(fLine, *lineBtm);
    changeVisible(fLine, 0);
    fLine = !fLine;
}

void PlotAPI::btmAddingPoints()
{
    interaction->creating();
}

void PlotAPI::btmCleanAll()
{
    _generator->removeAll();
    emptyFuncs();
    //scene->update();
}

void PlotAPI::btmReadFile()
{

    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Выберите файл",
        QString(),
        "Текстовые файлы (*.txt);;Все файлы (*.*)"
        );

    if (filePath.isEmpty()) return;
    btmCleanAll();
    _minX = _maxX = 0;
    readFile(filePath);

}

void PlotAPI::editPoints(QPointF pos, Qt::MouseButton button)
{
    // pos -> local pos
    auto funcs = _generator->getFunc();
    if (funcs.isEmpty()) return;
    Function* mainFunc = funcs[0];
    QPointF scenePos = interaction->mapToScene(pos);
    QPointF posInFunc = _rect->mapFromScene(scenePos);
    QPointF logicalPos = mainFunc->pixelToLogical(posInFunc);

    QPointF logicalRadius = mainFunc->pixelToLogical(posInFunc + QPointF(4, 0));
    double r = fabs(logicalRadius.x() - logicalPos.x());


    // add point
    if (button == Qt::LeftButton){

        _generator->addControlPoints(logicalPos);
        CONTROL_POINTS = _generator->getControlPoints();
    }

    //remove point
    if (button == Qt::RightButton){
        _generator->removeControlPoints(logicalPos, r);
        CONTROL_POINTS = _generator->getControlPoints();
    }
    updateFunctions();
    scene->update();
}

void PlotAPI::emptyFuncs()
{

    for (auto &f : _generator->getFunc())
        f->setVisible(false);

}

void PlotAPI::updateFunctions()
{
    auto funcs = _generator->getFunc();
    if (funcs.isEmpty()) return;

    for (const auto& f : _generator->getFunc()){
        f->setParentItem(_rect);
        //scene->addItem(f);
    }

    funcs[0]->setVisible(fLine);
    funcs[1]->setVisible(fPunktire);
    funcs[2]->setVisible(fPoint);


}

void PlotAPI::backToHomeXY()
{
    _minX = _start_minX;
    _minY = _start_minY;
    _maxX = _start_maxX;
    _maxY = _start_maxY;
}


void PlotAPI::changeBtmColor(bool flag, Bottom &btm, QColor col)
{
    if (flag){
        btm.setColor(col);
    } else if (!flag){
        btm.setColor(Qt::darkCyan);
    }
}

void PlotAPI::changeVisible(bool flag, int index)
{
    if (flag)
        _generator->getFunc()[index]->setVisible(false);
    else if (!flag){
        _generator->getFunc()[index]->setVisible(true);
    }
}

void PlotAPI::applyButtonStates()
{
    changeBtmColor(!fLine, *lineBtm, Qt::gray);
    changeBtmColor(!fPoint, *pointsBtm, Qt::gray);
    changeBtmColor(!fPunktire, *punktireBtm, Qt::gray);
}




QRectF PlotAPI::logWheelRect(QRectF logicalRect)
{
    QRectF rect = logicalRect;
    QPointF center = rect.center();
    QSizeF newSize = rect.size() * _factor;


    QRectF newRect(center - QPointF(newSize.width() / 2, newSize.height() / 2), newSize);

    return newRect;
}

void PlotAPI::readFile(const QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QVector<QPointF> points;

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    while (!in.atEnd()){
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList parts = line.split(QRegularExpression("\\s+"));
        if (parts.size() != 2)
            continue;

        bool ok1 = false, ok2 = false;
        double x = parts[0].toDouble(&ok1);
        double y = parts[1].toDouble(&ok2);

        if (ok1 && ok2)
            points.append(QPointF(x, y));
    }
    //QString content = in.readAll();
    file.close();

    _generator->setControlPoints(points);
    CONTROL_POINTS = _generator->getControlPoints();

    refresh();

}


void PlotAPI::bottomHomeClicked()
{
    resize(800, 400);
    scene->clear();
    fPoint = true;
    fLine = true;
    fPunktire = true;
    _minX = 0;
    _maxX = 0;
    _factor = 1;
    flagWheel = 0;
    CONTROL_POINTS = QVector<Point3D>
        {
            {1, 1.2, 0},
            {1.5, 1.39, 0},
            {3, 1.5, 0},
            {4.5, 1.39, 0},
            {5, 1.2, 0}
        };

    displayMainMenu();
}




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
    applyButtonStates();
    axies->setLogicalRange(_logicalRect.left(), _logicalRect.right(),
                           _logicalRect.top(), _logicalRect.bottom());
    scene->update();
}
