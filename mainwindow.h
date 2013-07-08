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
#include <QFileDialog>
#include <QColorDialog>
#include <QComboBox>
#include "sliderdialog.h"

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
    QPixmap **colorpixmap;
    QColor *color;
    QLabel *brush_size_label;
    QSlider *slider_brush_size;
    QLineEdit *textedit_brush_size;
    QLabel *brush_opacity_label;
    QSlider *slider_brush_opacity;
    QLineEdit *textedit_brush_opacity;
    QLabel *zoom_label;
    QComboBox *combo_zoom;
    QMenu *fileMenu;
    QMenu *imageMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *resizeAct;
    QAction *invertAct;
    QAction *colorAct;
    QAction *hueAct;
    QAction *saturationAct;
    QAction *lightnessAct;
    QFileDialog *fdialog;
    QColorDialog *cdialog;
    ~MainWindow();
    
private:

public slots:
    void changeColor(int i, bool left);
    void changeBrushSizeSlider(int);
    void changeBrushSizeTextEdit();
    void changeBrushOpacitySlider(int);
    void changeBrushOpacityTextEdit();
    void resizeImage();
    void newImage();
    void openImage();
    void saveImage();
    void invertImage();
    void changeHue();
    void changeSaturation();
    void changeLightness();
    void showColorDialog(int);
    void colorDialogAction();
    void change_zoom(int);
};

#endif // MAINWINDOW_H
