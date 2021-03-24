#ifndef AUTOMATICPAGE_H
#define AUTOMATICPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <iostream>
#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <vector>
#include <sstream>
#include <cstring>
#include <unistd.h>

namespace Ui {
class Automaticpage;
}

class Automaticpage : public QWidget
{
    Q_OBJECT

public:
    explicit Automaticpage(QWidget *parent = nullptr);
    ~Automaticpage();


signals:
    void homeClicked();

private slots:
    void on_Homebutton2_clicked();

    void on_pushButton_clicked();

    void endTempo();

    void doNothing();

private:
    Ui::Automaticpage *ui;
    QTimer *_timer;
    std::vector<std::string> _vnote;
    std::vector<std::string> _vnoteNb;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;

private:
    bool checkLen(std::vector<std::string> numbers);
    bool checkNoteValid(std::vector<std::string> numbers);
    bool checkSpecificCase(std::vector<std::string> numbers);
    bool parseStringWithChar(char c, std::string parse);
    bool parseString(std::string numbers);
    std::string convertVnoteNb(std::vector<std::string> toConvert);
    int convertIntoNb(std::string vnote);
};

#endif // AUTOMATICPAGE_H
