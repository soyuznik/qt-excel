#ifndef DWINDOW_H
#define DWINDOW_H

#include <QDialog>


namespace Ui {
class dwindow;

}

class dwindow : public QDialog
{
    Q_OBJECT

public:
    explicit dwindow(QWidget *parent = nullptr);
    ~dwindow();
    std::string table;
    void append_table(std::string newtable);
    std::vector<std::string> texts = {};
    std::vector<std::string> get_text();

    bool is_showing = false;
    void reject();
    void updatelist();
    void clearlist();
    void clearnamedetails();
    void add_line(const std::string &line);



private slots:
    void on_buttonBox_rejected();

private:
    Ui::dwindow *ui;
};

#endif // DWINDOW_H
