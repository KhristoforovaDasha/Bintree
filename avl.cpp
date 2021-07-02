#include "avl.h"
#include <QDebug>
std:: set <int> st;
int left_son;
double x = 50,y = 700;
void AVL_tree::insert(int k) {
    //if(!(is_number_in(tree,k)))
    if(st.find(k) == st.end()){
        add(tree, k);
        st.insert(k);
    }
    return;
}
int is_number_in(AVL*&tree,int k){
    if(tree == nullptr) return 0;
    if(tree->val < k) return is_number_in(tree->right,k);
    else if(tree->val > k) return is_number_in(tree->left,k);
    else return 1;
}
void AVL_tree::add(AVL*& tree, int k) {
    if (tree == nullptr) {
        tree = new AVL(k);
        //QObject::connect(tree, SIGNAL (clicked()), this, SLOT (on_button_clicked(k)));
        return;
    }
    if (k < tree->val) add(tree->left, k);
    else add(tree->right, k);
    balance(tree);
    return;
}
int AVL_tree::height(AVL*& tree) {
    return tree ? tree->height : 0;
}
void AVL_tree :: new_height(AVL*& tree) {
    int hl = height(tree->left);
    int hr = height(tree->right);
    tree->height = std::max(hl, hr) + 1;
}
void AVL_tree:: balance(AVL*& tree) {
    new_height(tree);
    if (sub_height(tree) == 2) {
        if (sub_height(tree->right) < 0) {
            right_bal(tree->right);
        }
        left_bal(tree);
    }
    if (sub_height(tree) == -2) {
        if (sub_height(tree->left) > 0) {
            left_bal(tree->left);
        }
        right_bal(tree);
    }
}
int AVL_tree:: sub_height(AVL*& tree) {
    return height(tree->right) - height(tree->left);
}
void AVL_tree:: right_bal(AVL*& p) {
    AVL* q = p->left;
    p->left = q->right;
    q->right = p;
    new_height(p);
    new_height(q);
    p = q;
}
void AVL_tree:: left_bal(AVL*& p) {
    AVL* q = p->right;
    p->right = q->left;
    q->left = p;
    new_height(p);
    new_height(q);
    p = q;
}
AVL_tree::~AVL_tree() { delete tree; }
void AVL_tree::erase(int k) {
    remove(tree, k);
    return;
}
void AVL_tree::remove(AVL*& tree, int k) {
    if (tree == nullptr) return;
    if (k < tree->val) remove(tree->left, k);
    else if (k > tree->val) remove(tree->right, k);
    else {
        AVL* l = tree->left;
        AVL* r = tree->right;
        if (r == nullptr) {
            AVL* p = tree;
            tree = tree->left;
            delete p;
            return;
        }
        tree->val = findmin(tree->right);
        balance(tree);
        return;
    }
    balance(tree);
}
int AVL_tree:: findmin(AVL *& tree) {
    if (tree->left == nullptr) {
        int value = tree->val;
        tree = tree->right;
        return value;
    }
    return findmin(tree->left);
}
std::pair<int,int> AVL_tree::draw(QGraphicsScene*& scene,AVL*& tree,int label,int root){
    if(tree == nullptr) return {0,0};
    std::pair<int,int> vertex = draw(scene,tree->left,label+1,root);
    left_son++;
    QPixmap pixmap1("D:\\my_flower.jpg");
    QGraphicsPixmapItem *item1 = scene->addPixmap(pixmap1);
    item1->setPos(10 + left_son*70,label*100);
    QString t = QString::fromStdString(std::to_string(tree->val));
    /*QPixmap pixmap("D:\\listik.jpg");
    QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
    item->setPos( left_son*70-20,label*100);*/
    scene->addEllipse(10 + left_son*70,label*100,80,50);
    QPushButton* button = new QPushButton();
    QFont font(t);
    font.setStyleName("times");
    font.setBold(3);
    button->move(15 + left_son*70,label*100);
    button->setText(t);
    button->setFont(font);
    button->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    scene->addWidget(button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(on_button_clicked()));
    //x = 10 + left_son*70;
    //y = label*100;
    if(tree->left != nullptr) scene->addLine(20 + left_son*70,label*100 + 50,vertex.first + 10,vertex.second);
    //if(tree->right != nullptr) scene->addLine(x,y,40+left_son*70,label*100+50);
    /*auto text = scene->addText(t);
    text->setTextWidth(100);
    text->setPos(20 + left_son*70,label*100 + 10);*/
    //return{10 + left_son*70,label*100};
    int copy = left_son;
    std:: pair <int,int> node = draw(scene,tree->right,label+1,root);
    if(tree->right != nullptr) scene->addLine(20 + copy*70,label*100 + 50,node.first,node.second);
    return{10 + copy*70,label*100};
}
void AVL_tree:: out(QGraphicsScene*& scene) {
    int root_height = tree->height;
    left_son = 0;
    draw(scene,tree,0,root_height);
    return;
    /*std::queue <AVL*> q;
    q.push(tree);
    AVL* cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (cur != nullptr) {
            std::cout << cur->val << " " << cur->height << '\n';
            QString t = QString::fromStdString(std::to_string(cur->val));
            scene->addEllipse(10,10,100,50);
            auto text = scene->addText(t);
            text->setTextWidth(100);
            text->setPos(50,50);
            q.push(cur->left);
            q.push(cur->right);
        }
    }
    std::cout << '\n';*/
    //if(tree == nullptr) return;

}
/*void AVL:: button_pushed(int k){

}
void AVL:: on_button_clicked(){
    emit button_pushed(val);
}*/

void AVL_tree:: on_button_clicked(){
    key = (dynamic_cast<QPushButton*>(sender())->text()).toInt();
    qDebug() << key;
    emit button_clicked_();
}
