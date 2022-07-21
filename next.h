#ifndef NEXT_H
#define NEXT_H

#include <QMainWindow>
#include <QLabel>
#include <string>
#include <QUndoStack>
#include <QComboBox>


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

    void on_actionExit_triggered();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    Ui::next *ui;

    QLabel* status_message_image;
    QLabel* status_message_position;

    QPoint current_point;
    QImage dispalyed_image;

    std::string settings_config_filename;

    int current_image_index;
    bool cursor_changed;

    std::vector<int> label_history;
    std::vector<std::string> names;

    std::map<std::string, int> label_id_map;

    void init_ui();
};
#endif // NEXT_H
