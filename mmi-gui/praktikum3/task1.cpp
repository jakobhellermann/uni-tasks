#include <iostream>

using namespace std;

int containsDigits(char* string) {}

int main() {
    // a
    float f = 2.5;
    // long i = f;
    long i = static_cast<long>(f);

    // b
    int number = 12;
    // char* firstByte = (char*)&number;
    char* firstByte = reinterpret_cast<char*>(&number);

    // c
    const char* name = "Bob";
    // bool hasDigit = containsDigits((char*)name);
    bool hasDigit = containsDigits(const_cast<char*>(name));
}
