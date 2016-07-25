#ifndef INPUTBGCOLOUR_H
#define INPUTBGCOLOUR_H

#include <QDialog>

namespace Ui {
class InputBGColour;
}

class InputBGColour : public QDialog
{
    Q_OBJECT

public:
    explicit InputBGColour(QWidget *parent = 0);
    ~InputBGColour();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::InputBGColour *ui;
};

#endif // INPUTBGCOLOUR_H
