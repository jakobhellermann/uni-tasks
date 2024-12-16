//
// Created by jakob on 1/9/25.
//

#include "HashWorker.h"

#include <iostream>
#include <ostream>
#include <QThread>
#include <QDebug>

#include "stringhash.h"

void HashWorker::computeHashes(const QList<QString> &strings) {
    const int count = strings.size();

    for (int i = 0; i < count; i++) {
        const QString &value = strings[i];
        qDebug() << value;
        emit progressUpdate(i, count);

        if (QThread::currentThread()->isInterruptionRequested()) {
            qDebug() << "Interrupting hash worker.";
            emit cancelled();
            return;
        }
        const QString hash = computeStringHash(value);

        emit hashComputed(i, hash);
    }
    emit progressUpdate(count, count);
    emit done();
}
