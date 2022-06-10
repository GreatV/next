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

//void ImageCanvas::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    QRect dirty_rect = event->rect();
//    painter.drawImage(dirty_rect, image, dirty_rect);
//}
