#ifndef AVL_H
#define AVL_H
#include "Tree.h"
#include <QInputDialog>
//extern int left_son;
struct AVL:public QObject {
    int val;
    AVL* left;
    AVL* right;
    int height;
    AVL (int k) {
        val = k, left = right = nullptr, height = 1;
    }
};
class AVL_tree :public QObject{
    Q_OBJECT
public:
    void insert( int k);
    void init(QGraphicsScene* scene, QGraphicsView* view);
    virtual ~AVL_tree();
    void out(QGraphicsScene*& scene);
    friend void change(int ver);
    void erase(int k);
    int key;
private:
    void add(AVL*& tree, int k);
    int findmin(AVL*& tree);
    int height(AVL*& tree);
    void new_height(AVL*& tree);
    void balance(AVL*& tree);
    void left_bal(AVL*& p);
    void right_bal(AVL*& p);
    int sub_height(AVL*& tree);
    void remove(AVL*& tree, int k);
    std::pair<int,int> draw(QGraphicsScene*& scene,AVL*& tree,int label,int root);
    int is_number_in(AVL*&tree,int k);
    AVL* tree = nullptr;
public slots:
    void on_button_clicked();
signals:
    void button_clicked_();
};

#endif // AVL_H
