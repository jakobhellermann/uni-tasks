#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->inputOp1->setValidator(new QDoubleValidator(0, 100, 2, this));
    ui->inputOp2->setValidator(new QDoubleValidator(1, 100, 2, this));


    connect(ui->actionReset, &QPushButton::clicked, this, &MainWindow::reset);

    connect(ui->inputOp1, &QLineEdit::textChanged, this, &MainWindow::checkEnabledCalculate);
    connect(ui->inputOp2, &QLineEdit::textChanged, this, &MainWindow::checkEnabledCalculate);

    connect(ui->radioAdd, &QRadioButton::toggled, this, &MainWindow::checkEnabledCalculate);
    connect(ui->radioSub, &QRadioButton::toggled, this, &MainWindow::checkEnabledCalculate);
    connect(ui->radioMul, &QRadioButton::toggled, this, &MainWindow::checkEnabledCalculate);
    connect(ui->radioDiv, &QRadioButton::toggled, this, &MainWindow::checkEnabledCalculate);

    connect(ui->inputOp2, &QLineEdit::textChanged, this, &MainWindow::checkEnabledDiv);

    connect(ui->actionCalculate, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(ui->actionQuit, &QPushButton::clicked, this, &MainWindow::close);

    reset();
    checkEnabledCalculate();
    checkEnabledSwap();
    checkEnabledReset();
    checkEnabledDiv();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::reset() {
    ui->labelResult->setText("Noch kein Ergebnis");
    ui->inputOp1->setText("");
    ui->inputOp2->setText("");

    ui->radioAdd->setChecked(false);
    ui->radioSub->setChecked(false);
    ui->radioMul->setChecked(false);
    ui->radioDiv->setChecked(false);
}

// slots

/**
 * Enable the calculate button if any operator is selected
 */
void MainWindow::checkEnabledCalculate() {
    bool operatorSelected = ui->radioAdd->isChecked() ||
                            ui->radioSub->isChecked() ||
                            ui->radioMul->isChecked() ||
                            ui->radioDiv->isChecked();

    ui->actionCalculate->setEnabled(inputsFilled() && operatorSelected);
}

/**
 * Enable the swap button if both inputs are nonempty
 */
void MainWindow::checkEnabledSwap() {
    ui->actionSwapOperands->setEnabled(inputsFilled());
}

/**
 * Enable the reset button if either input isnonempty
 */
void MainWindow::checkEnabledReset() {
    ui->actionReset->setEnabled(!ui->inputOp1->text().isEmpty() || !ui->inputOp2->text().isEmpty());
}

/**
 * Enable divide operator if division is valid
 */
void MainWindow::checkEnabledDiv() {
    double operand2 = ui->inputOp2->text().toDouble();
    bool valid = operand2 > 0;
    ui->radioDiv->setVisible(valid);
    ui->radioDiv->setChecked(false);
    if (!valid) {
        ui->actionCalculate->setChecked(false);
        checkEnabledCalculate();
    }
}

enum Op { Add, Sub, Mul, Div, Unknown };

/**
 * Calculates `operand1 <op> operand2` and writes the result into `labelResult`
 */
void MainWindow::calculate() {
    double operand1 = ui->inputOp1->text().toDouble();
    double operand2 = ui->inputOp2->text().toDouble();

    Op op;
    if (ui->radioAdd->isChecked()) {
        op = Add;
    } else if (ui->radioSub->isChecked()) {
        op = Sub;
    } else if (ui->radioMul->isChecked()) {
        op = Mul;
    } else if (ui->radioDiv->isChecked()) {
        op = Div;
    } else {
        op = Unknown;
    }

    /*Op op = ui->radioAdd->isChecked()
                ? Add
                : ui->radioSub->isChecked()
                      ? Sub
                      : ui->radioMul->isChecked()
                            ? Mul
                            : ui->radioDiv->isChecked()
                                  ? Div
                                  : Unknown;*/

    double result = 0;
    switch (op) {
        case Add:
            result = operand1 + operand2;
            break;
        case Sub:
            result = operand1 - operand2;
            break;
        case Mul:
            result = operand1 * operand2;
            break;
        case Div:
            result = operand1 / operand2;
            break;
        case Unknown:
            return;
    }

    ui->labelResult->setText(QString::number(result, 'g', 2));
}

// private methods

/**
 * 
 * @return whether both input fields are nonempty
 */
bool MainWindow::inputsFilled() {
    return !ui->inputOp1->text().isEmpty() && !ui->inputOp2->text().isEmpty();
}
