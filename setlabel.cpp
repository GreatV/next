#include "setlabel.h"
#include "ui_setlabel.h"

SetLabel::SetLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetLabel)
{
    ui->setupUi(this);
}

SetLabel::~SetLabel()
{
    delete ui;
}
