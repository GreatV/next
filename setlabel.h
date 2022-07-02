#ifndef SETLABEL_H
#define SETLABEL_H

#include <QWidget>

namespace Ui {
class SetLabel;
}

class SetLabel : public QWidget
{
    Q_OBJECT

        public:
                 explicit SetLabel(QWidget *parent = nullptr);
    ~SetLabel();

private:
    Ui::SetLabel *ui;
};

#endif // SETLABEL_H
