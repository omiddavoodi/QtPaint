#include "colorselector.h"
#include <QMouseEvent>
void ColorSelector::mousePressEvent(QMouseEvent *event)
{
    emit this->pressed(index, (event->button() == Qt::RightButton ? false : true));
}
