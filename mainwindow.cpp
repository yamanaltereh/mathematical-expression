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
    QString str(ui->lineEdit->text());
    expression* myt;
    myt = new expression();
    myt->sss = str;
    myt->start();
    QString res = QString::number(myt->Resault);
    ui->lineEdit_2->setText(res);
}
