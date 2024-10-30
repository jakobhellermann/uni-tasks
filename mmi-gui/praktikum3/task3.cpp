// ReSharper disable CppDFAUnusedValue
// ReSharper disable CppDFAUnreadVariable
// ReSharper disable CppDeclaratorNeverUsed
#include <cmath>
#include <iostream>

struct Vector4d {
    float x, y, z, w;
};

Vector4d operator+(const Vector4d &a, const Vector4d &b) {
    return Vector4d(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vector4d &operator+=(Vector4d &a, const Vector4d &b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

float operator*(const Vector4d &a, const Vector4d &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4d operator-(const Vector4d &a) {
    return Vector4d(-a.x, -a.y, -a.z, -a.w);
}

float operator!(const Vector4d &a) {
    float lengthSquared = a * a;
    return sqrtf(lengthSquared);
}

std::ostream &operator <<(std::ostream &output, const Vector4d &vec) {
    output << "Vector4d(" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ")";
    return output;
}

int main2() {
    Vector4d v0 = {1, 1, 1, 2};
    Vector4d v1 = {2, 2, 1, 3};
    Vector4d v2 = v0 + v1; // ergibt v2 = {3,3,2,5}
    Vector4d v3 = -v0; // ergibt v3 = {-1,-1,-1,-2}
    v3 += v1; // ergibt v3 = {1,1,0,1}
    double dotProduct = v0 * v1; // ergibt dotProduct = 11
    double length = !v1; // ergibt length = 4.24264
    std::cout << length << std::endl;
}


struct Group {
    int numMales;
    int numFemales;
    int numDiverse;
};

Group operator+(const Group &a, const Group &b) {
    return Group(a.numMales + b.numMales, a.numFemales + b.numFemales, a.numDiverse + b.numDiverse);
}

Group &operator+=(Group &a, const Group &b) {
    a.numMales += b.numMales;
    a.numFemales += b.numFemales;
    a.numDiverse += b.numDiverse;
    return a;
}

int operator!(const Group &a) {
    return a.numMales + a.numFemales + a.numDiverse;
}

Group operator~(const Group &a) {
    return Group{0, 0, !a};
}


std::ostream &operator <<(std::ostream &output, const Group &group) {
    output << "Group(" << group.numMales << ", " << group.numFemales << ", " << group.numDiverse << ")";
    return output;
}

int main3() {
    Group g1;
    g1.numMales = 5;
    g1.numFemales = 2;
    g1.numDiverse = 1;
    Group g2;
    g2.numMales = 3;
    g2.numFemales = 8;
    g2.numDiverse = 2;
    Group g3 = g1 + g2; // ergibt g3 = { male: 8, female: 10, diverse = 3 }
    g3 += g1; // ergibt g3 = { male: 13, female: 12, diverse = 4 }
    ~g3; // ergibt g3 = { male: 0, female: 0, diverse = 29 }
    size_t count = !g2; // ergibt count = 13
}


int main() {
    main3();
}
