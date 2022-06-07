#ifndef NEXT_H
#define NEXT_H

#include <QMainWindow>

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
    void on_actionOpen_triggered(bool checked);

private:
    Ui::next *ui;
};
#endif // NEXT_H
