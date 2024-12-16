#include "NamesList.h"

void NamesList::addName(const std::string &name) {
    m_names.push_back(name);
}

std::string &NamesList::operator[](const size_t &index) {
    return m_names[index];
}

const std::string &NamesList::operator[](const size_t &index) const {
    return m_names[index];
}

const size_t NamesList::size() const {
    return m_names.size();
}
