#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawwidget.h"
#include <QDockWidget>
#include "colorselector.h"
#include <QPixmap>
#include <QColor>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    myDrawWidget *sdrawtable;
    QDockWidget *toolbar;
    ColorSelector **colorselector;
    QPixmap *colorpixmap;
    QColor *color;
    QLabel *brush_size_label;
    QSlider *slider_brush_size;
    QLineEdit *textedit_brush_size;
    QMenu *fileMenu;
    QMenu *imageMenu;
    QAction *exitAct;
    QAction *resizeAct;
    ~MainWindow();
    
private:

public slots:
    void changeColor(int i);
    void changeBrushSizeSlider(int);
    void changeBrushSizeTextEdit();
    void resizeImage();
};

#endif // MAINWINDOW_H
