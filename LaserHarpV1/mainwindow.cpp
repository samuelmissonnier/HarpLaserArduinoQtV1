#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->stackedWidget->insertWidget(1, &manualpage);
    ui->stackedWidget->insertWidget(2, &automaticpage);
    //connect(&manualpage, SIGNAL(homeClicked()), this, SLOT(moveHome()));
    connect(&automaticpage, SIGNAL(homeClicked()), this, SLOT(moveHome()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
