#ifndef INPUTDIMENSION_H
#define INPUTDIMENSION_H

#include <QDialog>

#include <QRegExpValidator>

namespace Ui {
class InputDimension;
}

class InputDimension : public QDialog
{
    Q_OBJECT

public:
    explicit InputDimension(QWidget *parent = 0);
    ~InputDimension();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::InputDimension *ui;
};

#endif // INPUTDIMENSION_H
