#include "dwindow.h"
#include "ui_dwindow.h"
#include <QListWidgetItem>
#include <iostream>
#include "mainwindow.h"
dwindow::dwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dwindow)
{
    ui->setupUi(this);
    ui->sumslist->setFont(QFont("Segoe UI" , 10));
}

dwindow::~dwindow()
{
    delete ui;
}

void dwindow::add_line(const std::string& line){
    this->append_table(line);
    this->updatelist();
}
void dwindow::reject()
{
    is_showing = false;
    mainwindow func_acces(false);
    func_acces.undo_status();
    hide();


}
void  dwindow::updatelist(){
    QString text = QString::fromStdString(table);
    QListWidgetItem *item = new QListWidgetItem(text);
    ui->sumslist->addItem(item);

}
void dwindow::append_table(std::string newtable){
    table = newtable;
}
void dwindow::clearlist(){
    ui->sumslist->clear();
}
void dwindow::clearnamedetails(){
    ui->tedit->clear();
    ui->details->clear();
    ui->diredit->clear();

}
std::vector<std::string> dwindow::get_text(){
    if(QDialog::exec()){
        is_showing = true;
        texts.clear();
        std::string text = ui->tedit->toPlainText().toStdString();
        std::string text_ = ui->details->toPlainText().toStdString();
        std::string text1 = ui->diredit->toPlainText().toStdString();


        texts.push_back(text);
        texts.push_back(text_);
        texts.push_back(text1);
        clearnamedetails();
        return texts;
    }}

void dwindow::on_buttonBox_rejected()
{
    reject();
}

