#include "tabedit.h"
#include "ui_tabedit.h"

tabedit::tabedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabedit)
{
    ui->setupUi(this);
}

tabedit::~tabedit()
{
    delete ui;
}
