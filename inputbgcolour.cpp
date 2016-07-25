#include "inputbgcolour.h"
#include "ui_inputbgcolour.h"
#include "opengl/glvolume.h"


extern GLfloat bgColour[3];

InputBGColour::InputBGColour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputBGColour)
{
    ui->setupUi(this);
    this->setWindowTitle("Choose Colour");
    QString b;
    this->ui->Red_lineEdit->setText(b.setNum(bgColour[0]));
    this->ui->Green_lineEdit->setText(b.setNum(bgColour[1]));
    this->ui->Blue_lineEdit->setText(b.setNum(bgColour[2]));
}

InputBGColour::~InputBGColour()
{

}

void InputBGColour::on_buttonBox_accepted()
{
    QString val = this->ui->Red_lineEdit->text();
    bgColour[0] = val.toFloat();
    val = this->ui->Green_lineEdit->text();
    bgColour[1] = val.toFloat();
    val = this->ui->Blue_lineEdit->text();
    bgColour[2] = val.toFloat();

}
