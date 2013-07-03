#include "colorselector.h"

void ColorSelector::mousePressEvent(QMouseEvent *event)
{
    emit this->pressed(index);
}
