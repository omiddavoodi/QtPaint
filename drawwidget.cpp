#include "drawwidget.h"
#include <QPainter>
#include <QColor>
#include <QDebug>


myDrawWidget::myDrawWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    this->image_height = 150;
    this->image_width = 200;

    this->pen = new QPen(QColor(0,0,0));

    this->scene = new QGraphicsScene(0,0,image_width, image_height,this);
    this->pixmap = new QPixmap(image_width, image_height);
    pixmap->fill(Qt::white);
    pitem = new QGraphicsPixmapItem();
    pitem->setPixmap(*pixmap);
    this->scene->addItem(pitem);
    this->setScene(scene);
    this->setBackgroundBrush(QBrush(QColor(127,127,127)));
    old_mouse_position.setX(0);
    old_mouse_position.setY(0);
    QBitmap bitmap("cursor2.bmp");
    cur = new QCursor(bitmap,bitmap,11,11);

    this->setCursor(*cur);
}

void myDrawWidget::set_image_width(int a)
{
    this->image_width = a;
}

void myDrawWidget::set_image_height(int a)
{
    this->image_height = a;
}

void myDrawWidget::mousePressEvent(QMouseEvent *e)
{
    QPointF point = this->mapToScene(e->x(), e->y());
    if (point.x() >= 0 && point.y() >= 0 && point.x() < this->image_width && point.y() < this->image_height)
    {
        QPainter qp;
        qp.begin(pixmap);
        qp.setPen(*pen);
        qp.drawPoint(point);
        qp.end();
        pitem->setPixmap(*pixmap);
        old_mouse_position = point;
    }
    this->setCursor(*cur);
}

void myDrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPointF point = this->mapToScene(e->x(), e->y());
    if (point.x() >= 0 && point.y() >= 0 && point.x() < this->image_width && point.y() < this->image_height)
    {
        QPainter qp;
        qp.begin(pixmap);
        qp.setPen(*pen);
        qp.drawLine(old_mouse_position,point);
        qp.end();
        pitem->setPixmap(*pixmap);
    }
    old_mouse_position = point;
    this->setCursor(*cur);
}

void myDrawWidget::changePen(QPen npen)
{
    this->pen->setBrush(npen.brush());
    this->pen->setCapStyle(npen.capStyle());
    this->pen->setColor(npen.color());
    this->pen->setCosmetic(npen.isCosmetic());
    this->pen->setWidth(npen.width());
}
