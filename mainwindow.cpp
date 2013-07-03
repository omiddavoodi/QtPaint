#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(400,300);

    sdrawtable = new myDrawWidget();
    this->setCentralWidget(sdrawtable);

    color_selection = new QDockWidget();
    colorselector = new ColorSelector*[16];
    colorpixmap = new QPixmap[16];
    color = new QColor[16];
    color[0].setRgb(0,0,0);
    color[1].setRgb(255,255,255);
    color[2].setRgb(255,0,0);
    color[3].setRgb(0,255,0);
    color[4].setRgb(0,0,255);
    color[5].setRgb(255,255,0);
    color[6].setRgb(0,255,255);
    color[7].setRgb(255,0,255);
    color[8].setRgb(127,127,127);
    color[9].setRgb(200,200,200);
    color[10].setRgb(127,0,0);
    color[11].setRgb(0,127,0);
    color[12].setRgb(0,0,127);
    color[13].setRgb(127,127,0);
    color[14].setRgb(0,127,127);
    color[15].setRgb(127,0,127);
    for (int i = 0; i < 16; ++i)
    {
        colorpixmap[i] = QPixmap(20,20);
        colorpixmap[i].fill(color[i]);
        colorselector[i] = new ColorSelector();
        colorselector[i]->setPixmap(colorpixmap[i]);
        colorselector[i]->setParent(color_selection);
        colorselector[i]->setGeometry(2 + 20 * (i/8),22 + (i%8)*20,20,20);
        colorselector[i]->index = i;
        connect(colorselector[i], SIGNAL(pressed(int)),this,SLOT(changeColor(int)));
    }
    this->addDockWidget(Qt::LeftDockWidgetArea, color_selection);

}

void MainWindow::changeColor(int i)
{
    this->sdrawtable->changePen(QPen(color[i]));
}

MainWindow::~MainWindow()
{

}
