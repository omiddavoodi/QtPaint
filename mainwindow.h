#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawwidget.h"
#include <QDockWidget>
#include "colorselector.h"
#include <QPixmap>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    myDrawWidget *sdrawtable;
    QDockWidget *color_selection;
    ColorSelector **colorselector;
    QPixmap *colorpixmap;
    QColor *color;
    ~MainWindow();
    
private:

public slots:
    void changeColor(int i);
};

#endif // MAINWINDOW_H
