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
    ui->stackedWidget->insertWidget(1, &manualpage);
    ui->stackedWidget->insertWidget(2, &automaticpage);
    connect(&manualpage, SIGNAL(homeClicked()), this, SLOT(moveHome()));
    connect(&automaticpage, SIGNAL(homeClicked()), this, SLOT(moveHome()));
    arduino_is_available = false;
    arduino_port_name = "";
    _arduino = new QSerialPort;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }
    if(arduino_is_available){
        _arduino->setPortName(arduino_port_name);
        _arduino->open(QSerialPort::WriteOnly);
        _arduino->setBaudRate(31250);
        _arduino->setDataBits(QSerialPort::Data8);
        _arduino->setParity(QSerialPort::NoParity);
        _arduino->setStopBits(QSerialPort::OneStop);
        _arduino->setFlowControl(QSerialPort::NoFlowControl);
    } else
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
}

MainWindow::~MainWindow()
{
    if(_arduino->isOpen()){
        _arduino->close();
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    qobject_cast<Manualpage*>(ui->stackedWidget->widget(1))->setArduinoComponent(_arduino);
}

void MainWindow::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    qint64 bw = 0;

    ui->stackedWidget->setCurrentIndex(2);
    if (_arduino->isWritable()){
        bw = _arduino->write("Auto");
        qDebug() << bw << "byte(s) written ";
        _arduino->flush();
    } else
        qDebug() << "Couldn't write to serial!";
    qobject_cast<Automaticpage*>(ui->stackedWidget->widget(2))->setArduinoComponent(_arduino);
}
