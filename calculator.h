#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class Calculator;
}

class Calculator : public QMainWindow {
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    double calcVal = 0.0;
    bool divTrigger = false;
    bool multTrigger = false;
    bool addTrigger = false;
    bool subTrigger = false;

private slots:
    void numPressed();
    void mathBtnPresssed();
    void equalBtn();
    void changeSign();
};

#endif // MAINWINDOW_H
