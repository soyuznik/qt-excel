
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


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "measuringdialog.h"

using namespace std;






// refresh space
void mainwindow::refresh_projectlist(){

}
void mainwindow::default_refresh(bool mode){// true makes the button enabled , false not
    switch(mode){
    case true:{timesf = 0;deleteItems = false;ui->refresh->setStyleSheet("background-color: white");ui->refresh->setEnabled(true);break;}
    case false:{timesf = 0;deleteItems = false;ui->refresh->setStyleSheet("background-color: white");ui->refresh->setEnabled(false);break;}
    }}
void mainwindow::display(string path){
    /* getting text from a file and adding it to the list --> datacache*/
    string text;
    std::list<string> qtextlist = {};
    ui->list->clear();
    currentopened = path;

    string mainpath = PATH + string("depozitdir\\");
    fstream inFile(mainpath + path);



    //while (inFile >> text) {qtextlist.push_back(text);}
    while (std::getline(inFile,text))
    {qtextlist.push_back(text);}
        for (string str : qtextlist) {
            /* this for loop adds things from my_list into the Qlistwidget*/

            std::string str1, str2 , str3 , str4 , str5;
            std::istringstream s(str);
            s>>str1;
            s>>str2;
            s>>str3;
            s>>str4;
            s>>str5;





            QTreeWidgetItem *item = new QTreeWidgetItem;
            for(int nr = 0 ; nr < 5 ; nr++){item->setBackground(nr,Qt::white);}
            // formatting the strings

            str1 = underscore2space(str1);
            str2 = underscore2space(str2);
            str3 = underscore2space(str3);
            str4 = underscore2space(str4);
            str5 = underscore2space(str5);



            QString qstr = QString::fromStdString(str1);
            QString qstr2 = QString::fromStdString(str2);
            QString qstr3 = QString::fromStdString(str3);
            QString qstr4 = QString::fromStdString(str4);
            QString qstr5 = QString::fromStdString(str5);
            item->setText(0,qstr);
            item->setText(1,qstr2);
            item->setText(2,qstr3);
            item->setText(3,qstr4);
            item->setText(4,qstr5);




             ui->list->addTopLevelItem(item);};

             ui->list->resizeColumnToContents(2);
             ui->list->resizeColumnToContents(4);
        inFile.close();

}
void mainwindow::default_refresh_(bool mode){// true makes the button enabled , false not
    switch(mode){
    case true:{timesf = 0;deleteItems = false;ui->refresh->setStyleSheet("background-color: white");ui->refresh->setEnabled(true);break;}
    case false:{timesf = 0;deleteItems = false;ui->refresh->setStyleSheet("background-color: white");ui->refresh->setEnabled(false);break;}
    }}


//save space
void mainwindow::saveCurrentTabsConfig(){
    string texts;
    ofstream inFile;
    inFile.open(PATH + string("depozitdir\\.name.txt"), std::ofstream::out | std::ofstream::trunc);



    for(int  nr = 0 ; nr <20 ; nr++){if(tabs[nr]->text().isEmpty() == true){tabs[nr]->setText("  ");}
        texts = space2underscore(tabs[nr]->text().toStdString()) + "\n";
        inFile << texts;}
    inFile.close();
}
void mainwindow::saveCurrentConfig(string location){
   QList<QTreeWidgetItem*> items = ui->list->findItems(QString(""), Qt::MatchContains);
    string texts;

    foreach(QTreeWidgetItem *item, items){


        /* aici trebuie sa fac de pe stackoverflow si sa adaug sa faca din " " in "-" ca sa poata da split pe coloane*/
        for(int  nr = 0 ; nr <4 ; nr++){if(item->text(nr).isEmpty() == true){item->setText( nr ,"  ");}}
        texts = texts + space2underscore(item->text(0).toStdString()) + "  "+ space2underscore(item->text(1).toStdString())
                + "  " + space2underscore(item->text(2).toStdString()) + "  " + space2underscore(item->text(3).toStdString())
                + "  " + space2underscore(item->text(4).toStdString()) +"\n";}
    fstream inFile;
    inFile.open(location, std::ofstream::out | std::ofstream::trunc);
    inFile.clear();

    inFile << texts;
    inFile.close();


}
void mainwindow::saveall(){

  string number;
  number = to_string(last);
  currentpath = PATH +string("depozitdir\\") + currentopened;

  saveCurrentConfig(currentpath);

}




void mainwindow::make_projectsave(){
    ofstream ofFile(PATH + string("depozitdir\\info.txt"));
    string line;


    for(int nr = 0;nr<scazator.size();nr++){

        line = column1[nr] +"  "+ column2[nr] +"  "+ column3[nr] + "  "+ scazator[nr] +"  "+ column4[nr] + "\n";
        ofFile<<line;}


    string dirname = std::string(namevector[2]);
    string name = std::string(namevector[0]);
    namevector.clear();
    ofFile<< "=filename->" +name+"\n";
    ofFile<< "=dir->" +dirname+"\n";
    ofFile.close();
    string path = PATH + "makesave.pyw";
    ShellExecuteA(NULL,"open",path.c_str(),NULL,NULL,SW_SHOW);// doesnt work


}
void mainwindow::make_dialoglisttext(){
    dialog->clearlist();
    float totalsum;
    for(int nr = 0;nr<scazator.size();nr++){
        float fir,sec;
        try{
           fir = stoi(column2[nr]);
           sec = stoi(scazator[nr]);}
        catch(std::invalid_argument){break;}

        float sum = fir * sec;
        totalsum = totalsum + sum;
        string nonnewline = column1[nr]+"    "+ column2[nr]+ "    "+ scazator[nr] + "  →  " + to_string(sum);
        dialog->append_table(nonnewline);
        dialog->updatelist();
        }
    dialog->append_table("__________________________________________________________________________________________________________");
    dialog->updatelist();
    dialog->append_table("In total:                                    "+ to_string(totalsum) + " lei");
    dialog->updatelist();

    }
void mainwindow::make_calc(){
    int sec , res;
    for (int nr = 0;nr<descazut.size() ;nr++ ) {

        if(nr<scazator.size()){
            try {sec = stoi(scazator[nr]);

            }  catch (std::invalid_argument) {sec = 0;}

            }
        ////////////////////////
        if(call == "deleter"){
               res = stoi(descazut[nr]) - sec;}// crash??
        else if(call == "adder"){res = stoi(descazut[nr]) + sec;}
        else{ sec = 0;}

        result.push_back(res);}
    display_vector();
}
void mainwindow::format_text(string location){
    string text;
    column1.clear();
    column2.clear();
    column3.clear();
    column4.clear();
    std::list<string> qtextlist = {};
    fstream inFile(location);
    //while (inFile >> text) {qtextlist.push_back(text);}
    while (std::getline(inFile,text))
    {qtextlist.push_back(text);}
        for (string str : qtextlist) {
            /* this for loop adds things from my_list into the Qlistwidget*/

            std::string t_str1,t_str2,t_str3,t_str4,t_str5;


            std::istringstream s(str);
            s>>t_str1;
            s>>t_str2;
            s>>t_str3;
            s>>t_str4;
            s>>t_str5;
            column1.push_back(t_str1);
            column2.push_back(t_str2);
            column3.push_back(t_str3);
            column4.push_back(t_str5);
            // formatting the strings

            if(location == PATH + string("depozitdir\\deleter.txt")
                    || location == PATH + string("depozitdir\\adder.txt"))

            {scazator.push_back(t_str4);}
            else{descazut.push_back(t_str4);}
        }
        result.clear();

}
void mainwindow::display_vector(){
    //result
    QList<QTreeWidgetItem*> itemsf = ui->list->findItems(QString(""), Qt::MatchContains);
    int nr = 0;



        foreach(QTreeWidgetItem *itemf, itemsf){

            QString str = QString::number(result[nr]);
            if(nr>result.size()){break;}
            nr++;
            itemf->setText(3 , str);


        }}






//slots



void mainwindow::on_p1_clicked(){saveall();last = 1;display("name1.txt");enableall();ui->p1->setEnabled(false);}//gotta add to save
void mainwindow::on_p2_clicked(){saveall();last = 2;display("name2.txt");enableall();ui->p2->setEnabled(false);}
void mainwindow::on_p3_clicked(){saveall();last = 3;display("name3.txt");enableall();ui->p3->setEnabled(false);}
void mainwindow::on_p4_clicked(){saveall();last = 4;display("name4.txt");enableall();ui->p4->setEnabled(false);}
void mainwindow::on_p5_clicked(){saveall();last = 5;display("name5.txt");enableall();ui->p5->setEnabled(false);}
void mainwindow::on_p6_clicked(){saveall();last = 6;display("name6.txt");enableall();ui->p6->setEnabled(false);}
void mainwindow::on_p7_clicked(){saveall();last = 7;display("name7.txt");enableall();ui->p7->setEnabled(false);    }
void mainwindow::on_p8_clicked(){saveall();last = 8;display("name8.txt");enableall(); ui->p8->setEnabled(false);  }
void mainwindow::on_p9_clicked(){saveall();last = 9; display("name9.txt");enableall();ui->p9->setEnabled(false);  }
void mainwindow::on_p10_clicked(){saveall();last = 10;  display("name10.txt");enableall();ui->p10->setEnabled(false);  }
void mainwindow::on_p11_clicked(){saveall();last = 11; display("name11.txt"); enableall();ui->p11->setEnabled(false);  }
void mainwindow::on_p12_clicked(){saveall();last = 12;  display("name12.txt");enableall();ui->p12->setEnabled(false);  }
void mainwindow::on_p13_clicked(){saveall();last = 13;display("name13.txt");enableall();ui->p13->setEnabled(false); }
void mainwindow::on_p14_clicked(){saveall();last = 14;display("name14.txt"); enableall();ui->p14->setEnabled(false);   }
void mainwindow::on_p15_clicked(){saveall();last = 15;display("name15.txt");enableall();ui->p15->setEnabled(false);  }
void mainwindow::on_p16_clicked(){saveall();last = 16;display("name16.txt"); enableall(); ui->p16->setEnabled(false); }
void mainwindow::on_p17_clicked(){saveall();last = 17; display("name17.txt"); enableall(); ui->p17->setEnabled(false); }
void mainwindow::on_p18_clicked(){saveall();last = 18;display("name18.txt"); enableall();  ui->p18->setEnabled(false); }
void mainwindow::on_p19_clicked(){saveall();last = 19;display("name19.txt"); enableall();ui->p19->setEnabled(false);   }
void mainwindow::on_p20_clicked(){saveall();last = 20;display("name20.txt");enableall();   ui->p20->setEnabled(false); }










