#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "manualpage.h"
#include "automaticpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void moveHome();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Manualpage manualpage;
    Automaticpage automaticpage;
};
#endif // MAINWINDOW_H
