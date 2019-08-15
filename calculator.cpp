#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calculator){
    ui->setupUi(this);

    // Initilize things in this constructor
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numBtns[10];
    for (int i = 0; i < 10; ++i) {
        QString btnName = "Button" + QString::number(i);
        numBtns[i] = Calculator::findChild<QPushButton *>(btnName);
        connect(numBtns[i], SIGNAL(released()), this, SLOT(numPressed()));
    }
    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(mathBtnPresssed()));
    connect(ui->ButtonMinus, SIGNAL(released()), this, SLOT(mathBtnPresssed()));
    connect(ui->ButtonMultiply, SIGNAL(released()), this, SLOT(mathBtnPresssed()));
    connect(ui->ButtonDivide, SIGNAL(released()), this, SLOT(mathBtnPresssed()));
    connect(ui->ButtonEqual, SIGNAL(released()), this, SLOT(equalBtn()));
    connect(ui->ButtonChangeSign, SIGNAL(released()), this, SLOT(changeSign()));
}

Calculator::~Calculator() {
    delete ui;
}

void Calculator::numPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();
    QString displayVal = ui->Display->text();

    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0) {
        ui->Display->setText(btnVal);
    } else {
        QString newVal = displayVal + btnVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::mathBtnPresssed() {
    divTrigger = false;
    multTrigger= false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();

    if (QString::compare(btnVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if (QString::compare(btnVal, "*", Qt::CaseInsensitive) == 0) {
        multTrigger = true;
    } else if (QString::compare(btnVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    }  else if (QString::compare(btnVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::equalBtn() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dbDisplayVal = displayVal.toDouble();

    if (addTrigger || subTrigger || multTrigger || divTrigger) {
        if (addTrigger) {
            solution = calcVal + dbDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dbDisplayVal;
        } else if (multTrigger) {
            solution = calcVal * dbDisplayVal;
        } else if (divTrigger) {
            solution = calcVal / dbDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::changeSign() {
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9]*");
    if (reg.exactMatch(displayVal)) {
        double dbDisplay = displayVal.toDouble();
        double dbDisplayValSign = -1 * dbDisplay;
        ui->Display->setText(QString::number(dbDisplayValSign));
    }
}
