#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msg_btn1;
    msg_btn1.setText("Hello");
    msg_btn1.exec();
    ui->lcd1->display(2);
    
}

void MainWindow::SetPlot(QWidget *plot)
{
//    ui->grapf->minimumSize(). ;
      plot->setParent(ui->grapf);

}

void MainWindow::show_g()
{
    ui->grapf->show();
}


void MainWindow::on_xSlider_sliderMoved(int position)
{
    xSlider = position;
    ui->xLCD->display(xSlider);
}

void MainWindow::on_ySlider_sliderMoved(int position)
{
    ySlider = position;
    ui->yLCD->display(ySlider);

}
