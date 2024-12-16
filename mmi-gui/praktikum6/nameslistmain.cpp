#include <iostream>
#include <memory>

#include "NamesList.h"


// Änderungen:
// - initialisierung mit unique_ptr
// - kein delete
// - NamesList& in Funktion übergeben statt ptr

void printNamesList(const NamesList &list) {
    std::cout << "Names:" << std::endl;

    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << std::endl;
    }
}

int main() {
    std::unique_ptr<NamesList> namesList = make_unique<NamesList>();
    namesList->addName("Alice");
    namesList->addName("Bob");
    namesList->addName("Charles");
    namesList->addName("Daisy");

    printNamesList(*namesList);

    std::cout << "Number of elements in list: " << namesList->size() << std::endl;

    return 0;
}
