#include "mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QThread>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->buttonChooseFile, &QPushButton::clicked, this, &MainWindow::onButtonChooseClicked);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &MainWindow::onButtonCancelClicked);
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::onButtonClearClicked);
    connect(ui->buttonCompute, &QPushButton::clicked, this, &MainWindow::onButtonComputeClicked);

    ui->hashTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new QStandardItemModel(0, 2);
    model->setHeaderData(0, Qt::Horizontal, "String", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Hash", Qt::DisplayRole);

    ui->hashTable->setModel(model);

    workerThread = new QThread();
    worker = new HashWorker();
    worker->moveToThread(workerThread);

    connect(worker, &HashWorker::progressUpdate, this, &MainWindow::onProgressUpdate);
    connect(worker, &HashWorker::hashComputed, this, &MainWindow::onHashComputed);
    connect(worker, &HashWorker::cancelled, this, &MainWindow::onCancellationDone);
    connect(worker, &HashWorker::done, this, &MainWindow::onComputeFinished);

    calculateButtonStates();
}

MainWindow::~MainWindow() {
    workerThread->requestInterruption();
    workerThread->quit();
    workerThread->wait();

    delete ui;
    delete model;
    delete workerThread;
    delete worker;
}

void MainWindow::calculateButtonStates() {
    const bool notEmpty = model->rowCount() > 0;

    ui->buttonChooseFile->setEnabled(!running);
    ui->buttonClear->setEnabled(!running && notEmpty);
    ui->buttonCompute->setEnabled(!running && notEmpty);
    ui->buttonCancel->setEnabled(running);
}

void MainWindow::onButtonChooseClicked() {
    const auto filename = QFileDialog::getOpenFileName(this, tr("Choose File"), nullptr, tr("Text Files (*.txt)"));
    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        return;
    }

    model->removeRows(0, model->rowCount());
    QTextStream stream(&file);
    for (QString line = stream.readLine(); !line.isNull(); line = stream.readLine()) {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(line));
        rowItems.append(new QStandardItem(""));
        model->appendRow(rowItems);
    }

    file.close();

    calculateButtonStates();
}

void MainWindow::onButtonCancelClicked() {
    workerThread->requestInterruption();
    calculateButtonStates();

    workerThread->quit();
    workerThread->wait();
    delete workerThread;
    delete worker;
    workerThread = new QThread();
    worker = new HashWorker();
    worker->moveToThread(workerThread);

    connect(worker, &HashWorker::progressUpdate, this, &MainWindow::onProgressUpdate);
    connect(worker, &HashWorker::hashComputed, this, &MainWindow::onHashComputed);
    connect(worker, &HashWorker::cancelled, this, &MainWindow::onCancellationDone);
    connect(worker, &HashWorker::done, this, &MainWindow::onComputeFinished);
}

void MainWindow::onButtonClearClicked() {
    model->removeRows(0, model->rowCount());
    calculateButtonStates();

    ui->progressLabel->setText("");
    ui->progressBar->setValue(0);
}

void MainWindow::onButtonComputeClicked() {
    running = true;
    calculateButtonStates();

    workerThread->start();

    QList<QString> hashesToCompute;
    for (int i = 0; i < model->rowCount(); i++) {
        const auto name = model->item(i, 0)->text();
        hashesToCompute.append(name);

        model->item(i, 1)->setText("");
    }

    QMetaObject::invokeMethod(worker, "computeHashes", Q_ARG(QList<QString>, hashesToCompute));
}

void MainWindow::onProgressUpdate(int index, int total) {
    if (!running) {
        ui->progressLabel->setText("");
        ui->progressBar->setValue(0);
        return;
    }

    ui->progressLabel->setText(QString("Computing %1/%2").arg(index).arg(total));
    const int percentage = total > 0
                               ? static_cast<int>(static_cast<float>(index) / static_cast<float>(total) * 100)
                               : 0;
    ui->progressBar->setValue(percentage);
}

void MainWindow::onHashComputed(int index, QString hash) {
    model->setItem(index, 1, new QStandardItem(hash));
}

void MainWindow::onCancellationDone() {
    running = false;

    onProgressUpdate(0, 0);
    calculateButtonStates();
}

void MainWindow::onComputeFinished() {
    running = false;

    calculateButtonStates();
}
