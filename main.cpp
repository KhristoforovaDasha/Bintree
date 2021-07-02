#include "mainwindow.h"

#include <QApplication>
#include "avl.h"
#include "dekart.h"

//MainWindow w;
int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
     //gen.seed(time(0));
      //AVL_tree avl;
     //avl.init(&scene,&view);
    //w = MainWindow();
     MainWindow w;
    //w.avl = AVL_tree();
    //w.dekart = Dekart_tree();
    //w.redblack = RedBlack_tree();
    //w.twothree = TwoThree_tree();
    for(int i = 0; i < 9; i++) w.avl.insert(i*1000);
    for(int i = 0; i < 9; i++) w.dekart.insert(i*1000);
    for(int i = 0; i < 9; i++) w.redblack.insert(i*1000);
    //for(int i = 7; i < 15; i++) w.redblack.insert(i*1000);
    for(int i = 0; i < 9; i++) w.twothree.insert(i*1000);
    //w.avl.out(w.scene);
     w.show();
     return a.exec();
}
