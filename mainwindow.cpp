#include "mainwindow.h"
#include "resizedialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(400,300);

    sdrawtable = new myDrawWidget();
    this->setCentralWidget(sdrawtable);

    toolbar = new QDockWidget();
    colorselector = new ColorSelector*[17];
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
        colorselector[i]->setParent(toolbar);
        colorselector[i]->setGeometry(2 + 20 * (i/8),22 + (i%8)*20,20,20);
        colorselector[i]->index = i;
        connect(colorselector[i], SIGNAL(pressed(int)),this,SLOT(changeColor(int)));
    }
    brush_size_label = new QLabel("Brush Size", toolbar);
    brush_size_label->setGeometry(2,186,80,20);

    textedit_brush_size = new QLineEdit("1 px", toolbar);
    textedit_brush_size->setGeometry(2,206,80,20);

    connect(textedit_brush_size, SIGNAL(textEdited(QString)),this,SLOT(changeBrushSizeTextEdit()));

    slider_brush_size = new QSlider(Qt::Horizontal, toolbar);
    slider_brush_size->setGeometry(2, 226,80,20);
    slider_brush_size->setMaximum(100);
    slider_brush_size->setMinimum(1);
    slider_brush_size->setValue(1);

    connect(slider_brush_size,SIGNAL(sliderMoved(int)),this,SLOT(changeBrushSizeSlider(int)));

    colorselector[16] = new ColorSelector();
    colorselector[16]->setPixmap(colorpixmap[0]);
    colorselector[16]->setParent(toolbar);
    colorselector[16]->setGeometry(2 ,248,20,20);

    this->addDockWidget(Qt::LeftDockWidgetArea, toolbar);
    toolbar->setFixedWidth(85);
    toolbar->setMinimumWidth(85);
    toolbar->setMaximumWidth(85);

    fileMenu = this->menuBar()->addMenu(tr("&File"));
    exitAct = fileMenu->addAction(tr("&Exit"));
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));

    imageMenu = this->menuBar()->addMenu(tr("&Image"));
    resizeAct = imageMenu->addAction(tr("&Resize"));
    connect(resizeAct, SIGNAL(triggered()),this,SLOT(resizeImage()));


}

void MainWindow::changeColor(int i)
{
    this->sdrawtable->changePen(QPen(QBrush(color[i]),slider_brush_size->value(),Qt::SolidLine,Qt::RoundCap));
    colorselector[16]->setPixmap(colorpixmap[i]);
}

void MainWindow::changeBrushSizeSlider(int i)
{
    this->sdrawtable->changePen(QPen(QBrush(sdrawtable->getPen().color()),i,Qt::SolidLine,Qt::RoundCap));
    textedit_brush_size->setText(QVariant(slider_brush_size->value()).toString().append(" px"));
}

void MainWindow::changeBrushSizeTextEdit()
{
    int newsize = 1;
    if (textedit_brush_size->text().indexOf("px") > -1)
        newsize = QVariant(textedit_brush_size->text().mid(0,textedit_brush_size->text().size()-3)).toInt();
    else
        newsize = QVariant(textedit_brush_size->text()).toInt();
    newsize = (newsize > 100 ? 100 : newsize);
    newsize = (newsize < 1? slider_brush_size->value() : newsize);
    this->sdrawtable->changePen(QPen(QBrush(sdrawtable->getPen().color()),newsize,Qt::SolidLine,Qt::RoundCap));
    textedit_brush_size->setText(QVariant(newsize).toString().append(" px"));
    slider_brush_size->setValue(newsize);
}

void MainWindow::resizeImage()
{
    resizeDialog *rd;
    rd = new resizeDialog(this->sdrawtable->pixmap->width(),this->sdrawtable->pixmap->height(),this);
    rd->exec();
    if (rd->returnSize.width() > 0 && rd->returnSize.height() > 0)
    {
        this->sdrawtable->resizePicture(rd->returnSize.width(), rd->returnSize.height());
    }
    delete rd;
}

MainWindow::~MainWindow()
{

}
