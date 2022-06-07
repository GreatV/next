#include "next.h"
#include "./ui_next.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QScreen>

#include <opencv2/opencv.hpp>


static void QImage2cvMat(QImage& image, cv::Mat& mat)
{
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        break;
    }
}


next::next(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::next)
{
    ui->setupUi(this);

    this->resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

next::~next()
{
    delete ui;
}


void next::on_actionOpen_triggered()
{
    qDebug() << "action Open is triggered.";
    auto fileName = QFileDialog::getOpenFileName(this,
                                                 tr("Open Image File"),
                                                 "",
                                                 tr("Image Files (*.jpg;*.png;*.jpeg;*.bmp)"));
    if (fileName.isEmpty())
    {
        return;
    }
    //  cv::Mat image = cv::imread(fileName.toStdString());
    //  resize image when image is too large or too small
    //  cv::resize(image, image, cv::Size(640, 640), 0, 0, cv::INTER_LINEAR);
    //  cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    //  QImage im((uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    QImage im(fileName);
    ui->labelDisplayedImage->setPixmap(QPixmap::fromImage(im));
    ui->labelDisplayedImage->resize(ui->labelDisplayedImage->pixmap().size());
}

