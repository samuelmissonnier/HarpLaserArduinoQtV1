#ifndef MANUALPAGE_H
#define MANUALPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class Manualpage;
}

class Manualpage : public QWidget
{
    Q_OBJECT

public:
    explicit Manualpage(QWidget *parent = nullptr);
    ~Manualpage();

private slots:
    void on_Homebutton_clicked();

    void on_pushButton_clicked();

signals:
    void homeClicked();

private:
    Ui::Manualpage *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // MANUALPAGE_H
