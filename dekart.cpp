#include "dekart.h"
#include "ellipse.h"
int son;
std:: set <int> st1;
Dekart_tree:: ~Dekart_tree() { delete tree; }
void  Dekart_tree:: split(Dekart* tree, int key, Dekart*& l, Dekart*& r) {
    if (tree == nullptr) {
        l = r = nullptr;
    }
    else if (key < tree->val) {
        split(tree->left, key, l, tree->left);
        r = tree;
    }
    else {
        split(tree->right, key, tree->right, r);
        l = tree;
    }
}
void Dekart_tree:: merge(Dekart*& tree, Dekart* l, Dekart* r) {
    if (l == nullptr) tree = r;
    else if (r == nullptr) tree = l;
    else if (l->prior > r->prior) {
        merge(l->right, l->right, r);
        tree = l;
    }
    else {
        merge(r->left, l, r->left);
        tree = r;
    }
}
void Dekart_tree::insert(int k) {
    if(st1.find(k) == st1.end()){
         add(tree, k);
         st1.insert(k);
    }
    return;
}
void Dekart_tree::erase(int k) {
    remove(tree, k);
    return;
}
void Dekart_tree::add(Dekart*& tree, int k) {
    Dekart* l;
    Dekart* r;
    split(tree, k, l, r);
    Dekart* m = new Dekart(k);
    merge(l, l, m);
    merge(tree, l, r);
}
void Dekart_tree::remove(Dekart*& tree, int k) {
    if (tree->val == k) {
        merge(tree, tree->left, tree->right);
    }
    else {
        if (tree->val > k) remove(tree->left, k);
        else remove(tree->right, k);
    }
}
int count = 0;
std:: map <int,int> mp;
std::pair<int,int> Dekart_tree::draw(QGraphicsScene*& scene,Dekart*& tree,int label){
    if(tree == nullptr) return {0,0};
    std::pair<int,int> vertex = draw(scene,tree->left,label+1);
    son++;
    QString t = QString::fromStdString(std::to_string(tree->val));
    QPixmap pixmap("D:\\listik.jpg");
    QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
    item->setPos(10 + son*70,label*100 - 30);
    QPushButton* button = new QPushButton();
    button->move(15 + son*70,label*100);
    button->setText(t);
    button->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    scene->addWidget(button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(on_button_clicked_dekart()));
    //count++;
   // QPushButton* button = new QPushButton();
    //button->move(10 + son*70,label*100);
    //button->setText(QString:: fromStdString(std::to_string(tree->val)));
    //QString st = button->text();
    //connect(button, SIGNAL (released()), this, SLOT (on_button_clicked()));
    //scene->addWidget(button);
   // mp.insert({count,tree->val});
    //ellipse* Ellipse;
    //Ellipse->text = t;
    //Ellipse->setRect(10 + son*70,label*100,80,50);
    scene->addEllipse(10 + son*70,label*100,80,50);
   // scene->addItem(Ellipse);
    //x = 10 + left_son*70;
    //y = label*100;
    if(tree->left != nullptr) scene->addLine(20 + son*70,label*100 + 50,vertex.first + 10,vertex.second);
    //if(tree->right != nullptr) scene->addLine(x,y,40+left_son*70,label*100+50);
    /*auto text = scene->addText(t);
    text->setTextWidth(100);
    text->setPos(20 + son*70,label*100 + 10);*/
    //return{10 + left_son*70,label*100};
    int copy = son;
    std:: pair <int,int> node = draw(scene,tree->right,label+1);
    if(tree->right != nullptr) scene->addLine(20 + copy*70,label*100 + 50,node.first,node.second);
    return{10 + copy*70,label*100};
}
void Dekart_tree::out(QGraphicsScene*& scene) {
    son = 0;
    draw(scene,tree,0);
    return;
    /*std::queue <Dekart*> q;
    q.push(tree);
    Dekart* cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (cur != nullptr) {
            std::cout << cur->val << " " << cur->prior << '\n';
            q.push(cur->left);
            q.push(cur->right);
        }
    }
    std::cout << '\n';*/
}
void Dekart_tree:: on_button_clicked_dekart(){
    key = (dynamic_cast<QPushButton*>(sender())->text()).toInt();
    emit button_clicked_();
}
