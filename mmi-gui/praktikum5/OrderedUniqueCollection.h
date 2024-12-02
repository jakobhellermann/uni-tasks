#ifndef ORDEREDUNIQUECOLLECTION_H
#define ORDEREDUNIQUECOLLECTION_H

#include <vector>
#include <iostream>


class ElementAlreadyExists final : public std::exception {
};

template<typename T>
class OrderedUniqueCollection {
    std::vector<T> list;

    size_t size() const {
        return list.size();
    }

    T &operator[](size_t i) {
        return list[i];
    }

    const T &operator[](size_t i) const {
        return list[i];
    }

public:
    void add(T item);

    template<typename T2>
    friend std::ostream &operator<<(std::ostream &os, const OrderedUniqueCollection<T2> &collection);
};

template<typename T>
void OrderedUniqueCollection<T>::add(T item) {
    for (auto it = list.begin(); it != list.end(); it++) {
        if (item == *it) {
            throw ElementAlreadyExists();
        }
        if (item < *it) {
            list.insert(it, item);
            return;
        }
    }

    list.push_back(item);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const OrderedUniqueCollection<T> &collection) {
    os << "OrderedUniqueCollection(";
    for (const auto &it: collection.list) {
        os << it << ", ";
    }
    os << ")";
    return os;
}


#endif //ORDEREDUNIQUECOLLECTION_H
