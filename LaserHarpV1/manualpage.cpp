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
    ui->Homebutton->setIcon(QIcon("./rsc/previous-black.png"));
    ui->Homebutton->setIconSize(QSize(60, 60));
}

Manualpage::~Manualpage()
{
    delete ui;
}

void Manualpage::setArduinoComponent(QSerialPort *arduino)
{
    _arduino = arduino;
}

void Manualpage::on_Homebutton_clicked()
{
    qint64 bw = 0;

    if (_arduino->isWritable()){
        bw = _arduino->write("no");
        qDebug() << bw << "byte(s) written ";
        _arduino->flush();
    } else
        qDebug() << "Couldn't write to serial!";
    emit homeClicked();
}

void Manualpage::on_pushButton_clicked()
{
    qint64 bw = 0;

    if (_arduino->isWritable()){
        bw = _arduino->write("Manual");
        qDebug() << bw << "byte(s) written ";
        _arduino->flush();
    } else
        qDebug() << "Couldn't write to serial!";
}
