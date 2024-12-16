//
// Created by jakob on 1/9/25.
//

#ifndef HASHWORKER_H
#define HASHWORKER_H
#include <qobject.h>


class HashWorker : public QObject {
    Q_OBJECT

public:
    explicit HashWorker(QObject *parent = nullptr): QObject(parent) {
    }

signals:
    void hashComputed(int index, QString hash);

    void progressUpdate(int item, int count);
    void cancelled();
    void done();

public slots:
    void computeHashes(const QList<QString> &strings);
};


#endif //HASHWORKER_H
