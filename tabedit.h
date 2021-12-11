#ifndef TABEDIT_H
#define TABEDIT_H

#include <QDialog>

namespace Ui {
class tabedit;
}

class tabedit : public QDialog
{
    Q_OBJECT

public:
    explicit tabedit(QWidget *parent = nullptr);
    ~tabedit();

private:
    Ui::tabedit *ui;
};

#endif // TABEDIT_H
