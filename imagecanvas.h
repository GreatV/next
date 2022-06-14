#ifndef IMAGECANVAS_H
#define IMAGECANVAS_H

#include <QLabel>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>


enum drawShape{
    Point = 0,
    Rect,
    };


class ImageCanvas : public QLabel
{
    Q_OBJECT
public:
    ImageCanvas(QWidget *parent = nullptr);
    ~ImageCanvas();

    QPoint getMousePosition();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

//    void paintEvent(QPaintEvent *event);

private:
    QImage image;

    QPoint last_point;
    QPoint end_point;
    bool labeling;

    void drawShapeTo(int draw_shape_type = 1);
};

#endif // IMAGECANVAS_H
