#include "drawwidget.h"
#include <QPainter>
#include <QColor>
#include <QDebug>


myDrawWidget::myDrawWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    this->image_height = 150;
    this->image_width = 200;

    this->setMouseTracking(true);

    this->pen = new QPen(QColor(0,0,0));
    this->pen2 = new QPen(QColor(255,255,255));

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

    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
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
    QPointF point = this->mapToScene(e->x()-(200-image_width)/2.0, e->y()-(150-image_height)/2.0);
    if (point.x() >= 0 && point.y() >= 0 && point.x() < this->image_width && point.y() < this->image_height)
    {
        QPainter qp;
        qp.begin(pixmap);
        if (e->button() == Qt::LeftButton)
            qp.setPen(*pen);
        else if (e->button() == Qt::RightButton)
            qp.setPen(*pen2);
        qp.drawPoint(point);
        qp.end();
        pitem->setPixmap(*pixmap);
        old_mouse_position = point;
    }
    this->setCursor(*cur);
}

void myDrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton || e->buttons() == Qt::RightButton)
    {
        QPointF point = this->mapToScene(e->x()-(200-image_width)/2.0, e->y()-(150-image_height)/2.0);
        if (point.x() >= 0 && point.y() >= 0 && point.x() < this->image_width && point.y() < this->image_height)
        {
            QPainter qp;
            qp.begin(pixmap);
            if (e->buttons() == Qt::LeftButton)
                qp.setPen(*pen);
            else if (e->buttons() == Qt::RightButton)
                qp.setPen(*pen2);
            qp.drawLine(old_mouse_position,point);
            qp.end();
            pitem->setPixmap(*pixmap);
        }
        old_mouse_position = point;
        this->setCursor(*cur);
    }
}

void myDrawWidget::changePen(QPen npen)
{
    this->pen->setBrush(npen.brush());
    this->pen->setCapStyle(npen.capStyle());
    this->pen->setColor(npen.color());
    this->pen->setCosmetic(npen.isCosmetic());
    this->pen->setWidth(npen.width());
}

QPen myDrawWidget::getPen()
{
    return *this->pen;
}

void myDrawWidget::changeSecondaryPen(QPen npen)
{
    this->pen2->setBrush(npen.brush());
    this->pen2->setCapStyle(npen.capStyle());
    this->pen2->setColor(npen.color());
    this->pen2->setCosmetic(npen.isCosmetic());
    this->pen2->setWidth(npen.width());
}

QPen myDrawWidget::getSecondaryPen()
{
    return *this->pen2;
}

void myDrawWidget::resizePicture(int width, int height)
{
    int ow = pixmap->width(), oh = pixmap->height();
    QPixmap *s = new QPixmap(width, height);
    s->fill(Qt::white);
    QPainter qp;
    qp.begin(s);
    qp.drawPixmap(0,0,*pixmap);
    qp.end();
    pixmap = new QPixmap(width,height);
    qp.begin(pixmap);
    qp.drawPixmap(0,0,*s);
    qp.end();
    delete s;
    QPointF newpoint(pitem->offset().x()-(width-ow)/2.0,pitem->offset().y()-(height-oh)/2.0);
    this->pitem->setPixmap(*pixmap);
    pitem->setOffset(newpoint);
    this->setSceneRect(newpoint.x(),newpoint.y(),width,height);
    this->image_height = height;
    this->image_width = width;
}

void myDrawWidget::clearImage()
{
    this->pixmap->fill(Qt::white);
    this->pitem->setPixmap(*pixmap);
}

void myDrawWidget::loadImageFromFile(QString filename, const char *format)
{
    int ow = pixmap->width(), oh = pixmap->height();
    pixmap->load(filename, format);
    int height = pixmap->height(), width = pixmap->width();
    QPointF newpoint(pitem->offset().x()-(width-ow)/2.0,pitem->offset().y()-(height-oh)/2.0);
    this->pitem->setPixmap(*pixmap);
    pitem->setOffset(newpoint);
    this->setSceneRect(newpoint.x(),newpoint.y(),width,height);
    this->image_height = height;
    this->image_width = width;
}

void myDrawWidget::saveImageFile(QString filename, const char *format)
{
    pixmap->save(filename,format);
}

