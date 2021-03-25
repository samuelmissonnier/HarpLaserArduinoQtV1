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
    void setArduinoComponent(QSerialPort *arduino);

private slots:
    void on_Homebutton_clicked();

    void on_pushButton_clicked();

signals:
    void homeClicked();

private:
    Ui::Manualpage *ui;
    QSerialPort *_arduino;
};

#endif // MANUALPAGE_H
