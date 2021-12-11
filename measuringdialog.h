#ifndef MEASURINGDIALOG_H
#define MEASURINGDIALOG_H

#include <QDialog>

namespace Ui {
class measuringdialog;
}

class measuringdialog : public QDialog
{
    Q_OBJECT

public:
    explicit measuringdialog(QWidget *parent = nullptr);
    ~measuringdialog();
    std::vector<std::string> get_text();


    void set_name(std::string name);
    void set_price(std::string price);
    void set_quantity(std::string quantity);

private:
    bool showing = false;
    Ui::measuringdialog *ui;
};

#endif // MEASURINGDIALOG_H
