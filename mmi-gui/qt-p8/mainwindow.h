#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void reset();

    void checkEnabledCalculate();
    void checkEnabledSwap();
    void checkEnabledReset();
    void checkEnabledDiv();

    void calculate();

private:

    bool inputsFilled();

    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
