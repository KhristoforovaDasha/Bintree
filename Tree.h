#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <cmath>
#include <queue>
#include <random>
#include <ctime>
#include <set>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPaintDevice>
#include <QPushButton>
#include <QObject>
#include <QSignalMapper>
#include <QDataStream>
class Tree
{
public:
    virtual void insert(int k) = 0;
    virtual void erase(int k) = 0;
};
#endif // TREE_H
