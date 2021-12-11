#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTreeWidgetItem>
#include <vector>
#include "dwindow.h"
#include "dcolumn.h"
#include <string>
#include <QFileSystemModel>
#include <thread>
QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:

    mainwindow(bool init_ui,QWidget *parent = nullptr);
    ~mainwindow();
    void undo_status();
    QPushButton *buttonThatClickedUs;
    std::vector<std::string> cache_stoarge;



    int projectcolumn = 3;
    int undoClicks = 0;
    bool finishui = false;
    QTreeWidgetItem *previousitem = nullptr;
    QTreeWidgetItem *lastselected;
    std::vector<std::string> mscol1;
    std::vector<std::string> mscol2;
    std::string ms4price;
    std::string ms4quantity;

    int times = 0;
    int timesf = 0;
    int timesy = 0;
    int timesz = 0;
    bool ProjectMode = false;
    bool ImportMode = false;
    bool import_perm = true;
    bool project_perm = true;
    std::string call;
    std::string mode;
    int nr_of_saves = 0;

    std::string PATH = "D:\\Visual Studio\\Projects\\WidgetApp\\";


    std::vector<std::string> descazut;
    std::vector<std::string> scazator;
    std::vector<std::string> projecttokens;
    std::vector<std::vector<std::string>*> column;

    std::vector<int> result;
    std::vector<float> sums;
    std::vector<QPushButton*> tabs;
    bool deleteItems = false;
    std::string dialogText;
    dwindow *dialog = new dwindow(this);
    dcolumn *dcol = new dcolumn(PATH + "depozitdir\\saveclmn.txt");

    QPoint savepos;

    QString ftext0 ,ftext1,ftext2;
    std::string detail_text;
    QTreeWidgetItem *itemfs = new QTreeWidgetItem;
    std::string save_deposit;
    std::string path;
    int last;
    std::string currentopened;
    std::string currentpath;
    std::string showing;
    std::vector<std::string> namevector = {};
    std::string dir;
    char* textarray1;
    QStringList ColumnNames;
    std::vector<std::string> strColumn;
    int columncount;
    QFileSystemModel *dirModel;




private slots:
//save list columns
    void show_dcol();
    void create_column(std::string name);
    void remove_column(std::string name);
    QStringList load_clmnlist();
    void save_clmnlist();


    void clear_cache();
    void change_name();
    void init_measuringdialog();
    void verify_integrity();
    void on_list_itemClicked(QTreeWidgetItem *item);
    void reload();

    void saveCurrentTabsConfig(std::string nabsPath);
    void display(std::string path);
    void delete_item();
    void on_add_clicked();


    void refresh_projectlist();
    void make_projectsave();
    void make_dialoglisttext();
    void enableall();
    void saveall();


    void changetab_name();
    void dirItemClicked(const QModelIndex &index);




void newf();
    void on_project_clicked();
    void format_text(std::string location);

    void make_calc();

    void display_vector();
void copy();
    void on_make_doc_clicked();

    void on_show_clicked();




    void on_projectlist_itemDoubleClicked(QListWidgetItem *item);
    void listMenu(QPoint pos );
    void tabMenu(QPoint pos );




    void on_show_dia_clicked();

    void saveCurrentStatus();






    void on_p2_clicked();

    void on_p1_clicked();

    void on_p3_clicked();

    void on_p4_clicked();

    void on_p5_clicked();

    void on_p6_clicked();

    void on_p7_clicked();

    void on_p8_clicked();

    void on_p9_clicked();

    void on_p10_clicked();

    void on_p11_clicked();

    void on_p12_clicked();

    void on_p13_clicked();

    void on_p14_clicked();

    void on_p15_clicked();

    void on_p16_clicked();

    void on_p17_clicked();

    void on_p18_clicked();

    void on_p19_clicked();

    void on_p20_clicked();

    void on_add_butt_clicked();

    void on_import_2_clicked();

    void on_actionNou_triggered();

    void on_actionElimina_triggered();

    void on_actionImporteaza_triggered();

    void on_actionProiect_triggered();

    void on_actionCalculeaza_triggered();

    void on_actionArata_Proiectele_triggered();

    void on_actionSalvare_Rapida_triggered();

    void on_actionUndo_triggered();

    void on_actionAdauga_Coloana_triggered();

private:

    void saveCurrentConfig(std::string location);
    void format_list();

private:
    Ui::mainwindow *ui;

};
#endif // MAINWINDOW_H
