#ifndef TWOTHREE_H
#define TWOTHREE_H
#include "Tree.h"
struct TwoThree {
    int size;
    int key[3];
    TwoThree* first;
    TwoThree* second;
    TwoThree* third;
    TwoThree* fourth;
    TwoThree* parent;
    QPushButton* button;
    bool find(int k) {
        for (int i = 0; i < size; ++i)
            if (key[i] == k) return true;
        return false;
    }

    void swap(int& x, int& y) {
        int r = x;
        x = y;
        y = r;
    }

    void sort2(int& x, int& y) {
        if (x > y) swap(x, y);
    }

    void sort3(int& x, int& y, int& z) {
        if (x > y) swap(x, y);
        if (x > z) swap(x, z);
        if (y > z) swap(y, z);
    }

    void sort() { // Ключи в вершинах должны быть отсортированы
        if (size == 1) return;
        if (size == 2) sort2(key[0], key[1]);
        if (size == 3) sort3(key[0], key[1], key[2]);
    }

    void insert_to_node(int k) {
        key[size] = k;
        size++;
        sort();
    }

    void remove_from_node(int k) {
        if (size >= 1 && key[0] == k) {
            key[0] = key[1];
            key[1] = key[2];
            size--;
        }
        else if (size == 2 && key[1] == k) {
            key[1] = key[2];
            size--;
        }
    }

    void become_node2(int k, TwoThree* first_, TwoThree* second_) {
        key[0] = k;
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
    }

    bool is_leaf() {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
    }
    TwoThree(int k) : size(1), key{ k, 0, 0 }, first(nullptr), second(nullptr),
        third(nullptr), fourth(nullptr), parent(nullptr) {}

    TwoThree(int k, TwoThree* first_, TwoThree* second_, TwoThree* third_, TwoThree* fourth_, TwoThree* parent_) :
        size(1), key{ k, 0, 0 }, first(first_), second(second_),
        third(third_), fourth(fourth_), parent(parent_) {}
};

class TwoThree_tree :public QObject {
    Q_OBJECT
public:
    void insert(int k);
    void erase(int k);
    void out(QGraphicsScene*& scene);
    int key;
    virtual ~TwoThree_tree();
private:
    TwoThree* root;
    TwoThree* add(TwoThree* tree, int k);
    TwoThree* remove(TwoThree* tree, int k);
    TwoThree* split(TwoThree* tree);
    std::pair<int,int> draw(QGraphicsScene*& scene,TwoThree*& tree,int label);
    TwoThree* search_min(TwoThree* tree);
    TwoThree* search(TwoThree* tree, int k);
    TwoThree* fix(TwoThree* tree);
    TwoThree* restibute(TwoThree* leaf);
    TwoThree* merge(TwoThree* leaf);
public slots:
    void on_button_clicked_TwoThree();
signals:
    void button_clicked_();
};

#endif // TWOTHREE_H
