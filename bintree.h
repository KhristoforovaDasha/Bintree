#ifndef BINTREE_H
#define BINTREE_H
#include "Tree.h"

class bintree:Tree
{
public:
    bintree();
    void out(QGraphicsScene*& scene);
    std::pair<int,int> draw(QGraphicsScene*& scene,Tree*& tree,int label);
};

#endif // BINTREE_H
