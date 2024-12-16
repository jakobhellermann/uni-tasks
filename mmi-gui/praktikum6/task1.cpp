#include <complex.h>
#include <iostream>
#include <memory>
#include <stdio.h>

#include "rectangle.h"

class Animal {
public:
    virtual void makeNoise() {
        std::cout << "...";
    }

    virtual ~Animal() = default;

    friend class Dog;

    friend void makeNoise();
};

class Dog : public Animal {
public:
    void makeNoise() {
        std::cout << "bark" << std::endl;
    }

    ~Dog() override {
        std::cout << "deleting dog" << std::endl;
    }
};

void takes_animal(Animal animal) {
    animal.makeNoise();
}


class InitializerTestParent {
public:
    InitializerTestParent(int a) {
    }
};

class InitializerTest : public InitializerTestParent {
    const int member;

    InitializerTest(float c) : InitializerTestParent(5), member(3) {
        // this->member = 3;
    }

    InitializerTest() : InitializerTest(100) {
    }
};

/*
Ohne virtual inheritance:

A   A
|   |
B   C
 \ /
  D

Mit virtual inheritance:
  A
 / \
B   C
 \ /
  D
*/

class DiamondGrandarent {
    int member;
};

class DiamondParentA : virtual public DiamondGrandarent {
};

class DiamondParentB : virtual public DiamondGrandarent {
};

class DiamondChild : public DiamondParentA, DiamondParentB {
};


int main() {
    // Q1: Standardmäßig sind Methoden in C++ nicht polymorph. Was bedeutet das? Wie stell
    // man sicher, dass eine Methode polymorph wird?

    Animal *animal = new Dog();
    animal->makeNoise();

    // A: Nicht polymorph bedeutet, dass eine methode nicht automatisch von Kindklassen überschrieben wird.
    // Mit `virtual` kann man dieses Verhalten erzielen.

    // Q2: Wieso benötigt man in C++ Destruktoren, aber nicht in Java?
    // A: Java ist garbage collected.

    // Q3: Wieso sollte ein Destruktor in einer Klassenhierarchie mit dem Schlüsselwort virtual
    //versehen sein?
    delete animal;
    // A: Damit Kindklassen die Möglichkeit haben, einen Destruktor zu haben.

    // Q4: Wie realisiert man in C++ eine abstrakte Klasse?
    // A: Jede Methode ist virtual.

    // Q5:
    // Nennen Sie die drei Situationen, die die Verwendung von Initialisierungslisten in
    // Konstruktoren erforderlich machen.
    // A:
    // - const member initialisieren
    // - Aufrufen von Parent-Konstruktor
    // - Aufrufen eines bestehenden Konstruktors

    // Q6: Welches Problem lösen Smart Pointer?
    // A: Smart Pointer helfen bei der Speicherverwaltung.
    // Sie funktionieren dadurch, dass automatisch beim Ende des Scopes der Destruktor aufgerufen wird.

    // Q7: Erklären Sie, wie die drei Smart Pointer funktionieren: Shared pointer, unique pointer,
    // weak pointer.
    // - Shared: Ein Object kann mehrere Besitzer haben, der shared_pointer speichert die Anzahl der Besitzer und löscht bei n=0
    //   - Weak: Ein "Besitzer" eines Shared pointers, der allerdings die reference count nicht erhöht,

    std::weak_ptr<int> weak_copy;
    //
    {
        std::shared_ptr<int> shared = std::make_shared<int>(5);
        auto copy = shared;
        weak_copy = std::weak_ptr(shared);

        std::cout << shared.use_count() << std::endl;
    }
    std::cout << weak_copy.lock() << std::endl;

    // unique ptr: Exact ein Besitzer, entspricht automatischem new / delete.

    // Q8: Welche Wirkung hat das Schlüsselwort friend? Warum sollte man es einsetzen,
    //obwohl man stattdessen auch Getter verwenden kann, um auf interne Attribute
    //zuzugreifen?
    // A: `friend` bedeutet, dass die besagte Klasse oder Methode auf private member zugreifen darf.

    // Q9: Erklären Sie, wie es in C++ zum Diamantenproblem kommen kann und wie man es
    //löst.

    // Siehe Codebeispiel, der Grandparent-Member ist zweimal im Kind.
    // Lösung: virtual inheritance

    // Q10: Index-Operator zweimal mit und ohne const
    // A: Damit der Operator sowohl in const-, als auch in nicht-const Kontexten verwendet werden kann.
    // Und im const-Fall auch eine const referenz zurückgibt.

    Rectangle a(10, 10, 4, 3);
    Rectangle b(8, 20, 2, 1);


    Rectangle c = a | b;
    std::cout << std::endl;
    std::cout << c.getX() << std::endl;
    std::cout << c.getY() << std::endl;
    std::cout << c.getWidth() << std::endl;
    std::cout << c.getHeight() << std::endl;
}
