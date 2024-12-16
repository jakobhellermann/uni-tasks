#ifndef NAMESLIST_H
#define NAMESLIST_H

#include <string>
#include <vector>

using namespace std;

class NamesList {
public:
    NamesList() {}

    void addName(const std::string& name);

    std::string& operator[](const size_t& index);
    const std::string& operator[](const size_t& index) const;

    const size_t size() const;

private:
    std::vector<std::string> m_names;
};

#endif //NAMESLIST_H
