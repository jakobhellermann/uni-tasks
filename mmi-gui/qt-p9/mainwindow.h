#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

#include "HashWorker.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:

    void calculateButtonStates();

    Ui::MainWindow *ui;
    QStandardItemModel *model;

    QThread *workerThread;
    HashWorker *worker;

    bool running = false;

public slots:
    void onButtonChooseClicked();
    void onButtonCancelClicked();
    void onButtonClearClicked();
    void onButtonComputeClicked();

    void onProgressUpdate(int index, int total);
    void onHashComputed(int index, QString hash);
    void onCancellationDone();
    void onComputeFinished();
};
#endif // MAINWINDOW_H
