#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QObject>



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



private:

    //void centratePlot();
    QGraphicsView *view;
    QGraphicsScene *scene;
    int weight;
    int height;


};

