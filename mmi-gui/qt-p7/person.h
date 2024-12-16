#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>
#include <QDate>

class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastname MEMBER m_lastname)
    Q_PROPERTY(QString firstname MEMBER m_firstname)
    Q_PROPERTY(QDate dateOfBirth MEMBER m_dateOfBirth)

public:
    Person(QObject *parent = nullptr);
    Person(QString lastname, QString firstname, QDate dateOfBirth, QObject *parent = nullptr);

    const QString& lastname()       { return m_lastname; }
    const QString& firstname()      { return m_firstname; }
    const QDate& dateOfBirth()      { return m_dateOfBirth; }

private:
    QString m_lastname;
    QString m_firstname;
    QDate m_dateOfBirth;
};

#endif // PERSON_H
