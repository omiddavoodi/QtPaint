#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include <QLabel>

class ColorSelector : public QLabel
{
    Q_OBJECT

public:
    int index;
    ColorSelector(){}
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
signals:
    void pressed(int i, bool left);
    void doubleClicked(int i);
};

#endif // COLORSELECTOR_H
