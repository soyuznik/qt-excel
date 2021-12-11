#ifndef DCOLUMN_H
#define DCOLUMN_H

#include <QDialog>

namespace Ui {
class dcolumn;
}

class dcolumn : public QDialog
{
    Q_OBJECT

public:
    explicit dcolumn(std::string path , QWidget *parent = nullptr);
    ~dcolumn();
    void editcol();
    void addcol();
    void wait();
    std::string filetext;

private slots:
    void on_editb_clicked();

    void on_addb_clicked();

private:
    std::string PATH;
    Ui::dcolumn *ui;
};

#endif // DCOLUMN_H
