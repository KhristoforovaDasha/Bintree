#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avl.h"
#include "dekart.h"
#include "redblack.h"
int ind = 1;
int flag = 0;
double val = 1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,dekart()
    ,redblack()
    ,avl()
    ,twothree()
{
    ui->setupUi(this);
   // QImage image("D:\\image.jpg");
    view = new QGraphicsView(this);
    scene = new QGraphicsScene();
    //scene->addPixmap(QPixmap::fromImage(image));
    //this->setScene(scene);
    //button = new QPushButton();
    view->setGeometry(QRect(0,0,700,600));
    view->setScene(scene);
    ui->slider->setMaximum(200);
    ui->slider->setValue(50);
   // QObject::connect(this, SIGNAL (button_update()), this, SLOT (on_comboBox_currentIndexChanged(int)));
    //QObject::connect(&redblack, SIGNAL (button_clicked_()), this, SLOT (on_comboBox_currentIndexChanged(int index)));
    //QObject::connect(&avl, SIGNAL (button_clicked_()), this, SLOT (on_comboBox_currentIndexChanged(int index)));
    QObject::connect(&dekart, SIGNAL (button_clicked_()), this, SLOT (on_button_on()));
    QObject::connect(&redblack, SIGNAL (button_clicked_()), this, SLOT (on_button_on()));
    QObject::connect(&avl, SIGNAL (button_clicked_()), this, SLOT (on_button_on()));
    QObject::connect(&twothree, SIGNAL (button_clicked_()), this, SLOT (on_button_on()));
    //QObject::connect(&dekart, SIGNAL (button_clicked(k)), this, SLOT (on_button_on(k)));
    //dekart = new Dekart_tree();
    //connect(button, SIGNAL (released()), this, SLOT (on_button_clicked()));
   // sl = new QSlider(this);
    //sl->setMaximum(100);
   // sl->setMinimum(50);
   // sl->setOrientation(Qt::Horizontal);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_clicked()
{
    std:: string str;
    bool ok;
   str = QInputDialog::getText(0,QString::fromUtf8("Input"),QString::fromStdString("Enter a number"),QLineEdit::Normal,"",&ok).toStdString();
   int ver = atoi(str.c_str());
   avl.insert(ver);
   dekart.insert(ver);
   redblack.insert(ver);
   twothree.insert(ver);
   scene->clear();
   scene->update();
   QPixmap pixmap("D:\\my_flower.jpg");
   QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
   item->setPos(0,0);
   if(ind == 1) avl.out(scene);
   else if(ind == 2) redblack.out(scene);
   else if(ind == 3) dekart.out(scene);
   else twothree.out(scene);
}

void MainWindow::on_add_range_clicked()
{
   std:: string str;
   bool ok;
   str = QInputDialog::getText(0,QString::fromUtf8("Input"),QString::fromStdString("How many numbers?"),QLineEdit::Normal,"",&ok).toStdString();
   int ver = atoi(str.c_str());
   for(int i = 0; i < ver; i++){
       int k = rand();
       avl.insert(k);
       dekart.insert(k);
       redblack.insert(k);
       twothree.insert(k);
   }
   scene->clear();
   scene->update();
   if(ind == 1) avl.out(scene);
   else if(ind == 2) redblack.out(scene);
   else if(ind == 3) dekart.out(scene);
   else twothree.out(scene);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    std::cout << "aaaaaa";
    scene->clear();
    scene->update();
    if(index == 1){
      avl.out(scene);
      ind = 1;
    } else if(index ==2){
      redblack.out(scene);
      ind = 2;
    } else if(index == 3){
        ind = 3;
        dekart.out(scene);
    } else{
       ind = 4;
       twothree.out(scene);
    }
}

void MainWindow::on_slider_valueChanged(int value)
{
    if(val == 0) return;
    view->scale(1.0/val,1.0/val);
    val = 50.0/value;
    if(value == 0) return;
    view->scale(50.0 / value, 50.0 / value);
}
void MainWindow::clear(){
    scene->clear();
}
void MainWindow::on_button_on(){
    int kk = 0;
    if(ind == 1) kk = (dynamic_cast<AVL_tree*>(sender()))->key;
    else if(ind == 2) kk = (dynamic_cast<RedBlack_tree*>(sender()))->key;
    else if(ind == 3) kk = (dynamic_cast<Dekart_tree*>(sender()))->key;
    else if(ind == 4) kk = (dynamic_cast<TwoThree_tree*>(sender()))->key;
    dekart.erase(kk);
    avl.erase(kk);
    redblack.erase(kk);
    twothree.erase(kk);
    flag = 1;
}
/*void MainWindow::on_button_clicked(){
    int k = (button->text()).toInt();
    dekart.erase(k);
    avl.erase(k);
    redblack.erase(k);
    scene->clear();
    if(ind == 1){
      avl.out(scene);
    } else if(ind ==2){
      redblack.out(scene);
    } else if(ind== 3){
        dekart.out(scene);
    } else{
       twothree.out(scene);
    }
}*/
/*void ellipse::mousePressEvent(QMouseEvent* event) {

    int k = text.toInt();
    window->dekart.erase(k);
    window->scene->clear();
    window->dekart.out(window->scene);
}*/
//void MainWindow::on

void MainWindow::on_on_button_on_clicked()
{
    if(flag){
    scene->clear();
    scene->update();
    if(ind== 1){
      avl.out(scene);
    } else if(ind ==2){
      redblack.out(scene);
    } else if(ind == 3){
        dekart.out(scene);
    } else{
       twothree.out(scene);
    }
    }
    flag = 0;
}
