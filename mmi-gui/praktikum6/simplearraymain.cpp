//
// Created by Prof. Dr. Malte Weiß on 18.11.24.
//

#include <iostream>
#include <ostream>

#include "simplearray.h"

int main() {
    // Create simple array
    SimpleArray<int> array(5);

    // Output values
    for (int i = 0; i < 5; i++) {
        array.set(i, 100 * i);
    }

    // Test setting value out of bounds
    try {
        array.set(5, 1234);
    } catch (...) {
        std::cout << "Expected index out of bounds." << std::endl;
    }

    // Resize array and set value
    array.resize(6);
    array.set(5, 1234);

    // Output values
    for (int i = 0; i < array.size(); i++) {
        std::cout << array.get(i) << std::endl;
    }

    return 0;
}
