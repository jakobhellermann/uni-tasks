#ifndef TASK3_H
#define TASK3_H
#include <qobject.h>

void savePropertiesToFile(const QObject& obj, const QString& filename);
void readPropertiesFromFile(QObject& obj, const QString& filename);

#endif