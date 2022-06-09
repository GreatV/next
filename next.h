#ifndef NEXT_H
#define NEXT_H

#include <QMainWindow>
#include <QLabel>

#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class next; }
QT_END_NAMESPACE

class next : public QMainWindow
{
    Q_OBJECT

public:
    next(QWidget *parent = nullptr);
    ~next();

private slots:
    void on_actionOpen_triggered();

private:
    Ui::next *ui;

    QLabel* status_message_label;
    std::string settings_config_filename;

    int current_image_index;

    void init_ui();
};
#endif // NEXT_H
