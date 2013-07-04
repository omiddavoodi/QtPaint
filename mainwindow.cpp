#include "mainwindow.h"
#include "resizedialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(500,374);

    fdialog = new QFileDialog(this);

    sdrawtable = new myDrawWidget();
    this->setCentralWidget(sdrawtable);

    toolbar = new QDockWidget();
    colorselector = new ColorSelector*[26];
    colorpixmap = new QPixmap*[26];
    color = new QColor[24];
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
    color[16].setRgb(127,63,0);
    color[17].setRgb(255,127,63);
    color[18].setRgb(255,127,127);
    color[19].setRgb(127,255,127);
    color[20].setRgb(127,127,255);
    color[21].setRgb(255,255,127);
    color[22].setRgb(127,255,255);
    color[23].setRgb(255,127,255);
    for (int i = 0; i < 24; ++i)
    {
        colorpixmap[i] = new QPixmap(20,20);
        colorpixmap[i]->fill(color[i]);
        QPainter qp;
        qp.begin(colorpixmap[i]);
        qp.drawRect(0,0,19,19);
        qp.end();
        colorselector[i] = new ColorSelector();
        colorselector[i]->setPixmap(*colorpixmap[i]);
        colorselector[i]->setParent(toolbar);
        colorselector[i]->setGeometry(2 + 23 * (i/8),22 + (i%8)*23,20,20);
        colorselector[i]->index = i;
        connect(colorselector[i], SIGNAL(pressed(int, bool)),this,SLOT(changeColor(int, bool)));
    }
    brush_size_label = new QLabel("Brush Size", toolbar);
    brush_size_label->setGeometry(2,206,80,20);

    textedit_brush_size = new QLineEdit("1 px", toolbar);
    textedit_brush_size->setGeometry(2,226,80,20);

    connect(textedit_brush_size, SIGNAL(textEdited(QString)),this,SLOT(changeBrushSizeTextEdit()));

    slider_brush_size = new QSlider(Qt::Horizontal, toolbar);
    slider_brush_size->setGeometry(2, 246,80,20);
    slider_brush_size->setMaximum(100);
    slider_brush_size->setMinimum(1);
    slider_brush_size->setValue(1);

    connect(slider_brush_size,SIGNAL(sliderMoved(int)),this,SLOT(changeBrushSizeSlider(int)));

    brush_opacity_label = new QLabel("Brush Opacity", toolbar);
    brush_opacity_label->setGeometry(2,266,80,20);

    textedit_brush_opacity = new QLineEdit("255", toolbar);
    textedit_brush_opacity->setGeometry(2,286,80,20);

    connect(textedit_brush_opacity, SIGNAL(textEdited(QString)),this,SLOT(changeBrushOpacityTextEdit()));

    slider_brush_opacity = new QSlider(Qt::Horizontal, toolbar);
    slider_brush_opacity->setGeometry(2, 306,80,20);
    slider_brush_opacity->setMaximum(255);
    slider_brush_opacity->setMinimum(0);
    slider_brush_opacity->setValue(255);

    connect(slider_brush_opacity,SIGNAL(sliderMoved(int)),this,SLOT(changeBrushOpacitySlider(int)));

    colorpixmap[24] = new QPixmap(20,20);
    colorpixmap[24]->fill(color[0]);
    QPainter qp;
    qp.begin(colorpixmap[24]);
    qp.drawRect(0,0,19,19);
    qp.end();
    colorselector[24] = new ColorSelector();
    colorselector[24]->setPixmap(*colorpixmap[24]);
    colorselector[24]->setParent(toolbar);
    colorselector[24]->setGeometry(2 ,330,20,20);

    colorpixmap[25] = new QPixmap(20,20);
    colorpixmap[25]->fill(color[1]);
    qp.begin(colorpixmap[25]);
    qp.drawRect(0,0,19,19);
    qp.end();
    colorselector[25] = new ColorSelector();
    colorselector[25]->setPixmap(*colorpixmap[25]);
    colorselector[25]->setParent(toolbar);
    colorselector[25]->setGeometry(25 ,330,20,20);

    this->addDockWidget(Qt::LeftDockWidgetArea, toolbar);
    toolbar->setFixedWidth(85);
    toolbar->setMinimumWidth(85);
    toolbar->setMaximumWidth(85);

    fileMenu = this->menuBar()->addMenu(tr("&File"));
    newAct = fileMenu->addAction(tr("&New"));
    connect(newAct,SIGNAL(triggered()),this,SLOT(newImage()));
    openAct = fileMenu->addAction(tr("&Open"));
    connect(openAct,SIGNAL(triggered()),this,SLOT(openImage()));
    saveAct = fileMenu->addAction(tr("&Save"));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(saveImage()));
    exitAct = fileMenu->addAction(tr("&Exit"));
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));

    imageMenu = this->menuBar()->addMenu(tr("&Image"));
    resizeAct = imageMenu->addAction(tr("&Resize"));
    connect(resizeAct, SIGNAL(triggered()),this,SLOT(resizeImage()));


}

void MainWindow::changeColor(int i, bool left)
{
    if (left)
    {
        this->sdrawtable->changePen(QPen(QBrush(QColor(color[i].red(),color[i].green(),color[i].blue(),slider_brush_opacity->value())),slider_brush_size->value(),Qt::SolidLine,Qt::RoundCap));
        colorselector[24]->setPixmap(*colorpixmap[i]);
    }
    else
    {
        this->sdrawtable->changeSecondaryPen(QPen(QBrush(QColor(color[i].red(),color[i].green(),color[i].blue(),slider_brush_opacity->value())),slider_brush_size->value(),Qt::SolidLine,Qt::RoundCap));
        colorselector[25]->setPixmap(*colorpixmap[i]);
    }
}

void MainWindow::changeBrushSizeSlider(int i)
{
    this->sdrawtable->changePen(QPen(QBrush(sdrawtable->getPen().color()),i,Qt::SolidLine,Qt::RoundCap));
    this->sdrawtable->changeSecondaryPen(QPen(QBrush(sdrawtable->getSecondaryPen().color()),i,Qt::SolidLine,Qt::RoundCap));
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
    this->sdrawtable->changeSecondaryPen(QPen(QBrush(sdrawtable->getSecondaryPen().color()),newsize,Qt::SolidLine,Qt::RoundCap));
    textedit_brush_size->setText(QVariant(newsize).toString().append(" px"));
    slider_brush_size->setValue(newsize);
}

void MainWindow::changeBrushOpacitySlider(int i)
{
    this->sdrawtable->changePen(QPen(QBrush(QColor(sdrawtable->getPen().color().red(),sdrawtable->getPen().color().green(),sdrawtable->getPen().color().blue(),i))
                                     ,sdrawtable->getPen().width(),Qt::SolidLine,Qt::RoundCap));
    this->sdrawtable->changeSecondaryPen(QPen(QBrush(QColor(sdrawtable->getSecondaryPen().color().red(),sdrawtable->getSecondaryPen().color().green(),sdrawtable->getSecondaryPen().color().blue(),i))
                                     ,sdrawtable->getSecondaryPen().width(),Qt::SolidLine,Qt::RoundCap));
    textedit_brush_opacity->setText(QVariant(slider_brush_opacity->value()).toString());
}

void MainWindow::changeBrushOpacityTextEdit()
{
    int newopacity = QVariant(textedit_brush_opacity->text()).toInt();
    newopacity = (newopacity > 255 ? 255 : newopacity);
    newopacity = (newopacity < 0 ? 0 : newopacity);
    this->sdrawtable->changePen(QPen(QBrush(QColor(sdrawtable->getPen().color().red(),sdrawtable->getPen().color().green(),sdrawtable->getPen().color().blue(),newopacity))
                                     ,sdrawtable->getPen().width(),Qt::SolidLine,Qt::RoundCap));
    this->sdrawtable->changeSecondaryPen(QPen(QBrush(QColor(sdrawtable->getSecondaryPen().color().red(),sdrawtable->getSecondaryPen().color().green(),sdrawtable->getSecondaryPen().color().blue(),newopacity))
                                     ,sdrawtable->getSecondaryPen().width(),Qt::SolidLine,Qt::RoundCap));
    textedit_brush_opacity->setText(QVariant(newopacity).toString());
    slider_brush_opacity->setValue(newopacity);
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

void MainWindow::newImage()
{
    this->sdrawtable->clearImage();
}

void MainWindow::openImage()
{
    fdialog->setAcceptMode(QFileDialog::AcceptOpen);
    QString filename = fdialog->getOpenFileName(this,"Open Image",QString(),tr("Bitmap (*.bmp);;JPG (*.jpg);;JPEG (*.jpeg);;Graphic Interchange Format (*.gif);;Portable Network Graphic (*.png);;Portable Pixmap (*.ppm);;X11 Bitmap (*.xbm);;X11 Pixmap (*.xpm)"));
    this->sdrawtable->loadImageFromFile(filename);
}

void MainWindow::saveImage()
{
    fdialog->setAcceptMode(QFileDialog::AcceptSave);
    QString filename = fdialog->getSaveFileName(this,"Save Image",QString(),tr("Image files (*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm)"));
    if (fdialog->result() == 1) this->sdrawtable->saveImageFile(filename);
}

MainWindow::~MainWindow()
{

}
