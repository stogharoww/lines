#include "plotapi.h"

#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlotAPI *w = new PlotAPI();
    QSize size = w->minimumSize();
    qDebug() << size;
    w->setMinimumSize(100, 100);
    w->show();

    return a.exec();
}
