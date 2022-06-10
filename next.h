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

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    Ui::next *ui;

    QLabel* status_message_image;
    QLabel* status_message_position;

    QPoint last_point;
    std::string settings_config_filename;

    int current_image_index;
    bool cursor_changed;

    void init_ui();
};
#endif // NEXT_H
