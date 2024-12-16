#include "person.h"

Person::Person(QObject *parent) : QObject(parent) {

}

Person::Person(QString lastname, QString firstname, QDate dateOfBirth, QObject *parent) :
    m_lastname(lastname), m_firstname(firstname), m_dateOfBirth(dateOfBirth), QObject(parent) {

}
