#ifndef DEKART_H
#define DEKART_H
#include "Tree.h"
//extern std::mt19937 gen;
const int mod = 1e9 + 9;
struct Dekart {
    int val;
    int prior;
    Dekart* left;
    Dekart* right;
    QPushButton* button;
    Dekart():left(nullptr), right(nullptr) {}
    Dekart(int k) :val(k), prior(rand()%mod),left(nullptr), right(nullptr) {}
};
class Dekart_tree :public QObject{
    Q_OBJECT
public:
    void insert(int k);
    void erase(int k);
    void out(QGraphicsScene*& scene);
    virtual ~Dekart_tree();
    int key;
private:
    void add(Dekart*& tree, int k);
    void remove(Dekart*& tree, int k);
    void split(Dekart* tree,int key,Dekart*& l, Dekart*& r);
    void merge(Dekart*& tree, Dekart* l, Dekart* r);
    std::pair<int,int>draw(QGraphicsScene*& scene,Dekart*& tree,int label);
    Dekart* tree;
public slots:
    void on_button_clicked_dekart();
signals:
    void button_clicked_();
};

#endif // DEKART_H
