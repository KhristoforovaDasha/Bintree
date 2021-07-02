#include "redblack.h"
int sson = 0;
std:: set <int> st2;
void RedBlack_tree::insert(int k) {
    if(st2.find(k) == st2.end()){
    add(root, k);
    st2.insert(k);
    }
    return;
}
void RedBlack_tree::add(RedBlack*& tree,int k) {
    if (tree == nullptr) {
        tree = new RedBlack(k);
        balance(tree);
        return;
    }
    if (tree->left == nullptr && tree->val > k) {
        tree->left = new RedBlack(k);
        tree->left->parent = tree;
        balance(tree->left);
        return;
    }
    if (tree->right == nullptr && tree->val < k) {
        tree->right = new RedBlack(k);
        tree->right->parent = tree;
        balance(tree->right);
        return;
    }
    if (tree->val > k) {
        add(tree->left, k);
        //if(tree->left) tree->left->parent = tree;
    }
    else {
        add(tree->right, k);
        //if(tree->right) tree->right->parent = tree;
    }
    //balance(tree);
}
void RedBlack_tree::balance(RedBlack*& tree)
{
    std::cout << "balance" << '\n';
    if (tree == nullptr) {
        std::cout << 0 << '\n';
        return;
    }
    RedBlack* par = tree->parent;
    if (par == nullptr) {
        std::cout << 1 << '\n';
        setColor(tree, BLACK);
        return;
    }
    if (getColor(par) == BLACK) return;
    RedBlack* grand = tree->parent->parent;
    if (getColor(grand->left) == RED && getColor(grand->right)== RED) {
        std::cout << 2 << '\n';
            setColor(grand, RED);
            setColor(grand->left, BLACK);
            setColor(grand->right, BLACK);
            balance(grand);
    }
    else {
        std::cout << 3 << '\n';
        if (grand->left == par) {
            if (par->right == tree) rotate_left(par);
            setColor(grand, RED);
            setColor(grand->left, BLACK);
             rotate_right(grand);
        }
        else {
            std::cout << 4 << '\n';
            if (par->left == tree) {
                std:: cout << 5 << " ";
                rotate_right(par);
            }
            setColor(grand,RED);
            setColor(grand->right, BLACK);
            rotate_left(grand);
        }
    }
}
/*void RedBlack_tree::remove(RedBlack*& tree, int k)
{
    if (tree->val < k) remove(tree->right, k);
    else if (tree->val > k) remove(tree->left, k);
    else {
        if (tree->left == nullptr) {
            return;
        }
        tree->val = findmax(tree->left);
    }
}
int RedBlack_tree::findmax(RedBlack*& tree)
{
    if (tree->right == nullptr) {
        int value = tree->val;
        balance_erase(tree);
        tree->parent->right = nullptr;
        delete tree;
        return value;
    }
    else return findmax(tree->right);
}
void RedBlack_tree::balance_erase(RedBlack*& tree)
{
    if (getColor(tree) == RED) return;
    else {
        if (getColor(tree->left) == RED) {
            tree->parent->left = tree->left;
            tree->left->parent = tree->parent;
            setColor(tree->left, BLACK);
            return;
        }
        else {
            RedBlack* uncle = tree->parent->left;
            RedBlack* uncle_left = uncle->left;
            RedBlack* uncle_right = uncle->right;
            if (getColor(uncle) == BLACK) {
                if (getColor(uncle_left) == BLACK && getColor(uncle_right) == BLACK) {
                    if (getColor(tree->parent) == BLACK) {
                        setColor(uncle, RED);
                        balance_erase(tree->parent);
                    }
                    else {
                        setColor(uncle, RED);
                        setColor(tree->parent, BLACK);
                        return;
                    }
                }
                else {
                    if (getColor(uncle_right) == BLACK) {
                        setColor(uncle_left, BLACK);
                        setColor(uncle, RED);
                        rotate_left(uncle);
                    }
                    setColor(tree->parent->left, getColor(tree->parent));
                    setColor(tree->parent, BLACK);
                    setColor(tree->parent->left->left, BLACK);
                    rotate_right(tree->parent);
                }
            }
            else {
                setColor(uncle, BLACK);
                setColor(uncle->right, RED);
                rotate_right(tree->parent);
            }
        }
    }
}
void RedBlack_tree::erase(int k) {
    remove(root, k);
}*/
std::pair<int,int> RedBlack_tree::draw(QGraphicsScene*& scene,RedBlack*& tree,int label){
    if(tree == nullptr) return {0,0};
    std::pair<int,int> vertex = draw(scene,tree->left,label+1);
    sson++;
    QString t = QString::fromStdString(std::to_string(tree->val));
    QPixmap pixmap("D:\\listik.jpg");
    QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
    item->setPos(10 + sson*70,label*100 - 30);
    QPushButton* button = new QPushButton();
    QPen pen;
    QColor color = {0,0,0};
    pen.setColor(color);
    if(getColor(tree) == RED) scene->addEllipse(10 + sson*70,label*100,80,50,pen,QBrush(Qt::red));
    else scene->addEllipse(10 + sson*70,label*100,80,50,pen,QBrush(Qt::blue));
    button->move(10 + sson*70,label*100);
    button->setText(t);
    button->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    scene->addWidget(button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(on_button_clicked_RBT()));
    //x = 10 + left_son*70;
    //y = label*100;
    if(tree->left != nullptr) scene->addLine(20 + sson*70,label*100 + 50,vertex.first + 10,vertex.second);
    //if(tree->right != nullptr) scene->addLine(x,y,40+left_son*70,label*100+50);
   // QPainter pd;
    //pd.setBrush(Qt::white);
    /*QFont font("Times", 10, QFont::Bold);
    //font.setWeight(2);
    auto text = scene->addText(t,font);
    text->setTextWidth(100);
    text->setPos(20 + sson*70,label*100 + 10);*/
    //return{10 + left_son*70,label*100};
    int copy = sson;
    std:: pair <int,int> node = draw(scene,tree->right,label+1);
    if(tree->right != nullptr) scene->addLine(20 + copy*70,label*100 + 50,node.first,node.second);
    return{10 + copy*70,label*100};
}
void RedBlack_tree::out(QGraphicsScene*& scene)
{
    sson = 0;
    draw(scene,root,0);
    return;
   /* std::queue <RedBlack*> q;
    q.push(root);
    RedBlack* cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (cur != nullptr) {
            std::cout << cur->val << " " << cur->color << '\n';
            q.push(cur->left);
            q.push(cur->right);
        }
    }
    std::cout << '\n';*/
}
void RedBlack_tree::parents()
{
    std::cout << root->right->parent;
}
RedBlack_tree::~RedBlack_tree() { delete root; }

void RedBlack_tree::rotate_left(RedBlack*& tree)
{
    RedBlack* node = tree->right;
    tree->right = node->left;
    if(node->left) node->left->parent  = tree;
    if (node) node->parent = tree->parent;
    if (tree->parent) {
        if (tree == tree->parent->right) tree->parent->right = node;
        else tree->parent->left = node;
    }
    else root = node;
    node->left = tree;
    tree->parent = node;
    //setColor(tree, RED);
    //setColor(node, BLACK);
    //tree = node;
    return;
}

void RedBlack_tree::rotate_right(RedBlack*& tree)
{
    RedBlack* node = tree->left;
    tree->left = node->right;
   if(node->right) node->right->parent = tree;
   if (node) node->parent = tree->parent;
   if (tree->parent) {
       if (tree == tree->parent->right) tree->parent->right = node;
       else tree->parent->left = node;
   }
   else root = node;
    node->right = tree;
    tree->parent = node;
    //setColor(tree, RED);
    //setColor(node, BLACK);
    //tree = node;
    return;
}

int RedBlack_tree::getColor(RedBlack*& tree)
{
    if (tree == nullptr) return BLACK;
    return tree->color;
}

void RedBlack_tree::setColor(RedBlack*& tree,int color)
{
    if (tree == nullptr) return;
    tree->color = color;
}
void RedBlack_tree::erase(int k) {
    remove(root, k);
}
void RedBlack_tree::remove(RedBlack*& tree, int k) {
    if (tree->val > k) remove(tree->left, k);
    else if (tree->val < k) remove(tree->right, k);
    else {
        if (tree->right == nullptr && tree->left == nullptr) {
            if (tree->parent == nullptr) {
                tree = nullptr;
                return;
            }
            RedBlack* parent = tree->parent;
            int flag = 0, color = getColor(tree);
            if (tree->parent->right == tree) {
                flag = 1;
                tree->parent->right = nullptr;
                parent->right = nullptr;
            }
            else {
                tree->parent->left = nullptr;
                parent->left = nullptr;
            }
            delete tree;
            if (color == BLACK) {
                if (flag) balance_right(parent);
                else balance_left(parent);
            }
        }
        else if (tree->right == nullptr || tree->left == nullptr) {
            if (tree->parent == nullptr) {
                if (tree->right) {
                    //setColor(tree->right, BLACK);
                    tree->val = tree->right->val;
                     tree->right = nullptr;
                }
                else {
                    tree->val = tree->left->val;
                    tree->left = nullptr;
                }
                return;
            }
            if (tree->right == nullptr) {
                setColor(tree->left, BLACK);
                tree->left->parent = tree->parent;
                if (tree->parent->right == tree) {
                    tree->parent->right = tree->left;
                }
                else tree->parent->left = tree->left;
                //tree->left->parent = tree->parent;
            }
            else {
                setColor(tree->right, BLACK);
                tree->right->parent = tree->parent;
                if (tree->parent->right == tree) {
                    tree->parent->right = tree->right;
                }
                else tree->parent->left = tree->right;
                //tree->right->parent = tree->parent;
            }
            //delete tree;
        }
       /* else if (tree->left->right == nullptr) {
            if (tree->left->left == nullptr) {
                tree->val = tree->left->val;
                int color = getColor(tree->left);
                //tree->left = tree->left->left;
                tree->left == nullptr;
                delete tree->left;
                //tree->left = nullptr;
                if (color == BLACK) balance_left(tree);
            }
            else {
                tree->val = tree->left->val;
                setColor(tree->left->left,BLACK);
                tree->left = tree->left->left;
                tree->left->left->parent = tree;
                delete tree->left;
            }
        }*/
        else {
            tree->val = find(tree->left);
             findmax(tree->left);
        }
    }
}
int RedBlack_tree::find(RedBlack*& tree) {
    if (tree->right == nullptr) return tree->val;
    return find(tree->right);
}
void RedBlack_tree::findmax(RedBlack*& tree)
{
    if (tree->right == nullptr) {
        //value = tree->val;
        if (tree->left == nullptr) {
            int color = getColor(tree);
            RedBlack* parent = tree->parent;
            int flag = 0;
            if (tree->parent->right == tree) {
                tree->parent->right = nullptr;
                parent->right = nullptr;
                flag = 1;
            }
            else {
                tree->parent->left = nullptr;
                parent->left = nullptr;
            }
            delete tree;
            if(color == BLACK){
                if (flag)balance_right(parent);
                else balance_left(parent);
            }
        }
        else {
            /*tree->parent->right = tree->left;
            tree->left->parent = tree->parent;
            setColor(tree->left, BLACK);
            //delete tree;*/
            //RedBlack* parent = tree->parent;
            setColor(tree->left, BLACK);
            tree->left->parent = tree->parent;
            if (tree->parent->right == tree) {
                tree->parent->right = tree->left;
            }
            else tree->parent->left = tree->left;
            //tree->left->parent = parent;
            //setColor(tree->left, BLACK);
            /*tree->val = tree->left->val;
           // tree->left == nullptr;
            delete tree->left;*/
        }
        //return value;
    }
    else {
        findmax(tree->right);
    }
}

void RedBlack_tree::balance_right(RedBlack*& tree)
{
    RedBlack* uncle = tree->left;
    if (getColor(uncle) == RED) {
        setColor(uncle, BLACK);
        setColor(uncle->right, RED);
        rotate_right(tree);
    }
    else {
        RedBlack* uncle_right = tree->left->right;
        RedBlack* uncle_left = tree->left->left;
        if (getColor(uncle_right) == BLACK && getColor(uncle_left) == BLACK) {
            if (getColor(tree) == RED) {
                setColor(tree, BLACK);
                setColor(uncle, RED);
            }
            else {
                setColor(uncle, RED);
                if (tree->parent) {
                    if (tree->parent->right == tree) balance_right(tree->parent);
                    else balance_left(tree->parent);
                }
                else return;
            }
        }
        else {
            if (getColor(uncle_left) == BLACK) {
                setColor(uncle, RED);
                setColor(uncle_right, BLACK);
                rotate_left(uncle);
            }
            setColor(tree->left->left, BLACK);
            setColor(tree->left, getColor(tree));
            setColor(tree, BLACK);
            rotate_right(tree);
        }
    }
}

void RedBlack_tree::balance_left(RedBlack*& tree)
{
    RedBlack* uncle = tree->right;
    if (getColor(uncle) == RED) {
        setColor(uncle, BLACK);
        setColor(uncle->left, RED);
        rotate_left(tree);
    }
    else {
        RedBlack* uncle_right = tree->right->right;
        RedBlack* uncle_left = tree->right->left;
        if (getColor(uncle_right) == BLACK && getColor(uncle_left) == BLACK) {
            if (getColor(tree) == RED) {
                setColor(tree, BLACK);
                setColor(uncle, RED);
            }
            else {
                setColor(uncle, RED);
                if (tree->parent) {
                    if (tree->parent->right == tree) balance_right(tree->parent);
                    else balance_left(tree->parent);
                }
                else return;
            }
        }
        else {
            if (getColor(uncle_right) == BLACK) {
                setColor(uncle, RED);
                setColor(uncle_left, BLACK);
                rotate_right(uncle);
            }
            setColor(tree->right->right, BLACK);
            setColor(tree->right, getColor(tree));
            setColor(tree, BLACK);
            rotate_left(tree);
        }
    }
}
void RedBlack_tree:: on_button_clicked_RBT(){
    key = (dynamic_cast<QPushButton*>(sender())->text()).toInt();
    emit button_clicked_();
}
