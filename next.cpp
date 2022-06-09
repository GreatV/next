#include "next.h"
#include "./ui_next.h"

#include <fstream>

#include <QCollator>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QScreen>
#include <QStandardPaths>

#include <opencv2/opencv.hpp>

#include "nlohmann/json.hpp"

static void QImage2cvMat(QImage &image, cv::Mat &mat)
{
    switch (image.format()) {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(),
                      image.width(),
                      CV_8UC4,
                      (void *) image.constBits(),
                      image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(),
                      image.width(),
                      CV_8UC3,
                      (void *) image.constBits(),
                      image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(),
                      image.width(),
                      CV_8UC1,
                      (void *) image.constBits(),
                      image.bytesPerLine());
        break;
    default:
        break;
    }
}

next::next(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::next)
{
    status_message_label = nullptr;
    settings_config_filename = std::string("configs/settings.json");
    current_image_index = 0;
    ui->setupUi(this);

    init_ui();
}

void next::init_ui()
{
    this->resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

    // create configs dir if not exists
    QString configs_dir_name(".");
    QDir configs_dir(configs_dir_name);
    if (!configs_dir.exists("configs")) {
        configs_dir.mkdir("configs");
    }
}

next::~next()
{
    delete ui;
}

void next::on_actionOpen_triggered()
{
    qDebug() << "action Open is triggered.";

    std::ifstream settings_file(settings_config_filename);
    nlohmann::json settings;
    QString current_dir_name(".");
    if (settings_file) {
        settings = nlohmann::json::parse(settings_file);
        current_dir_name = QString(settings.at("current_dir").get<std::string>().c_str());
        qDebug() << "Current dir: " << current_dir_name;
        settings_file.close();
    }

    auto file_name = QFileDialog::getOpenFileName(this,
                                                  tr("Open Image File"),
                                                  current_dir_name,
                                                  tr("Image Files (*.jpg;*.png;*.jpeg;*.bmp)"));
    if (file_name.isEmpty()) {
        return;
    }

    auto file_info = QFileInfo(file_name);

    current_dir_name = file_info.dir().absolutePath();
    settings["current_dir"] = current_dir_name.toStdString();
    std::string settings_string = settings.dump();
    qDebug() << "settings content: " << QString(settings_string.c_str());

    std::ofstream save_settings(settings_config_filename);
    save_settings << settings_string;
    save_settings.close();

    QImage image(file_name);

    // get raw image size
    auto raw_depth = image.depth();
    auto raw_width = image.size().width();
    auto raw_height = image.size().height();

    // get image container's size
    auto available_width = ui->widgetCenter->size().width();
    auto available_height = ui->widgetCenter->size().height();

    auto w = raw_width > available_width ? available_width : raw_width;
    auto h = raw_height > available_height ? available_height : raw_height;

    // calculate resize ratio of image
    auto resize_ratio = w > h ? w * 1.0f / raw_width : h * 1.0f / raw_height;

    auto scaled_size(QSize(raw_width * resize_ratio, raw_height * resize_ratio));
    QImage dispalyed_image = image.scaled(scaled_size);

    ui->labelDisplayedImage->setPixmap(QPixmap::fromImage(dispalyed_image));
    ui->labelDisplayedImage->setAlignment(Qt::AlignCenter);

    // show image information in the status bar
    if (status_message_label) {
        ui->statusbar->removeWidget(status_message_label);
    } else {
        auto message = QString("%1% %2x%3 %4")
                           .arg(resize_ratio * 100)
                           .arg(raw_width)
                           .arg(raw_height)
                           .arg(raw_depth);
        status_message_label = new QLabel(message);
        status_message_label->setAlignment(Qt::AlignRight);
        ui->statusbar->addWidget(status_message_label, 1);
    }

    // find all image file in current dir
    QDir current_dir(current_dir_name);
    QStringList image_filters;
    image_filters << "*.jpg"
                  << "*.png"
                  << "*.jpeg"
                  << "*.bmp";
    auto image_list = current_dir.entryList(image_filters,
                                            QDir::Files | QDir::Readable | QDir::Writable);

    QCollator collator;
    collator.setNumericMode(true);

    // sort filenames naturally
    std::sort(image_list.begin(), image_list.end(), collator);

    // find index of current select image
    current_image_index = image_list.indexOf(file_info.fileName());

    if (!image_list.empty() && image_list.size() <= 32)
        qDebug() << "Image list: \n"
                 << image_list << "\nCurrent select image index: " << current_image_index
                 << "\nCurrent image filename: " << file_info.fileName();
}
