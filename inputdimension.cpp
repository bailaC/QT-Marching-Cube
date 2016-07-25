#include "inputdimension.h"
#include "ui_inputdimension.h"

#include "opengl/glvolume.h"

extern VOLUME grid;
QString gHeight = "1";
QString gWidth = "1";
QString gLength = "1";

QString Height = "128";
QString Width = "128";
QString Length = "128";

bool pressCancel = false;


InputDimension::InputDimension(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDimension)
{
    ui->setupUi(this);
    this->setWindowTitle("Dimension");
    this->ui->grid_height_Edit->setText(gHeight);
    this->ui->grid_width_Edit->setText(gWidth);
    this->ui->grid_length_Edit->setText(gLength);

    this->ui->height_Edit->setText(Height);
    this->ui->width_Edit->setText(Width);
    this->ui->length_Edit->setText(Length);

}

InputDimension::~InputDimension()
{

}

void InputDimension::on_buttonBox_accepted()
{
    QRegExpValidator* rxv = new QRegExpValidator(QRegExp("\\d*"), this);
    ui ->height_Edit->setValidator(new QIntValidator(0, 100, this));
    ui ->width_Edit->setValidator(rxv);
    ui ->length_Edit->setValidator(rxv);

    Height = this->ui->height_Edit->text();
    grid.Nx = Height.toInt();
    Width = this->ui->width_Edit->text();
    grid.Ny = Width.toInt();
    Length = this->ui->length_Edit->text();
    grid.Nz = Length.toInt();


    gHeight = this->ui->grid_height_Edit->text();
    grid.Dx = gHeight.toInt();
    gWidth = this->ui->grid_width_Edit->text();
    grid.Dy = gWidth.toInt();
    gLength = this->ui->grid_length_Edit->text();
    grid.Dz = gLength.toInt();
}

void InputDimension::on_buttonBox_rejected()
{
    pressCancel = true;
}
