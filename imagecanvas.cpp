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
        mouse_pressed = true;

        drawn_rectangle.setTopLeft(event->pos());
        drawn_rectangle.setBottomRight(event->pos());
    }
}

void ImageCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        drawn_rectangle.setBottomRight(event->pos());

        this->update();
    }
}

void ImageCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mouse_pressed = false;

        this->update();
    }
}

void ImageCanvas::paintEvent(QPaintEvent *event)
{
    if (!this->pixmap().isNull()) {
        if (!copy_once) {
            ref_pixmap = QPixmap(this->pixmap());
            copy_once = true;
        }

        painter.begin(this);

        //When the mouse is pressed
        if (mouse_pressed) {
            // we are taking QPixmap reference again and again
            //on mouse move and drawing a line again and again
            //hence the painter view has a feeling of dynamic drawing
            painter.drawPixmap(0, 0, ref_pixmap);
            QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
            painter.setPen(pen);
            painter.drawRect(drawn_rectangle);

            labeling = true;
        } else if (labeling) {
            // It created a QPainter object by taking  a reference
            // to the QPixmap object created earlier, then draws a line
            // using that object, then sets the earlier painter object
            // with the newly modified QPixmap object
            QPainter tempPainter(&ref_pixmap);
            QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
            tempPainter.setPen(pen);
            tempPainter.drawRect(drawn_rectangle);

            painter.drawPixmap(0, 0, ref_pixmap);
        }

        painter.end();

    } else {
        QLabel::paintEvent(event);
    }
}
