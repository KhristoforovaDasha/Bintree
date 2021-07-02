#ifndef REDBLACK_H
#define REDBLACK_H
#include "Tree.h"
enum Color {RED, BLACK};
struct RedBlack {
    int val;
    RedBlack* left;
    RedBlack* right;
    RedBlack* parent;
    QPushButton* button;
    int color;
    RedBlack() { left = right = parent = nullptr; }
    RedBlack (int k) { val = k, left = right =parent = nullptr, color = RED; }
};
class RedBlack_tree : public QObject {
    Q_OBJECT
public:
    void insert(int k);
    void erase(int k);
    void out(QGraphicsScene*& scene);
    void parents();
    virtual ~RedBlack_tree();
    int key;
private:
    void rotate_left(RedBlack*& tree);
    void rotate_right(RedBlack*& tree);
    int getColor(RedBlack*& tree);
    void setColor(RedBlack*& tree,int color);
    void add(RedBlack*& tree, int k);
    void balance(RedBlack*& tree);
    void remove(RedBlack*& tree, int k);
    void findmax(RedBlack*& tree);
    void balance_erase(RedBlack*& tree);
    void balance_left(RedBlack*& tree);
    void balance_right(RedBlack*& tree);
    int find(RedBlack*& tree);
    std::pair<int,int> draw(QGraphicsScene*& scene,RedBlack*& tree,int label);
    RedBlack* root;
public slots:
    void on_button_clicked_RBT();
signals:
    void button_clicked_();
};
#endif // REDBLACK_H
