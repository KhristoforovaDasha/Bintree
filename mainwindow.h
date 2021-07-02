#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include "avl.h"
#include "dekart.h"
#include "redblack.h"
#include "twothree.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsScene* scene;
    QGraphicsView* view;
    //QGraphicsSceneMouseEvent* event;
    //QSlider* sl;
    AVL_tree avl;
    Dekart_tree dekart;
    RedBlack_tree redblack;
    TwoThree_tree twothree;
    //QPushButton* button;
    void clear();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Add_clicked();
    //void on_button_clicked();

    void on_add_range_clicked();

    void on_comboBox_currentIndexChanged(int index);

    //void on_horizontalSlider_valueChanged(int value);

    void on_slider_valueChanged(int value);
    void on_button_on();
    void on_on_button_on_clicked();

signals:
    void button_update();
private:
    Ui::MainWindow *ui;
};
/*class ellipse:public QGraphicsEllipseItem
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
};*/

#endif // MAINWINDOW_H
