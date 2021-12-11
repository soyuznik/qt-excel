
#include <cstring>
#include <QtWidgets>
#include<QtCore>
#include<iostream>
#include<fstream>
#include <QApplication>
#include <cstdio>
#include<stdio.h>
#include <string>
#include <sstream>
#include <array>
#include<vector>
#include<string>
#include <windows.h>
#include <shellapi.h>
#include<thread>
#include <QFileInfoList>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <windows.h>
#include <stringapiset.h>
#include <unistd.h>
#include <condition_variable>
#include <mutex>
#include <errhandlingapi.h>
#include <processthreadsapi.h>

#define LOCALPATH "D:\\Visual Studio\\Projects\\WidgetApp\\projectdir"
#define TB "depozitdir\\.name.txt"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "measuringdialog.h"

using namespace std;
inline std::string GETGLOBALPATH()
{   char tmp[256];
    getcwd(tmp, 256);
    static std::string word = string(tmp) + string("\\");
    return word;
}




//util
inline bool exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
string space2underscore(string text)
{
    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] == ' ')
            text[i] = '_';
    }
    return text;
}
string underscore2space(string text)
{
    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] == '_')
            text[i] = ' ';
    }
    return text;
}
void RemoveWordFromLine(std::string &line, const std::string &word)
{

  auto n = line.find(word);
  if (n != std::string::npos )
  { try{
    line.erase(n, word.length());}catch(...){return;}
  }
}
//actions
void mainwindow::verify_integrity(){
    std::vector<string> appfiles = {    ".name.txt","adder.txt",  "deleter.txt", "name1.txt"
                                      ,"name10.txt", "name11.txt", "name12.txt", "name13.txt",   "name14.txt"
                                      , "name15.txt", "name16.txt", "name17.txt",   "name18.txt", "name19.txt", "name2.txt"
                                      , "name20.txt",   "name3.txt",  "name4.txt",  "name5.txt", "name6.txt",    "name7.txt"
                                      ,  "name8.txt",  "name9.txt"};

    string path1 = PATH + "projectdir";
    string path2 = PATH + "depozitdir";
    QDir dir(path1.c_str());
    if (!dir.exists())
        dir.mkpath(".");
    QDir dir0(path2.c_str());
    if (!dir0.exists())
        dir0.mkpath(".");




   for(int index0 = 0;index0 < (int)appfiles.size(); index0++){
       string abpath;

        abpath = PATH + string("depozitdir\\")+ string(appfiles[index0]);
        try{ofstream file(abpath, ofstream::app);file.close();}catch(...){continue;}}
  string apath = PATH + "depozitdir\\.name.txt";
   ofstream maketab(apath,ios::trunc);
   for(int i = 1;i<=20;i++){
       maketab << to_string(i) + "\n";
    }maketab.close();
}
void mainwindow::delete_item(){
    QTreeWidgetItem *itemfs = ui->list->itemAt(savepos);
    if(!itemfs){return;}

    itemfs->setText(0,"");itemfs->setText(1,"");itemfs->setText(2,"");itemfs->setText(3,"");


    delete itemfs;


}
void mainwindow::copy(){
    QTreeWidgetItem *itemfs = ui->list->itemAt(savepos);
    if(!itemfs){return;}
     ftext0 = itemfs->text(0);
    ftext1 = itemfs->text(1);
    ftext2 = itemfs->text(2);
    //QTreeWidgetItem *item = new QTreeWidgetItem();
    //item->setText(0,text0);
    //item->setText(1,text1);
    //item->setText(2,text2);
    //ui->list->addTopLevelItem(item);


}
void mainwindow::change_name(){
      QString tabname = QInputDialog::getText(this,"Dialog","Schimba Numele");
      buttonThatClickedUs->setText(tabname);


}
void mainwindow::tabMenu(QPoint pos){
    QMenu contextMenu(this);
    buttonThatClickedUs = qobject_cast<QPushButton*>(sender());
       QAction action("Schimba numele", this);
       savepos = pos;

        connect(&action, SIGNAL(triggered()),
                this, SLOT(change_name()));
        contextMenu.addAction(&action);
        contextMenu.exec(mapToGlobal(pos));

}
void mainwindow::show_dcol(){
    dcol->show();
    dcol->wait();
    ColumnNames.clear();
    ColumnNames << load_clmnlist();
    ui->list->setColumnCount(ColumnNames.size());
    ui->list->setHeaderLabels(ColumnNames);



}
void mainwindow::listMenu(QPoint pos){
try{
    QMenu contextMenu(this);
       QAction action("Elimina randul", this);
       QAction action1("Creaza rand nou", this);
       QAction action2("Copie randul", this);
       QAction action3("Schimba unitatea de masura", this);
       QAction action4("Adauga coloana",this);
      savepos = pos;
       connect(&action3, SIGNAL(triggered()),
               this, SLOT(changetab_name()));
       connect(&action, SIGNAL(triggered()),
               this, SLOT(delete_item()));
       connect(&action1, SIGNAL(triggered()),
               this, SLOT(newf()));
       connect(&action2, SIGNAL(triggered()),
               this, SLOT(copy()));
       connect(&action4, SIGNAL(triggered()),
               this, SLOT(show_dcol()));
       contextMenu.addAction(&action);
       contextMenu.addAction(&action1);
       contextMenu.addAction(&action2);
       contextMenu.addAction(&action4);
       contextMenu.addAction(&action3);
       contextMenu.exec(mapToGlobal(pos));
    }
catch(...){return;}
}
void mainwindow::newf()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->list);
    item->setText(0,ftext0);
    item->setText(1,ftext1);
    item->setText(2,ftext2);
    ftext0.clear();
    ftext1.clear();
    ftext2.clear();
    ui->list->addTopLevelItem(item);

}
void mainwindow::enableall(){
    previousitem = nullptr;
    for(int i = 0 ;i<20;i++){
        tabs[i]->setEnabled(true);
    }

}
void mainwindow::changetab_name(){
    measuringdialog *msdialog = new measuringdialog();
    QTreeWidgetItem *msitem = ui->list->itemAt(savepos);
    msdialog->set_name(msitem->text(0).toStdString());
    msdialog->set_price(msitem->text(1).toStdString());
    msdialog->set_quantity(msitem->text(3).toStdString());

    vector<string> msnamevector = msdialog->get_text();
    //append
    ms4price = msnamevector[0];
    ms4quantity = msnamevector[1];
    if(ms4price == ""){
        ms4price = " ";
    }
    if(ms4quantity == ""){
        ms4quantity = " ";
    }
    mscol1.push_back(ms4price);
    mscol2.push_back(ms4quantity);
    //save_mssystem();
    delete msdialog;



    msitem->setText(2,QString::fromStdString(ms4price));
    msitem->setText(4,QString::fromStdString(ms4quantity));
}


//save space
void mainwindow::saveCurrentStatus(){
    if(finishui == false){return;}
    nr_of_saves++;
    saveCurrentConfig(PATH+"savestatus\\itemsav"+to_string(nr_of_saves)+".txt");
cache_stoarge.push_back(PATH+"savestatus\\itemsav"+to_string(nr_of_saves)+".txt");}
void mainwindow::saveCurrentTabsConfig(string nabsPath){
    string texts;
    ofstream inFile;

    inFile.open(PATH + nabsPath, std::ofstream::out | std::ofstream::trunc);

    for(int  nr = 0 ; nr <20 ; nr++){if(tabs[nr]->text().isEmpty() == true){tabs[nr]->setText("  ");}
        texts = space2underscore(tabs[nr]->text().toStdString()) + "\n";
        inFile << texts;}
    inFile.close();
}
void mainwindow::saveCurrentConfig(string location){
   QList<QTreeWidgetItem*> items = ui->list->findItems(QString(""), Qt::MatchContains);
    string texts;

    foreach(QTreeWidgetItem *item, items){

        for(int  nr = 0 ; nr <=columncount ; nr++){if(item->text(nr).isEmpty() == true){item->setText( nr ,"  ");}}
        for(int  nr = 0 ; nr <=columncount ; nr++){
        texts = texts + space2underscore(item->text(nr).toStdString()) + "  ";}
        texts = texts + "\n";


    }
    fstream inFile;
    inFile.open(location, std::ofstream::out | std::ofstream::trunc);
    inFile.clear();

    inFile << texts;
    inFile.close();


}
void mainwindow::saveall(){
  string number = to_string(last);
  saveCurrentConfig(currentopened);
  saveCurrentStatus();



}
void mainwindow::clear_cache(){
    for(int i = 0 ;i<(int)cache_stoarge.size();i++){
       remove(cache_stoarge[i].c_str());
    }
}



//save columns space
void mainwindow::remove_column(string name){
    fstream filesave(PATH+"depozitdir\\saveclmn.txt");
    string ch;
    string file_contents;
    while(std::getline(filesave,ch)){
        file_contents = file_contents + ch + "\n";
    }
    filesave.close();
    RemoveWordFromLine(file_contents,name);
    ofstream ofilesave(PATH+"depozitdir\\saveclmn.txt");
    ofilesave << file_contents;
    ofilesave.close();
    ColumnNames.clear();
    ColumnNames << load_clmnlist();
    ui->list->setHeaderLabels(ColumnNames);

}
void mainwindow::create_column(string name){
   ofstream filesave(PATH+"depozitdir\\saveclmn.txt", ios::app);
   filesave << name + "\n";
   filesave.close();
   ColumnNames.clear();
   ColumnNames << load_clmnlist();
   ui->list->setHeaderLabels(ColumnNames);



}
QStringList mainwindow::load_clmnlist(){
    list<string> textlist;
    textlist.clear();
    QStringList qtextlist;
    string text;
    columncount = 0;
    ifstream filesave(PATH+"depozitdir\\saveclmn.txt");
    while (std::getline(filesave,text))
    {textlist.push_back(text);}
    for(string str : textlist){
        columncount++;
        qtextlist.append(QString::fromStdString(str));
    }
    return qtextlist;
}
void mainwindow::save_clmnlist(){
    ofstream filesave(PATH+"depozitdir\\saveclmn.txt");
    vector<string> namevec;
    for(QString name : ColumnNames){
        string strname = name.toStdString();
        namevec.push_back(strname);
    }
    for(string name : namevec){
        filesave << name + "\n";
    }
    filesave.close();}


//init space
void mainwindow::init_measuringdialog(){


}
void mainwindow::reload(){
   tabs.push_back(ui->p1);
   tabs.push_back(ui->p2);
   tabs.push_back(ui->p3);
   tabs.push_back(ui->p4);
   tabs.push_back(ui->p5);
   tabs.push_back(ui->p6);
   tabs.push_back(ui->p7);
   tabs.push_back(ui->p8);
   tabs.push_back(ui->p9);
   tabs.push_back(ui->p10);
   tabs.push_back(ui->p11);
   tabs.push_back(ui->p12);
   tabs.push_back(ui->p13);
   tabs.push_back(ui->p14);
   tabs.push_back(ui->p15);
   tabs.push_back(ui->p16);
   tabs.push_back(ui->p17);
   tabs.push_back(ui->p18);
   tabs.push_back(ui->p19);
   tabs.push_back(ui->p20);

   fstream inFile(PATH + string("depozitdir\\.name.txt"));
   std::vector<string> text;

   while(!inFile.eof()){

       string tx;
       inFile >> tx;

       text.push_back(tx);
   }

   for(int i = 0 ;i<20;i++){
       tabs[i]->hide();
       string _tout = text[i];
       QString text = QString::fromStdString(_tout);
       tabs[i]->setText(text);
       tabs[i]->setContextMenuPolicy(Qt::CustomContextMenu);
       connect(tabs[i], SIGNAL(customContextMenuRequested(QPoint)),
               this, SLOT(tabMenu(QPoint)));
   }
   tabs[0]->show();


}
mainwindow::mainwindow(bool init_ui ,QWidget *parent  ): QMainWindow(parent), ui(new Ui::mainwindow){
    if(init_ui == true){
    verify_integrity();
    ui->setupUi(this);




    // hiding lost shit lmao
    ui->add->hide();
    ui->refresh->hide();
    ui->make_doc->hide();
    ui->project->hide();
    ui->import_2->hide();
    ui->show->hide();
    ui->show_dia->hide();
    //projectlist entry
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    string path = PATH + "projectdir";
    dirModel->setRootPath(path.c_str());

    ui->projectlist->setModel(dirModel);
    ui->projectlist->hideColumn(1);
    ui->projectlist->hideColumn(2);
    ui->projectlist->hideColumn(3);
    ui->projectlist->setRootIndex(dirModel->index(path.c_str()));
    ui->projectlist->expandToDepth(3);

    connect(ui->projectlist, &QTreeView::clicked, this, &mainwindow::dirItemClicked);



    reload();//crash

    ui->add_butt->setFixedWidth(30);

    ui->list->setAutoScroll(false);

    ColumnNames << load_clmnlist();
    save_clmnlist();
    ui->projectlist->setFont(QFont("Segoe UI" , 10));
    ui->list->setHeaderLabels(ColumnNames);

    ui->list->setStyleSheet("QTreeWidget::item:!selected "
    "{ "
      "border: 1px solid gainsboro; "
      "border-left: none; "
      "border-top: none; "
    "}"
    "QTreeWidget::item:selected {}");//; border-right: 1px solid gray;border-left: 1px solid gray;border-upper: 1px solid gray;});

    ui->list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->list, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(listMenu(QPoint)));
    ui->project->setStyleSheet("background-color: white");
    ui->import_2->setStyleSheet("background-color: white");
    ui->make_doc->setEnabled(false);
    ui->actionCalculeaza->setEnabled(false);
    ui->show->setStyleSheet("background-color: gainsboro");
    ui->projectlist->hide();

    on_p1_clicked();
    finishui = true;
    refresh_projectlist();



    }}
mainwindow::~mainwindow(){

    saveCurrentTabsConfig(TB);
    saveall();
    clear_cache();
    delete ui;
    delete dirModel;
    delete itemfs;
}




// refresh space

void mainwindow::refresh_projectlist(){

}
void mainwindow::display(string path){
    /* methe*/
    string text;
    std::list<string> qtextlist = {};
    ui->list->clear();
    currentopened = path;


    fstream inFile(path);

    //more meth}
    while (std::getline(inFile,text))
    {qtextlist.push_back(text);}
        for (string str : qtextlist) {
            /* meth*/
            QTreeWidgetItem *item = new QTreeWidgetItem;
            if(str == ""){str = "_";}
            std::stringstream ss(str);
            string buf;
            std::vector<std::string> tokens;
            for(int nr = 0 ; nr < 5 ; nr++){item->setBackground(nr,Qt::white);}
            while (ss >> buf)
                    tokens.push_back(buf);
            repeat_addition:
            if(columncount > (int)tokens.size()){
                tokens.push_back("_");
                goto repeat_addition;
            }
            for(int i=0 ; i <= columncount ; i++){
                string mstr;
                try{mstr = underscore2space(tokens[i]);}catch(...){mstr = "  ";}
                QString qstr = QString::fromStdString(mstr);
                item->setText(i,qstr);

            }
            ui->list->addTopLevelItem(item);}
                 inFile.close();
}
void mainwindow::undo_status(){
    //nr_of_saves
    //undoClicks ++;

    int currentSaveIndex = nr_of_saves-undoClicks;
    if(currentSaveIndex<1){return;}
    display(PATH + "savestatus\\itemsav"+to_string(currentSaveIndex)+".txt");

}
void mainwindow::make_projectsave(){
    ofstream ofFile(PATH + string("depozitdir\\info.txt"));
    string line;


    int rows = (int)projecttokens.size() / columncount;
    //checking if we need a more row or not

    int row = 1;
    int column_ = 0;


    for(int nr = 0;nr<(int)projecttokens.size();nr++){
        if(column_==columncount){row++;column_ = 1;}
        else{column_++;}
        int index = row * columncount + column_ - columncount - 1;
        if(projecttokens[index] != "__"){line = projecttokens[index];
        ofFile << space2underscore(line) + "  ";}
        if(space2underscore(projecttokens[index]) == "__"){ofFile << "\n";}
    }



    string dirname = std::string(namevector[2]);
    string name = std::string(namevector[0]);
    namevector.clear();
    ofFile<< "=filename->" +name+"\n";
    ofFile<< "=dir->" +dirname+"\n";
    ofFile.close();
    string path = PATH + "makesave.pyw";
    ShellExecuteA(NULL,"open",path.c_str(),NULL,NULL,SW_SHOW);// NOW DOES work
    scazator.clear();
    descazut.clear();


}
void mainwindow::make_dialoglisttext(){
    //clearing the list
    dialog->clearlist();
    string line;
    int row = 1;
    int column_ = 0;
    //string nonnewline = column1[nr]+"    "+ column2[nr]+ "    "+ scazator[nr] + "  →  " + to_string(sum);

    for(int nr = 0;nr<(int)projecttokens.size();nr++){
        if(column_==columncount){row++;column_ = 1;}
        else{column_++;}
        int index = row * columncount + column_ - columncount - 1;
        if(projecttokens[index] != "__"){
            line = line + "  "  +projecttokens[index];}
        if(space2underscore(projecttokens[index]) == "__"){dialog->add_line(line);line.clear();}
    }

}
void mainwindow::make_calc(){
    int sec , res;
    for (int nr = 0;nr<(int)descazut.size() ;nr++ ) {
        //setting sec value
        if(nr<(int)scazator.size()){
        try {sec = stoi(scazator[nr]);}catch (std::invalid_argument){sec = 0;}}

        //adding or subtracting the integers depending on the call
        if(call == "deleter"){res = stoi(descazut[nr]) - sec;}
        else if(call == "adder"){res = stoi(descazut[nr]) + sec;}
        else{sec = 0;}
        //appending the result
        result.push_back(res);}
    //displaying the result
    display_vector();
}
void mainwindow::format_text(string location){
    projecttokens.clear();
    string text;
    int qindex = 0;

    std::list<string> qtextlist = {};
    fstream inFile(location);

    while (std::getline(inFile,text))
    {qtextlist.push_back(text);}
        for (string str : qtextlist) {

            qindex++;
            if(str == ""){str = "  ";}




            std::istringstream ss(str);
            string buf;

            while(ss >> buf){
                projecttokens.push_back(buf);
            }
            //column vector sorting
            // formatting the strings
            int index = qindex * columncount + projectcolumn - columncount;
            if(location == PATH + string("depozitdir\\deleter.txt")
            || location == PATH + string("depozitdir\\adder.txt"))
            {scazator.push_back(projecttokens[index]);}
            else{descazut.push_back(projecttokens[index]);}

        }
        result.clear();

}
void mainwindow::display_vector(){
    //result

    QList<QTreeWidgetItem*> itemsf = ui->list->findItems(QString(""), Qt::MatchContains);
    int nr = 0;
       foreach(QTreeWidgetItem *itemf, itemsf){
            QString str = QString::number(result[nr]);
            if(nr>(int)result.size()){break;}
            nr++;
            itemf->setText(projectcolumn , str);}
}




//slots

void mainwindow::dirItemClicked(const QModelIndex &index){
    Q_ASSERT(index.isValid());

    QString path = dirModel->filePath(index);
    string s_path = path.toStdString();
    QFileInfo qtpath(path);
    if(qtpath.isFile()){

        ShellExecuteA(NULL,"open",s_path.c_str(),NULL,NULL, SW_HIDE );

    }



}
void mainwindow::on_list_itemClicked(QTreeWidgetItem *item)
{
    if (deleteItems == true){delete item;}
    else{
        Qt::ItemFlags tmp = item->flags();

        item->setFlags(tmp | Qt::ItemIsEditable);

            }
    }
void mainwindow::on_add_clicked()
{

    newf();

}
void mainwindow::on_project_clicked(){
if(timesy == 0 && project_perm == true) {

        timesy = 1;
        import_perm = false;
        ui->project->setStyleSheet("background-color: green");
        ProjectMode = true;

        saveall();
        QList<QTreeWidgetItem*> itemsf = ui->list->findItems(QString(""), Qt::MatchContains);

        if(ProjectMode == true){
        foreach(QTreeWidgetItem *itemf, itemsf)
            for(int nr = 3;nr<4;nr++){
                itemf->setText(nr , "0");}}}
else if(timesy == 1) {
    import_perm = true;

          saveCurrentConfig(PATH + string("depozitdir\\deleter.txt"));
          call = "deleter";
        timesy = 0;
        ui->project->setStyleSheet("background-color: white");
        ProjectMode = false;
        display(PATH +"depozitdir\\name" + to_string(last) + ".txt");

        saveall();
ui->actionCalculeaza->setEnabled(true);}}
void mainwindow::on_make_doc_clicked()//clearing vector and textedits
{   dialog->clearnamedetails();

    //
    format_text(currentopened);


    if(call == "deleter"){
    format_text(PATH + string("depozitdir\\deleter.txt"));}
    else if(call == "adder"){format_text(PATH + string("depozitdir\\adder.txt"));}
    //ui->make_doc->setEnabled(false);
    ui->actionCalculeaza->setEnabled(false);
    make_calc();
    make_dialoglisttext();
    namevector = dialog->get_text();
    make_projectsave();


}
void mainwindow::on_show_clicked(){
static int times = 0;

if(times == 0){times = 1;ui->projectlist->show();ui->show->setStyleSheet("background-color: white");}
else if(times == 1){times = 0;ui->projectlist->hide();ui->show->setStyleSheet("background-color: gainsboro");}}





void mainwindow::on_projectlist_itemDoubleClicked(QListWidgetItem *item)//trash
{
    string text = item->text().toStdString();
    text = PATH + string("projectdir\\"+text+".xlsx");



    //system("cd D:\\Visual Studio\\Projects\\WidgetApp & start exec.pyw");

    ShellExecuteA(NULL,"open",text.c_str(),NULL,NULL, SW_HIDE );
}
void mainwindow::on_show_dia_clicked()
{
    saveall();
}
void mainwindow::on_p1_clicked(){saveall();last = 1;display(PATH +"depozitdir\\name1.txt");enableall();ui->p1->setEnabled(false);}//gotta add to save
void mainwindow::on_p2_clicked(){saveall();last = 2;display(PATH +"depozitdir\\name2.txt");enableall();ui->p2->setEnabled(false);}
void mainwindow::on_p3_clicked(){saveall();last = 3;display(PATH +"depozitdir\\name3.txt");enableall();ui->p3->setEnabled(false);}
void mainwindow::on_p4_clicked(){saveall();last = 4;display(PATH +"depozitdir\\name4.txt");enableall();ui->p4->setEnabled(false);}
void mainwindow::on_p5_clicked(){saveall();last = 5;display(PATH +"depozitdir\\name5.txt");enableall();ui->p5->setEnabled(false);}
void mainwindow::on_p6_clicked(){saveall();last = 6;display(PATH +"depozitdir\\name6.txt");enableall();ui->p6->setEnabled(false);}
void mainwindow::on_p7_clicked(){saveall();last = 7;display(PATH +"depozitdir\\name7.txt");enableall();ui->p7->setEnabled(false);    }
void mainwindow::on_p8_clicked(){saveall();last = 8;display(PATH +"depozitdir\\name8.txt");enableall(); ui->p8->setEnabled(false);  }
void mainwindow::on_p9_clicked(){saveall();last = 9; display(PATH +"depozitdir\\name9.txt");enableall();ui->p9->setEnabled(false);  }
void mainwindow::on_p10_clicked(){saveall();last = 10;  display(PATH +"depozitdir\\name10.txt");enableall();ui->p10->setEnabled(false);  }
void mainwindow::on_p11_clicked(){saveall();last = 11; display(PATH +"depozitdir\\name11.txt"); enableall();ui->p11->setEnabled(false);  }
void mainwindow::on_p12_clicked(){saveall();last = 12;  display(PATH +"depozitdir\\name12.txt");enableall();ui->p12->setEnabled(false);  }
void mainwindow::on_p13_clicked(){saveall();last = 13;display(PATH +"depozitdir\\name13.txt");enableall();ui->p13->setEnabled(false); }
void mainwindow::on_p14_clicked(){saveall();last = 14;display(PATH +"depozitdir\\name14.txt"); enableall();ui->p14->setEnabled(false);   }
void mainwindow::on_p15_clicked(){saveall();last = 15;display(PATH +"depozitdir\\name15.txt");enableall();ui->p15->setEnabled(false);  }
void mainwindow::on_p16_clicked(){saveall();last = 16;display(PATH +"depozitdir\\name16.txt"); enableall(); ui->p16->setEnabled(false); }
void mainwindow::on_p17_clicked(){saveall();last = 17; display(PATH +"depozitdir\\name17.txt"); enableall(); ui->p17->setEnabled(false); }
void mainwindow::on_p18_clicked(){saveall();last = 18;display(PATH +"depozitdir\\name18.txt"); enableall();  ui->p18->setEnabled(false); }
void mainwindow::on_p19_clicked(){saveall();last = 19;display(PATH +"depozitdir\\name19.txt"); enableall();ui->p19->setEnabled(false);   }
void mainwindow::on_p20_clicked(){saveall();last = 20;display(PATH +"depozitdir\\name20.txt");enableall();   ui->p20->setEnabled(false); }



void mainwindow::on_add_butt_clicked()
{static int opened = 1;

    static bool reverse;
    if(opened ==20){
        reverse = true;ui->add_butt->setText("--");

       }
    else if (opened == 1){reverse = false;ui->add_butt->setText("++");}
    if(reverse == true){tabs[opened]->hide();opened--;}
    else if(reverse == false){tabs[opened]->show();opened++;}



}
void mainwindow::on_import_2_clicked()
{
    if(timesz == 0 && import_perm == true){
            timesz = 1;
            ui->import_2->setStyleSheet("background-color: green");
            ImportMode = true;
            project_perm = false;
            saveall();
            QList<QTreeWidgetItem*> itemsf = ui->list->findItems(QString(""), Qt::MatchContains);

            foreach(QTreeWidgetItem *itemf, itemsf)
                for(int nr = 3;nr<4;nr++){
                    itemf->setText(nr , "0");}}
    else if(timesz == 1) {
            saveCurrentConfig(PATH + string("depozitdir\\adder.txt"));
            call = "adder";
            timesz = 0;
            ui->import_2->setStyleSheet("background-color: white");
            ImportMode = false;
            ui->actionCalculeaza->setEnabled(true);
            display(PATH+"depozitdir\\name" + to_string(last) + ".txt");
            saveall();
    project_perm = true;}
}

void mainwindow::on_actionNou_triggered()
{
    newf();
}
void mainwindow::on_actionElimina_triggered()
{
    if (timesf ==0){timesf = 1;deleteItems = true;}
    else if (timesf = 1){timesf = 0;deleteItems = false;}
}
void mainwindow::on_actionImporteaza_triggered(){

    static int toolcount = 0;
    if(toolcount==0){toolcount=1;ui->actionElimina->setEnabled(false);}
    else if(toolcount==1){toolcount=0;ui->actionElimina->setEnabled(true);}
    on_import_2_clicked();
}
void mainwindow::on_actionProiect_triggered()
{
    static int toolcount1 = 0;
    if(toolcount1==0){toolcount1=1;ui->actionElimina->setEnabled(false);}
    else if(toolcount1==1){toolcount1=0;ui->actionElimina->setEnabled(true);}
     on_project_clicked();
}
void mainwindow::on_actionCalculeaza_triggered()
{
     on_make_doc_clicked();
}
void mainwindow::on_actionArata_Proiectele_triggered()
{
      on_show_clicked();
}
void mainwindow::on_actionSalvare_Rapida_triggered()
{
    saveall();
}
void mainwindow::on_actionUndo_triggered()
{
   undo_status();
}


void mainwindow::on_actionAdauga_Coloana_triggered()
{
    create_column(" new");
}

