#include "manualpage.h"
#include "./ui_manualpage.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <iostream>

Manualpage::Manualpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manualpage)
{
    ui->setupUi(this);
    ui->Homebutton->setFixedSize(45, 45);
    ui->Homebutton->setIcon(QIcon("C:/Users/Samuel/Desktop/LaserHarpV1/rsc/previous-black.png"));
    ui->Homebutton->setIconSize(QSize(60, 60));
    /*arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

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
        // open and configure the serialport
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(31250);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    } else
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");*/
}

Manualpage::~Manualpage()
{
    /*if(arduino->isOpen()){
        arduino->close();
    }*/
    delete ui;
}

void Manualpage::on_Homebutton_clicked()
{
    /*qint64 bw = 0;

    if (arduino->isWritable()){
        qDebug() << "je suis passé par ici tu connais les bails mon vieux";
        bw = arduino->write("no");
        qDebug() << bw << "byte(s) written ";
    } else
        qDebug() << "Couldn't write to serial!";*/
    emit homeClicked();
}

void Manualpage::on_pushButton_clicked()
{
    /*qint64 bw = 0;

    if (arduino->isWritable()){
        qDebug() << "je suis passé par ici tu connais les bails";
        bw = arduino->write("Manual");
        qDebug() << bw << "byte(s) written ";
    } else
        qDebug() << "Couldn't write to serial!";*/

}
