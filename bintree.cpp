#include "bintree.h"
bintree::bintree()
{

}
/*std::pair<int,int> bintree::draw(QGraphicsScene*& scene,Tree*& tree,int label,int root){
    if(tree == nullptr) return {0,0};
    std::pair<int,int> vertex = draw(scene,tree->left,label+1,root);
    left_son++;
    QString t = QString::fromStdString(std::to_string(tree->val));
    scene->addEllipse(10 + left_son*70,label*100,80,50);
    //x = 10 + left_son*70;
    //y = label*100;
    if(tree->left != nullptr) scene->addLine(20 + left_son*70,label*100 + 50,vertex.first + 10,vertex.second);
    //if(tree->right != nullptr) scene->addLine(x,y,40+left_son*70,label*100+50);
    auto text = scene->addText(t);
    text->setTextWidth(100);
    text->setPos(20 + left_son*70,label*100 + 10);
    //return{10 + left_son*70,label*100};
    int copy = left_son;
    std:: pair <int,int> node = draw(scene,tree->right,label+1,root);
    if(tree->right != nullptr) scene->addLine(20 + copy*70,label*100 + 50,node.first,node.second);
    return{10 + copy*70,label*100};
}*/
