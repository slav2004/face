#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtDataVisualization/Q3DSurface>


using namespace QtDataVisualization; //уточнить!!!

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetPlot(QWidget *plot);
//    void SetPlot(Q3DSurface *plot);
    void show_g();

private slots:
    void on_pushButton_clicked();

    void on_xSlider_sliderMoved(int position);

    void on_ySlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    int xSlider;
    int ySlider;

};

#endif // MAINWINDOW_H
