#include "OrderedUniqueCollection.h"
#include <iostream>

struct Cube {
    float width, height, depth;

    friend std::ostream &operator<<(std::ostream &os, const Cube &c) {
        return os << "(" << c.width << ", " << c.height << ", " << c.depth << " @ " << c.getVolume() << ")";
    }

    bool operator==(const Cube &other) const {
        return this->getVolume() == other.getVolume();
    }

    auto operator<=>(const Cube &other) const {
        return this->getVolume() <=> other.getVolume();
    }

private:
    float getVolume() const {
        return width * height * depth;
    }
};


int main() {
    OrderedUniqueCollection<int> collectionInt;
    collectionInt.add(5);
    collectionInt.add(2);
    collectionInt.add(8);
    // collection.add(8);
    std::cout << collectionInt << std::endl;

    OrderedUniqueCollection<std::string> collectionString;
    collectionString.add("banana");
    collectionString.add("apple");
    collectionString.add("grapefruit");
    std::cout << collectionString << std::endl;

    OrderedUniqueCollection<Cube> collectionCube;
    collectionCube.add(Cube{.width = 0.5, .height = 0.5, .depth = 0.5});
    collectionCube.add(Cube{.width = 1.0, .height = 0.5, .depth = 2.0});
    collectionCube.add(Cube{.width = 0.1, .height = 0.1, .depth = 0.3});
    std::cout << collectionCube << std::endl;
}
