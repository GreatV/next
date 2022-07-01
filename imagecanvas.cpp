#include "imagecanvas.h"
#include <QPainter>


ImageCanvas::ImageCanvas(QWidget *parent)
    : QLabel(parent)
{
    copy_once = false;
}

ImageCanvas::~ImageCanvas() {}


void ImageCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        last_point = event->position().toPoint();
        labeling = true;
        qDebug() << "[MousePressEvent]: " << last_point;
        draw_rect.setTopLeft(event->pos());
        draw_rect.setBottomRight(event->pos());
    }
}

void ImageCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && labeling) {
        end_point = event->position().toPoint();
        draw_rect.setBottomRight(event->pos());
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
        this->update();
    }
}

void ImageCanvas::paintEvent(QPaintEvent *event)
{
    if (!this->pixmap().isNull())
    {
        if (!copy_once)
        {
            ref_pixmap = QPixmap(this->pixmap());
            copy_once = true;
        }

        painter.begin(this);

        //When the mouse is pressed
        if(labeling){
            // we are taking QPixmap reference again and again
            //on mouse move and drawing a line again and again
            //hence the painter view has a feeling of dynamic drawing
            painter.drawPixmap(0,0,ref_pixmap);
            painter.drawRect(draw_rect);

            drawStarted = true;
        }
        else if (drawStarted){
            // It created a QPainter object by taking  a reference
            // to the QPixmap object created earlier, then draws a line
            // using that object, then sets the earlier painter object
            // with the newly modified QPixmap object
            QPainter tempPainter(&ref_pixmap);
            tempPainter.drawRect(draw_rect);

            painter.drawPixmap(0,0,ref_pixmap);
        }

        painter.end();

    }
    else
    {
        QLabel::paintEvent(event);
    }
}
