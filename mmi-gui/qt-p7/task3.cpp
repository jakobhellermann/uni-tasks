#include "task3.h"

#include <fstream>
#include <iostream>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QFile>

#include "mainwindow.h"

/*
Q: Erklären Sie den Unterschied zwischen der automatischen Speicherverwaltung, die eine QObject-Instanz bietet,
und der automatischen Speicherverwaltung von Shared Pointern in C++. Welches Konzept ist Ihrer Ansicht nach besser?
A:
- QObjects beinhalten eine Hierarchie, bei der jedes Object ein Parent haben kann. Wird der Parent gelöscht, so werden
(standardmäßig) auch alle Kinder gelöscht. QObjects sind nicht kopierbar, d.h. es gibt exact einen Besitzer.
- shared_ptr bieten dagegen reference counting, d.h. mehrere Besitzer sind möglich.

- Kein Konzept ist "besser", sondern nur geeignet für verschiedene Use-Cases.
 */

void savePropertiesToFile(const QObject &obj, const QString &filename) {
    QFile file(filename);
    QDataStream stream(&file);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "Unable to open file for writing";
        return;
    }

    const auto metaObject = obj.metaObject();
    stream << metaObject->propertyCount();

    for (int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); i++) {
        QMetaProperty property = metaObject->property(i);
        QString name = QString::fromLatin1(property.name());
        QVariant value = property.read(&obj);

        stream << name << value;
    }

    file.close();
}

void readPropertiesFromFile(QObject &obj, const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Unable to open file for reading";
        return;
    }
    QDataStream stream(&file);


    int propertyCount;
    stream >> propertyCount;


    if (propertyCount == 0) {
        qWarning() << "No properties found";
    }

    for (int i = 0; i < propertyCount; i++) {
        QString propertyName;
        QVariant propertyValue;
        stream >> propertyName;
        stream >> propertyValue;

        obj.setProperty(propertyName.toStdString().c_str(), propertyValue);
    }

    file.close();
}
