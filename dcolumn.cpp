#include "dcolumn.h"
#include "ui_dcolumn.h"
#include <fstream>
using namespace std;
dcolumn::dcolumn(std::string path , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dcolumn)
{
    ui->setupUi(this);
    PATH = path;
    ifstream infile(PATH);
    string text;
    while(std::getline(infile,text)){
        filetext = filetext + text + "\n";
    }
    infile.close();
    ui->collist->setText(QString::fromStdString(filetext));


    this->hide();
}
void dcolumn::editcol(){
    ofstream infile(PATH);
    infile << ui->collist->toPlainText().toStdString();
    infile.close();

}
void dcolumn::wait(){
    if(QDialog::exec()){
        return;
    }
}
void dcolumn::addcol(){
    ui->collist->setText(QString::fromStdString(ui->collist->toPlainText().toStdString() + string("Coloana Noua")+ string("\n")));
}
dcolumn::~dcolumn()
{
    delete ui;
}

void dcolumn::on_editb_clicked()
{
    editcol();
}


void dcolumn::on_addb_clicked()
{
    addcol();
}

