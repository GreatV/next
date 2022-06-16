#include "imagecanvas.h"
#include <QPainter>


ImageCanvas::ImageCanvas(QWidget *parent)
    : QLabel(parent)
{}

ImageCanvas::~ImageCanvas() {}


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
