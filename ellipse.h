/*#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include "mainwindow.h"

extern MainWindow w;

class ellipse:public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    ellipse();
    QString text;
    MainWindow* window;
protected:
    void mousePressEvent(QMouseEvent* event);
public slots:
    void blah();
};

#endif // ELLIPSE_H*/
