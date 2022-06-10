#ifndef IMAGECANVAS_H
#define IMAGECANVAS_H

#include <QLabel>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>

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
};

#endif // IMAGECANVAS_H
