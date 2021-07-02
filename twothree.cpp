#include "twothree.h"
int sons= 0;
std:: set <int> st3;
void TwoThree_tree::insert(int k)
{
    if(st3.find(k) == st3.end()){
    root = add(root, k);
    st3.insert(k);
    }
    return;
}

void TwoThree_tree::erase(int k)
{
    root = remove(root, k);
    return;
}

void TwoThree_tree::out(QGraphicsScene*& scene)
{
    sons = 0;
    draw(scene,root,0);
    return;
    /*std::queue <TwoThree*> q;
    q.push(root);
    TwoThree* cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (cur != nullptr) {
            if (cur->size == 1) {
                std::cout << cur->key[0] << '\n';
                q.push(cur->first);
                q.push(cur->second);
            }
            else {
                std::cout << cur->key[0] << " " << cur->key[1] << '\n';
                q.push(cur->first);
                q.push(cur->second);
                q.push(cur->third);
            }
        }
    }
    std::cout << '\n';*/
}

TwoThree_tree::~TwoThree_tree()
{
    delete root;
}

TwoThree* TwoThree_tree::add(TwoThree* p, int k) { // вставка ключа k в дерево с корнем p; всегда возвращаем корень дерева, т.к. он может меняться
    if (!p) return new TwoThree(k); // если дерево пусто, то создаем первую 2-3-вершину (корень)

    if (p->is_leaf()) p->insert_to_node(k);
    else if (k <= p->key[0]) add(p->first, k);
    else if ((p->size == 1) || ((p->size == 2) && k <= p->key[1])) add(p->second, k);
    else add(p->third, k);

    return split(p);
}
TwoThree* TwoThree_tree:: split(TwoThree* item) {
    if (item->size < 3) return item;

    TwoThree* x = new TwoThree(item->key[0], item->first, item->second, nullptr, nullptr, item->parent);
    TwoThree* y = new TwoThree(item->key[2], item->third, item->fourth, nullptr, nullptr, item->parent);
    if (x->first)  x->first->parent = x;
    if (x->second) x->second->parent = x;
    if (y->first)  y->first->parent = y;
    if (y->second) y->second->parent = y;

    if (item->parent) {
        item->parent->insert_to_node(item->key[1]);

        if (item->parent->first == item) item->parent->first = nullptr;
        else if (item->parent->second == item) item->parent->second = nullptr;
        else if (item->parent->third == item) item->parent->third = nullptr;

        if (item->parent->first == nullptr) {
            item->parent->fourth = item->parent->third;
            item->parent->third = item->parent->second;
            item->parent->second = y;
            item->parent->first = x;
        }
        else if (item->parent->second == nullptr) {
            item->parent->fourth = item->parent->third;
            item->parent->third = y;
            item->parent->second = x;
        }
        else {
            item->parent->fourth = y;
            item->parent->third = x;
        }

        TwoThree* tmp = item->parent;
        delete item;
        return tmp;
    }
    else {
        x->parent = item;
        y->parent = item;
        item->become_node2(item->key[1], x, y);
        return item;
    }
}
std::pair<int,int> TwoThree_tree::draw(QGraphicsScene*& scene,TwoThree*& tree,int label){
    if(tree == nullptr) return {0,0};
    std::pair<int,int> vertex = draw(scene,tree->first,label+1);
    sons++;
    QString t;
    t = QString::fromStdString(std::to_string(tree->key[0]));
    QPixmap pixmap("D:\\listik.jpg");
    QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
    item->setPos(10 + sons*70,label*100 - 30);
    scene->addEllipse(10 + sons*70,label*100,80,50);
    QPushButton* button = new QPushButton();
    button->move(10 + sons*70,label*100);
    button->setText(t);
    button->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    scene->addWidget(button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(on_button_clicked_TwoThree()));
    /*auto text = scene->addText(t);
    text->setTextWidth(100);
    text->setPos(20 + sons*70,label*100 + 10);*/
    if(tree->first != nullptr) scene->addLine(20 + sons*70,label*100 + 50,vertex.first + 10,vertex.second);
    if(tree->size == 2){
        QPixmap pixmap("D:\\listik.jpg");
        QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
        item->setPos(100 + sons*70,label*100 - 30);
       scene->addEllipse(100 + sons*70,label*100,80,50);
       t = QString::fromStdString(std::to_string(tree->key[1]));
       QPushButton* button2 = new QPushButton();
       button2->move(100 + sons*70,label*100);
       button2->setText(t);
       button2->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
       scene->addWidget(button2);
       QObject::connect(button2,SIGNAL(clicked()),this,SLOT(on_button_clicked_TwoThree()));
       /*auto text = scene->addText(t);
       text->setTextWidth(100);
       text->setPos(110 + sons*70,label*100 + 10);*/
    }
    int copy = sons;
    std:: pair <int,int> node = draw(scene,tree->second,label+1);
    if(tree->second != nullptr) scene->addLine(20 + copy*70,label*100 + 50,node.first,node.second);
    if(tree->size == 2){
        int copy_2 = copy+1;
        sons++;
        std:: pair <int,int> node_2 = draw(scene,tree->third,label+1);
        //sons++;
        if(tree->third != nullptr) scene->addLine(110 + copy_2*70,label*100 + 50,node_2.first,node_2.second);
        return {100 + copy_2*70,label*100};
    }
    else return{10 + copy*70,label*100};
 }
/*{
    //QString t = QString::fromStdString(std::to_string(tree->key[0]));
    scene->addEllipse(10 + sons*70,label*100,80,50);
    QString t;
    if(tree->size == 2){
         t = QString::fromStdString(std::to_string(tree->key[0]) +" " + std::to_string(tree->key[1]));
         scene->addEllipse(10 + sons*70,label*100,80,50);
    }
    else t = QString::fromStdString(std::to_string(tree->key[0]));
    if(tree->first != nullptr) scene->addLine(20 + sons*70,label*100 + 50,vertex.first + 10,vertex.second);
    auto text = scene->addText(t);
    text->setTextWidth(100);
    text->setPos(20 + sons*70,label*100 + 10);
    int copy = sons;
    std:: pair <int,int> node = draw(scene,tree->second,label+1);
    if(tree->second != nullptr) scene->addLine(20 + copy*70,label*100 + 50,node.first,node.second);
    if(tree->size == 2){
        int copy_2 = sons;
        std:: pair <int,int> node_2 = draw(scene,tree->third,label+1);
        if(tree->third != nullptr) scene->addLine(20 + copy_2*70,label*100 + 50,node_2.first,node_2.second);
        return {10 + copy_2*70,label*100};
    }
    else return{10 + copy*70,label*100};
}*/
TwoThree* TwoThree_tree::search_min(TwoThree* tree)
{
    if (!tree) return tree;
    if (tree->first == nullptr)return tree;
    else return search_min(tree->first);
}
TwoThree* TwoThree_tree:: search(TwoThree* tree, int k)
{
    if (!tree) return tree;
    if (tree->find(k)) return tree;
    else if (k < tree->key[0]) return search(tree->first, k);
    else if (tree->size == 1 || (tree->size == 2 && k < tree->key[1])) return search(tree->second, k);
    else if(tree->size == 2) return search(tree->third, k);
}
TwoThree* TwoThree_tree::fix(TwoThree* tree)
{
    if (tree->size == 0 && tree->parent == nullptr) {
        delete tree;
        return nullptr;
    }
    if (tree->size != 0) {
        if (tree->parent) return fix(tree->parent);
        else return tree;
    }
    TwoThree* parent = tree->parent;
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) tree = restibute(tree);
    else if (parent->size == 2 && parent->third->size == 2) tree = restibute(tree);
    else tree = merge(tree);
    return fix(tree);
}
TwoThree* TwoThree_tree::remove(TwoThree* tree, int k)
{
    TwoThree* item = search(tree, k); // Ищем узел, где находится ключ k

        if (!item) return tree;

        TwoThree* min = nullptr;
        if (item->key[0] == k) min = search_min(item->second); // Ищем эквивалентный ключ
        else min = search_min(item->third);

        if (min) { // Меняем ключи местами
            int &z = (k == item->key[0] ? item->key[0] : item->key[1]);
            item->swap(z, min->key[0]);
            item = min; // Перемещаем указатель на лист, т.к. min - всегда лист
        }

        item->remove_from_node(k); // И удаляем требуемый ключ из листа
        return fix(item);
}
TwoThree* TwoThree_tree::restibute(TwoThree* leaf) {
    TwoThree* parent = leaf->parent;
    TwoThree* first = parent->first;
    TwoThree* second = parent->second;
    TwoThree* third = parent->third;
    if (parent->size == 2 && first->size < 2 && second->size < 2 && third->size < 2) {
        if (first == leaf) {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = nullptr;
            parent->first->insert_to_node(parent->key[0]);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first != nullptr) parent->first->first = leaf->first;
            else if (leaf->second != nullptr) parent->first->first = leaf->second;
            if (parent->first->first != nullptr) parent->first->first->parent = parent->first;
            parent->remove_from_node(parent->key[0]);
            delete first;
        }
        else if (second == leaf) {
            first->insert_to_node(parent->key[0]);
            parent->remove_from_node(parent->key[0]);
            if (leaf->first != nullptr) first->third = leaf->first;
            else if (leaf->second != nullptr) first->third = leaf->second;

            if (first->third != nullptr) first->third->parent = first;

            parent->second = parent->third;
            parent->third = nullptr;

            delete second;
        }
        else if (third == leaf) {
            second->insert_to_node(parent->key[1]);
            parent->third = nullptr;
            parent->remove_from_node(parent->key[1]);
            if (leaf->first != nullptr) second->third = leaf->first;
            else if (leaf->second != nullptr) second->third = leaf->second;

            if (second->third != nullptr)  second->third->parent = second;

            delete third;
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->first != nullptr) {
                leaf->second = leaf->first;
                leaf->first = nullptr;
            }

            leaf->insert_to_node(parent->key[1]);
            if (second->size == 2) {
                parent->key[1] = second->key[1];
                second->remove_from_node(second->key[1]);
                leaf->first = second->third;
                second->third = nullptr;
                if (leaf->first != nullptr) leaf->first->parent = leaf;
            }
            else if (first->size == 2) {
                parent->key[1] = second->key[0];
                leaf->first = second->second;
                second->second = second->first;
                if (leaf->first != nullptr) leaf->first->parent = leaf;

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                first->remove_from_node(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr) second->first->parent = second;
                first->third = nullptr;
            }
        }
        else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->first == nullptr) {
                    leaf->first = leaf->second;
                    leaf->second = nullptr;
                }
                second->insert_to_node(parent->key[1]);
                parent->key[1] = third->key[0];
                third->remove_from_node(third->key[0]);
                second->second = third->first;
                if (second->second != nullptr) second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
            else if (first->size == 2) {
                if (leaf->second == nullptr) {
                    leaf->second = leaf->first;
                    leaf->first = nullptr;
                }
                second->insert_to_node(parent->key[0]);
                parent->key[0] = first->key[1];
                first->remove_from_node(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr) second->first->parent = second;
                first->third = nullptr;
            }
        }
        else if (first == leaf) {
            if (leaf->first == nullptr) {
                leaf->first = leaf->second;
                leaf->second = nullptr;
            }
            first->insert_to_node(parent->key[0]);
            if (second->size == 2) {
                parent->key[0] = second->key[0];
                second->remove_from_node(second->key[0]);
                first->second = second->first;
                if (first->second != nullptr) first->second->parent = first;
                second->first = second->second;
                second->second = second->third;
                second->third = nullptr;
            }
            else if (third->size == 2) {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                third->remove_from_node(third->key[0]);
                first->second = second->first;
                if (first->second != nullptr) first->second->parent = first;
                second->first = second->second;
                second->second = third->first;
                if (second->second != nullptr) second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
        }
    }
    else if (parent->size == 1) {
    leaf->insert_to_node(parent->key[0]);

    if (first == leaf && second->size == 2) {
        parent->key[0] = second->key[0];
        second->remove_from_node(second->key[0]);

        if (leaf->first == nullptr) leaf->first = leaf->second;

        leaf->second = second->first;
        second->first = second->second;
        second->second = second->third;
        second->third = nullptr;
        if (leaf->second != nullptr) leaf->second->parent = leaf;
    }
    else if (second == leaf && first->size == 2) {
        parent->key[0] = first->key[1];
        first->remove_from_node(first->key[1]);

        if (leaf->second == nullptr) leaf->second = leaf->first;

        leaf->first = first->third;
        first->third = nullptr;
        if (leaf->first != nullptr) leaf->first->parent = leaf;
    }
    }
    return parent;
}
TwoThree* TwoThree_tree::merge(TwoThree* leaf) {
    TwoThree* parent = leaf->parent;

    if (parent->first == leaf) {
        parent->second->insert_to_node(parent->key[0]);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;

        if (leaf->first != nullptr) parent->second->first = leaf->first;
        else if (leaf->second != nullptr) parent->second->first = leaf->second;

        if (parent->second->first != nullptr) parent->second->first->parent = parent->second;

        parent->remove_from_node(parent->key[0]);
        delete parent->first;
        parent->first = nullptr;
    }
    else if (parent->second == leaf) {
        parent->first->insert_to_node(parent->key[0]);

        if (leaf->first != nullptr) parent->first->third = leaf->first;
        else if (leaf->second != nullptr) parent->first->third = leaf->second;

        if (parent->first->third != nullptr) parent->first->third->parent = parent->first;

        parent->remove_from_node(parent->key[0]);
        delete parent->second;
        parent->second = nullptr;
    }

    if (parent->parent == nullptr) {
        TwoThree* tmp = nullptr;
        if (parent->first != nullptr) tmp = parent->first;
        else tmp = parent->second;
        tmp->parent = nullptr;
        delete parent;
        return tmp;
    }
    return parent;
}
void TwoThree_tree::on_button_clicked_TwoThree(){
    key = (dynamic_cast<QPushButton*>(sender())->text()).toInt();
    emit button_clicked_();
}
