#include "next.h"
#include "./ui_next.h"

next::next(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::next)
{
    ui->setupUi(this);
}

next::~next()
{
    delete ui;
}


void next::on_actionOpen_triggered(bool checked)
{
    qDebug() << "action Open is triggered.";

}

