#include "imagecanvas.h"
#include <QPainter>


ImageCanvas::ImageCanvas(QWidget *parent)
    : QLabel(parent)
{}

ImageCanvas::~ImageCanvas() {}

QPoint ImageCanvas::getMousePosition()
{
    return last_point;
}

void ImageCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        last_point = event->position().toPoint();
        labeling = true;
        qDebug() << "[MousePressEvent]: " << last_point;
    }
}

void ImageCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && labeling) {
        end_point = event->position().toPoint();
//        drawShapeTo();
//        qDebug() << "[MouseMoveEvent]: " << point;
    }
}

void ImageCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && labeling) {
        end_point = event->position().toPoint();
        labeling = false;
        qDebug() << "[MouseReleseEvent]: " << end_point;
    }
}

void ImageCanvas::drawShapeTo(const int draw_shape_type)
{
    QPainter painter(this);
//    painter.setPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if (draw_shape_type == 0)
    {
        painter.drawLine(last_point, end_point);
    }

    if (draw_shape_type == 1)
    {
        painter.drawRect(QRect(last_point, end_point));
    }

    int rad = (2 / 2) + 2;
    update(QRect(last_point, end_point).normalized().adjusted(-rad, -rad, +rad, +rad));
    last_point = end_point;
}

//void ImageCanvas::paintEvent(QPaintEvent *event)
//{
////    QPainter painter(this);
////    QRect dirty_rect = event->rect();
////    painter.drawImage(dirty_rect, image, dirty_rect);
//}

