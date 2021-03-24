#include "automaticpage.h"
#include "./ui_automaticpage.h"

Automaticpage::Automaticpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Automaticpage)
{
    ui->setupUi(this);
    ui->Homebutton2->setFixedSize(45, 45);
    ui->Homebutton2->setIcon(QIcon("C:/Users/Samuel/Desktop/LaserHarpV1/rsc/previous-black.png"));
    ui->Homebutton2->setIconSize(QSize(60, 60));
    ui->errorMessage->hide();
    arduino_is_available = false;
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
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
}

Automaticpage::~Automaticpage()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void Automaticpage::on_Homebutton2_clicked()
{
    qint64 bw = 0;

    if (arduino->isWritable()){
        qDebug() << "je suis passé par ici tu connais les bails mon vieux";
        bw = arduino->write("no");
        qDebug() << bw << "byte(s) written ";
    } else
        qDebug() << "Couldn't write to serial!";
    emit homeClicked();
}

void Automaticpage::endTempo()
{
    ui->errorMessage->hide();
}

void Automaticpage::doNothing()
{
    std::cerr << "nothing" << std::endl;
}

int Automaticpage::convertIntoNb(std::string note)
{
    if (note.size() == 3) {
        if (std::strncmp(note.c_str(), "c#", 2) == 0)
            return 1 + (12 * (note[2] - 48));
        if (std::strncmp(note.c_str(), "d#", 2) == 0)
            return 3 + (12 * (note[2] - 48));
        if (std::strncmp(note.c_str(), "f#", 2) == 0)
            return 6 + (12 * (note[2] - 48));
        if (std::strncmp(note.c_str(), "g#", 2) == 0)
            return 8 + (12 * (note[2] - 48));
        if (std::strncmp(note.c_str(), "a#", 2) == 0)
            return 10 + (12 * (note[2] - 48));
    }
    if (note.size() == 2) {
        if (std::strncmp(note.c_str(), "c", 1) == 0)
            return 0 + (12 * (note[1] - 48));
        if (std::strncmp(note.c_str(), "d", 1) == 0)
            return 2 + (12 * (note[1] - 48));
        if (std::strncmp(note.c_str(), "e", 1) == 0)
            return 4 + (12 * (note[1] - 48));
        if (std::strncmp(note.c_str(), "f", 1) == 0)
            return 5 + (12 * (note[1] - 48));
        if (std::strncmp(note.c_str(), "g", 1) == 0)
            return 7 + (12 * (note[1] - 48));
        if (std::strncmp(note.c_str(), "a", 1) == 0)
            return 9 + (12 * (note[1] - 48));
        if (std::strncmp(note.c_str(), "b", 1) == 0)
            return 11 + (12 * (note[1] - 48));
     }
    return 0;
}

std::string Automaticpage::convertVnoteNb(std::vector<std::string> toConvert)
{
    std::string convert;

    for (size_t i = 0; i != toConvert.size(); i++) {
         convert += std::to_string(convertIntoNb(toConvert[i]));
         convert += " ";
    }
    convert[convert.size() -1] = '\0';
    return convert;
}

void Automaticpage::on_pushButton_clicked()
{
    _timer = new QTimer(this);
    std::string note = ui->textEdit->toPlainText().toStdString();
    std::stringstream ss(note);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    qint64 bw = 0;


    _vnote = vstrings;
    if (parseString(note) == false || note.size() < 1) {
        ui->errorMessage->show();
        connect(_timer, SIGNAL(timeout()), this, SLOT(endTempo()));
        _timer->setSingleShot(true);
        _timer->start(3000);
    } else {
        note = convertVnoteNb(_vnote);
        std::cerr << "note = ---" << note << "---" << std::endl;
        if (arduino->isWritable()){
                bw = arduino->write(note.c_str());
                //bw = arduino->write("test");
                qDebug() << bw << "byte(s) written ";
                //std::cerr << "bw = " << bw << std::endl;
                //std::cerr << "teetetetetetettetete" << std::endl;
        } else {
            qDebug() << "Couldn't write to serial!";
        }
    }
        //std::cerr << "there is an invalid note in your text zone" << std::endl;
    //std::cerr << "contenu saisie = " << note << std::endl;
}

bool Automaticpage::checkSpecificCase(std::vector<std::string> notes)
{
    for (size_t i = 0; i != notes.size(); i++) {
        if (notes[i][0] == 'e' && notes[i].size() > 2)
            return false;
        if (notes[i][0] == 'b' && notes[i].size() > 2)
            return false;
    }
    return true;
}

bool Automaticpage::parseStringWithChar(char c, std::string parse)
{
    for (size_t i = 0; parse.c_str()[i] != '\0'; i++) {
        if (parse.c_str()[i] == c)
            return true;
    }
    return false;
}

bool Automaticpage::checkLen(std::vector<std::string> notes)
{
    for (size_t i = 0; i != notes.size(); i++) {
        if (notes[i].size() != 2 && notes[i].size() != 3)
            return false;
    }
    return true;
}

bool Automaticpage::checkNoteValid(std::vector<std::string> notes)
{
    for (size_t i = 0; i != notes.size(); i++) {
        if (notes[i].size() == 3) {
            if (notes[i][0] < 'a' || notes[i][0] > 'z')
                return false;
            if (notes[i][1] != '#')
                return false;
            if(notes[i][2] < '0' || notes[i][2] > '9')
                return false;
        }
        if (notes[i].size() == 2) {
            if (notes[i][0] < 'a' || notes[i][0] > 'z')
                return false;
            if(notes[i][1] < '0' || notes[i][1] > '9')
                return false;
        }
    }
    return true;
}

bool Automaticpage::parseString(std::string notes)
{

    /*for (size_t i = 0; i != _vnote.size(); i++) {
        std::cerr << "_vnote[i] = ------" << _vnote[i] << "-----" << std::endl;
    }*/
    if (checkLen(_vnote) == false)
        return false;
    if (checkNoteValid(_vnote) == false)
        return false;
    if (checkSpecificCase(_vnote) == false)
        return false;
    for (size_t i = 0; notes[i] != '\0'; i++) {
        if ((parseStringWithChar(notes[i], " #0123456789cdefgab") == false))
            return false;
    }
    return true;
}
//----- PARSEUR ETAPE -----//
//1) parser les char dispos ok
//2) split chaque note dans un std::vector<std::string> ok
//3) verifier que chaque note est une len de 2 ou 3 autrement erreur ok
//4) verifier que si la taille est de 3 c'est bien lettre dièze chiffre ok
//5) verifier que si la taille est de 2 c'est bien lettre chiffre ok
//6) si e + chiffre est supérieur à 3 faux pareil pour B5 ok
//7) si un chiffre est supérieur supérieur à 10 erreur ko
