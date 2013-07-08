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
#include <QImage>

class myDrawWidget : public QGraphicsView
{
    Q_OBJECT
    private:
        int image_width;
        int image_height;
        int canvas_width;
        int canvas_height;
        int zoom_level;

        QPointF *old_mouse_position;
        QPointF *point;
        QPen *pen;
        QPen *pen2;
        QCursor *cur;
        QPainter qp;
        QImage s;
        QImage s2;

        void updateHelperPixamp(int, int);
        void updateHelperPixamp();
        void updateZoomedPixmap();
    public:
        explicit myDrawWidget(QWidget *parent = 0);

        void set_image_width(int a);
        void set_image_height(int a);

        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);
        void mouseReleaseEvent(QMouseEvent * event);

        void changePen(QPen npen);
        QPen getPen();
        void changeSecondaryPen(QPen npen);
        QPen getSecondaryPen();

        QGraphicsScene *scene;
        QPixmap *pixmap;
        QPixmap *helper_pixmap;
        QPixmap *zoomed_pixmap;
        QGraphicsPixmapItem *pitem;

        void resizePicture(int width, int height);
        void clearImage();
        void loadImageFromFile(QString filename, const char * format = 0);
        void saveImageFile(QString filename, const char * format = 0);
        void invertImage();
        void changeHue(int hue);
        void changeSaturation(int sat);
        void changeLightness(int lig);
        void setZoomLevel(int level);

        ~myDrawWidget();
    signals:

    public slots:
    
};

#endif // DRAWWIDGET_H
