#include "measuringdialog.h"
#include "ui_measuringdialog.h"

using namespace std;
measuringdialog::measuringdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::measuringdialog)
{
    ui->setupUi(this);
    this->show();

}
/*std::string get_ms2text();
    std::string get_ms3text();
    void set_name(std::string name);
    void set_price(std::string price);
    void set_quantity(std::string quantity); ---- defined*/
measuringdialog::~measuringdialog()
{
    delete ui;
}
std::vector<string> measuringdialog::get_text(){if(QDialog::exec()){
        string text1 = ui->ms2->toPlainText().toStdString();
        string text2 = ui->ms3->toPlainText().toStdString();
        std::vector<string> vector = {text1,text2};


        return vector;}}


void measuringdialog::set_name(std::string name)
{ui->name->setText(QString::fromStdString(name));}

void measuringdialog::set_price(std::string price)
{ui->price->setText(QString::fromStdString(price));}

void measuringdialog::set_quantity(std::string quantity)
{ui->quantity->setText(QString::fromStdString(quantity));}

