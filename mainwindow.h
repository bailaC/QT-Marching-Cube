#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_Grid_resolution_comboBox_activated(int index);

    void on_Point_size_comboBox_activated(int index);

    void on_Colour_map_comboBox_activated(int index);

    void on_Camera_combo_activated(int index);

    void on_Drawing_mode_comboBox_activated(int index);

    void on_browse_pushButton_clicked();

    void on_filepath_Edit_returnPressed();

    void on_checkBox_5_clicked();

    void on_HorizontalSlider_valueChanged(int value);

    void on_opacitySlider_sliderMoved(int position);

    void on_Background_comboBox_activated(int index);

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
