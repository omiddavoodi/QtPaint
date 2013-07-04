#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QCursor>
#include <QBitmap>

class myDrawWidget : public QGraphicsView
{
    Q_OBJECT
    private:
        int image_width;
        int image_height;
        QPointF old_mouse_position;
        QPen *pen;
        QPen *pen2;
        QCursor *cur;
    public:
        explicit myDrawWidget(QWidget *parent = 0);

        void set_image_width(int a);
        void set_image_height(int a);

        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);

        void changePen(QPen npen);
        QPen getPen();
        void changeSecondaryPen(QPen npen);
        QPen getSecondaryPen();

        QGraphicsScene *scene;
        QPixmap *pixmap;
        QGraphicsPixmapItem *pitem;

        void resizePicture(int width, int height);
        void clearImage();
        void loadImageFromFile(QString filename, const char * format = 0);
        void saveImageFile(QString filename, const char * format = 0);
    signals:

    public slots:
    
};

#endif // DRAWWIDGET_H
