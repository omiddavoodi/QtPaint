#include "drawwidget.h"
#include <QPainter>
#include <QColor>
#include <QDebug>


myDrawWidget::myDrawWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    this->image_height = 150;
    this->image_width = 200;
    this->canvas_height = 150;
    this->canvas_width = 200;
    this->zoom_level = 1;

    this->setMouseTracking(true);

    this->pen = new QPen(QColor(0,0,0));
    this->pen2 = new QPen(QColor(255,255,255));

    this->point = new QPointF();
    this->old_mouse_position = new QPointF();

    this->scene = new QGraphicsScene(0,0,image_width, image_height,this);
    this->pixmap = new QPixmap(image_width, image_height);
    this->helper_pixmap = new QPixmap(image_width, image_height);
    this->zoomed_pixmap = new QPixmap(image_width, image_height);
    pixmap->fill(Qt::white);
    helper_pixmap->fill(Qt::white);
    pitem = new QGraphicsPixmapItem();
    pitem->setPixmap(*pixmap);
    this->scene->addItem(pitem);
    this->setScene(scene);
    this->setBackgroundBrush(QBrush(QColor(127,127,127)));
    old_mouse_position->setX(0);
    old_mouse_position->setY(0);
    QBitmap bitmap("cursor2.bmp");
    cur = new QCursor(bitmap,bitmap,11,11);

    this->setCursor(*cur);

    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void myDrawWidget::set_image_width(int a)
{
    this->image_width = a;
    this->canvas_width = a*zoom_level;
}

void myDrawWidget::set_image_height(int a)
{
    this->image_height = a;
    this->canvas_height = a*zoom_level;
}

void myDrawWidget::mousePressEvent(QMouseEvent *e)
{
    int temp_x = e->x()-(200-image_width)*zoom_level/(2.0);
    int temp_y = e->y()-(150-image_height)*zoom_level/(2.0);

    point->setX(this->mapToScene(temp_x, temp_y).x() - pitem->offset().x() - (image_width - 200)*zoom_level/2.0);
    point->setY(this->mapToScene(temp_x, temp_y).y() - pitem->offset().y() - (image_height - 150)*zoom_level/2.0);

    if (point->x() >= 0 && point->y() >= 0 && point->x() < this->canvas_width && point->y() < this->canvas_height)
    {
        qp.begin(pixmap);
        if (e->button() == Qt::LeftButton)
            qp.setPen(*pen);
        else if (e->button() == Qt::RightButton)
            qp.setPen(*pen2);
        qp.drawPoint(point->x()/(zoom_level),point->y()/(zoom_level));
        qp.end();
        if (e->button() == Qt::RightButton)
            updateHelperPixamp();
        else
            updateHelperPixamp(point->x()/(zoom_level),point->y()/(zoom_level));
        updateZoomedPixmap();
        pitem->setPixmap(*zoomed_pixmap);
        old_mouse_position->setX(point->x()/(zoom_level));
        old_mouse_position->setY(point->y()/(zoom_level));
    }
    this->setCursor(*cur);
}

void myDrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    int temp_x = e->x()-(200-image_width)*zoom_level/(2.0);
    int temp_y = e->y()-(150-image_height)*zoom_level/(2.0);

    point->setX(this->mapToScene(temp_x, temp_y).x() - pitem->offset().x() - (image_width - 200)*zoom_level/2.0);
    point->setY(this->mapToScene(temp_x, temp_y).y() - pitem->offset().y() - (image_height - 150)*zoom_level/2.0);

    if (e->buttons() == Qt::LeftButton || e->buttons() == Qt::RightButton)
    {
        if (point->x() >= 0 && point->y() >= 0 && point->x() < this->canvas_width && point->y() < this->canvas_height)
        {
            qp.begin(pixmap);
            if (e->buttons() == Qt::LeftButton)
                qp.setPen(*pen);
            else if (e->buttons() == Qt::RightButton)
                qp.setPen(*pen2);
            qp.drawLine(old_mouse_position->x(), old_mouse_position->y(),point->x()/(zoom_level),point->y()/(zoom_level));
            qp.end();
            if (e->buttons() == Qt::RightButton)
                updateHelperPixamp();
            else
                updateHelperPixamp(point->x()/(zoom_level),point->y()/(zoom_level));
            updateZoomedPixmap();
            pitem->setPixmap(*zoomed_pixmap);
        }
        old_mouse_position->setX(point->x()/(zoom_level));
        old_mouse_position->setY(point->y()/(zoom_level));
        //this->setCursor(*cur);
    }
    else
    {
        updateHelperPixamp(point->x()/(zoom_level),point->y()/(zoom_level));
        updateZoomedPixmap();
        pitem->setPixmap(*zoomed_pixmap);
    }
}

void myDrawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int temp_x = e->x()-(200-image_width)*zoom_level/(2.0);
    int temp_y = e->y()-(150-image_height)*zoom_level/(2.0);

    point->setX(this->mapToScene(temp_x, temp_y).x() - pitem->offset().x() - (image_width - 200)*zoom_level/2.0);
    point->setY(this->mapToScene(temp_x, temp_y).y() - pitem->offset().y() - (image_height - 150)*zoom_level/2.0);

    updateHelperPixamp(point->x()/(zoom_level),point->y()/(zoom_level));
    updateZoomedPixmap();
    pitem->setPixmap(*zoomed_pixmap);
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

void myDrawWidget::resizePicture(int width2, int height2)
{
    int ow = pixmap->width(), oh = pixmap->height();
    QPixmap *s = new QPixmap(width2, height2);
    s->fill(Qt::white);
    qp.begin(s);
    qp.drawPixmap(0,0,*pixmap);
    qp.end();
    pixmap = new QPixmap(width2,height2);
    this->image_height = height2;
    this->image_width = width2;
    this->canvas_height = height2*zoom_level;
    this->canvas_width = width2*zoom_level;
    qp.begin(pixmap);
    qp.drawPixmap(0,0,*s);
    qp.end();
    delete s;
    QPointF *newpoint = new QPointF(pitem->offset().x()-((width2-ow)*zoom_level)/2.0,pitem->offset().y()-((height2-oh)*zoom_level)/2.0);
    updateHelperPixamp();
    updateZoomedPixmap();
    this->pitem->setPixmap(*zoomed_pixmap);
    pitem->setOffset(newpoint->rx(), newpoint->ry());
    this->setSceneRect(newpoint->x(),newpoint->y(),width2*zoom_level,height2*zoom_level);
    delete newpoint;

}

void myDrawWidget::clearImage()
{
    this->pixmap->fill(Qt::white);
    updateHelperPixamp();
    updateZoomedPixmap();
    this->pitem->setPixmap(*zoomed_pixmap);
}

void myDrawWidget::loadImageFromFile(QString filename, const char *format)
{
    int ow = pixmap->width(), oh = pixmap->height();
    pixmap->load(filename, format);
    int height2 = pixmap->height(), width2 = pixmap->width();
    QPointF *newpoint = new QPointF(pitem->offset().x()-((width2-ow)*zoom_level)/2.0,pitem->offset().y()-((height2-oh)*zoom_level)/2.0);
    this->image_height = height2;
    this->image_width = width2;
    this->canvas_height = height2*zoom_level;
    this->canvas_width = width2*zoom_level;
    updateHelperPixamp();
    updateZoomedPixmap();
    this->pitem->setPixmap(*zoomed_pixmap);
    pitem->setOffset(newpoint->rx(), newpoint->ry());
    this->setSceneRect(newpoint->x(),newpoint->y(),width2*zoom_level,height2*zoom_level);
    delete newpoint;
}

void myDrawWidget::saveImageFile(QString filename, const char *format)
{
    pixmap->save(filename,format);
}

void myDrawWidget::invertImage()
{
    s = pixmap->toImage();
    for (int x = 0; x < s.width(); ++x)
    {
        for (int y = 0; y < s.height(); ++y)
        {
            s.setPixel(x,y,(uint)(QColor(255-QColor(s.pixel(x,y)).red(),255-QColor(s.pixel(x,y)).green(),255-QColor(s.pixel(x,y)).blue()).rgb()));
        }
    }
    qp.begin(pixmap);
    qp.drawPixmap(0,0,QPixmap::fromImage(s));
    qp.end();
    updateHelperPixamp();
    updateZoomedPixmap();
    this->pitem->setPixmap(*zoomed_pixmap);

}

void myDrawWidget::changeHue(int hue)
{
    if (hue != 0)
    {
        s = pixmap->toImage();
        for (int x = 0; x < s.width(); ++x)
        {
            for (int y = 0; y < s.height(); ++y)
            {
                QColor temp = QColor(s.pixel(x,y)).toHsl();
                temp.setHsl(hue + temp.hue(),temp.saturation(),temp.lightness());
                s.setPixel(x,y,(uint)(temp.toRgb().rgb()));
            }
        }
        qp.begin(pixmap);
        qp.drawPixmap(0,0,QPixmap::fromImage(s));
        qp.end();
        updateHelperPixamp();
        updateZoomedPixmap();
        this->pitem->setPixmap(*zoomed_pixmap);
    }
}

void myDrawWidget::changeSaturation(int sat)
{
    if (sat != 0)
    {
        s = pixmap->toImage();
        for (int x = 0; x < s.width(); ++x)
        {
            for (int y = 0; y < s.height(); ++y)
            {
                QColor temp = QColor(s.pixel(x,y)).toHsl();
                if (sat > 0)
                    temp.setHsl(temp.hue(),(int)(sat/100.0*(100-temp.saturation())) + temp.saturation(),temp.lightness());
                else
                    temp.setHsl(temp.hue(),(int)(sat/100.0*(temp.saturation())) + temp.saturation(),temp.lightness());
                s.setPixel(x,y,(uint)(temp.toRgb().rgb()));
            }
        }
        qp.begin(pixmap);
        qp.drawPixmap(0,0,QPixmap::fromImage(s));
        qp.end();
        updateHelperPixamp();
        updateZoomedPixmap();
        this->pitem->setPixmap(*zoomed_pixmap);
    }
}

void myDrawWidget::changeLightness(int lig)
{
    if (lig != 0)
    {
        s = pixmap->toImage();
        for (int x = 0; x < s.width(); ++x)
        {
            for (int y = 0; y < s.height(); ++y)
            {
                QColor temp = QColor(s.pixel(x,y)).toHsl();
                if (lig > 0)
                    temp.setHsl(temp.hue(),temp.saturation(),(int)(lig/100.0*(255-temp.lightness())) + temp.lightness());
                else
                    temp.setHsl(temp.hue(),temp.saturation(),(int)(lig/100.0*(temp.lightness())) + temp.lightness());
                s.setPixel(x,y,(uint)(temp.toRgb().rgb()));
            }
        }
        qp.begin(pixmap);
        qp.drawPixmap(0,0,QPixmap::fromImage(s));
        qp.end();
        updateHelperPixamp();
        updateZoomedPixmap();
        this->pitem->setPixmap(*zoomed_pixmap);
    }
}

void myDrawWidget::setZoomLevel(int level)
{
    this->zoom_level = level;
    int ow = canvas_width, oh = canvas_height;
    canvas_width = zoom_level * image_width;
    canvas_height = zoom_level * image_height;
    qDebug() << canvas_width << " " << canvas_height;
    updateHelperPixamp();
    updateZoomedPixmap();
    this->pitem->setPixmap(*zoomed_pixmap);
    QPointF *newpoint = new QPointF(pitem->offset().x()-(canvas_width-ow)/2.0,pitem->offset().y()-(canvas_height-oh)/2.0);
    pitem->setOffset(newpoint->rx(), newpoint->ry());
    this->setSceneRect(newpoint->x(),newpoint->y(),canvas_width,canvas_height);
    delete newpoint;
}

myDrawWidget::~myDrawWidget()
{
    delete pen;
    delete pen2;
    delete cur;
    delete scene;
    delete pixmap;
    delete helper_pixmap;
    delete zoomed_pixmap;
    //delete pitem;
}


void myDrawWidget::updateHelperPixamp(int x, int y)
{
    delete helper_pixmap;
    helper_pixmap = new QPixmap(pixmap->width(), pixmap->height());
    qp.begin(helper_pixmap);
    qp.drawPixmap(0,0,*pixmap);
    qp.setPen(*pen);
    qp.drawPoint(x,y);
    qp.end();
}

void myDrawWidget::updateHelperPixamp()
{
    delete helper_pixmap;
    helper_pixmap = new QPixmap(pixmap->width(), pixmap->height());
    qp.begin(helper_pixmap);
    qp.drawPixmap(0,0,*pixmap);
    qp.end();
}

void myDrawWidget::updateZoomedPixmap()
{
    delete zoomed_pixmap;
    zoomed_pixmap = new QPixmap(canvas_width, canvas_height);
    s = helper_pixmap->toImage();
    s2 = zoomed_pixmap->toImage();
    for (int x = 0; x < s2.width(); ++x)
    {
        for (int y = 0; y < s2.height(); ++y)
        {
            s2.setPixel(x,y,(uint)(s.pixel(x/(zoom_level),y/(zoom_level))));
        }
    }
    qp.begin(zoomed_pixmap);
    qp.drawPixmap(0,0,QPixmap::fromImage(s2));
    qp.end();
}
