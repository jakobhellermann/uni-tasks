#include <iostream>

#include "mainwindow.h"

#include <QApplication>


#include "person.h"
#include "task3.h"

void checkObjectRoundtrip() {
    /*QObject obj = QObject(nullptr);
    obj.setProperty("test", QVariant(42));
    obj.setProperty("test2", QVariant("hello world"));
    obj.setProperty("test3", QVariant(3.1415));*/

    const Person obj("last", "first", QDate::currentDate(), nullptr);
    savePropertiesToFile(obj, "properties.txt");

    QObject reconstructed;
    readPropertiesFromFile(reconstructed, "properties.txt");

    std::cout << reconstructed.property("lastname").value<QString>().toStdString() << std::endl;
}

int main(int argc, char *argv[]) {
    checkObjectRoundtrip();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

