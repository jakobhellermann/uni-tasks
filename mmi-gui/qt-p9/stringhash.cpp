#include "stringhash.h"

#include <QCryptographicHash>
#include <QThread>

// === DIESE FUNKTION DARF NICHT VERÄNDERT WERDEN! ===

QString computeStringHash(QString string) {
    QCryptographicHash hash(QCryptographicHash::Sha3_512);
    hash.addData(string.toStdString().c_str());

    // QThread::sleep(1);

    return QString(hash.result().toHex());
}
