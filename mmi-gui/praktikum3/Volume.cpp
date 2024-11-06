#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

// Enumerator for units
enum Unit {
    CubicCm,    // cm^3
    CubicMeter  // m^3
};

// Cube
struct Cube {
    float edgeLengthInCm;
};

// Sphere
struct Sphere {
    float diameterInCm;
};

// Cylinder
struct Cylinder {
    float baseRadiusInCm;
    float heightInCm;
};

// 1 cm^3 = (1/100 m)^3 = 1/1000000 m^3
const float CM_CUBED_TO_M_CUBED = 1e-6;

float getVolume(Cube cube, Unit unit = CubicCm) {
    float volumeCm3 = cube.edgeLengthInCm * cube.edgeLengthInCm * cube.edgeLengthInCm;
    return unit == CubicCm ? volumeCm3 : volumeCm3 * CM_CUBED_TO_M_CUBED;
}

float getVolume(Cylinder cylinder, Unit unit = CubicCm) {
    float base = M_PI * cylinder.baseRadiusInCm * cylinder.baseRadiusInCm;
    float volumeCm3 = base * cylinder.heightInCm;
    return unit == CubicCm ? volumeCm3 : volumeCm3 * CM_CUBED_TO_M_CUBED;
}

float getVolume(Sphere sphere, Unit unit = CubicCm) {
    float radius = sphere.diameterInCm / 2;
    float volumeCm3 = (4.0f / 3.0f) * static_cast<float>(M_PI) * radius * radius * radius;
    return unit == CubicCm ? volumeCm3 : volumeCm3 * CM_CUBED_TO_M_CUBED;
}

template <typename T>
T read(const char *prompt) {
    cout << prompt << " ";
    T value;
    cin >> value;
    return value;
}

int main() {
    char unitInput = read<char>("Unit? [c] cm^3 [m] m^3");

    Unit unit;
    switch (std::tolower(unitInput)) {
        case 'c':
            unit = Unit::CubicCm;
            break;
        case 'm':
            unit = Unit::CubicMeter;
            break;
        default:
            cout << "Unknown unit '" << unitInput << "'" << endl;
            return -1;
    }

    float volume;

    char shape = read<char>("Which shape? [S]phere/[C]ube/C[Y]liner?");
    switch (std::tolower(shape)) {
        case 's': {
            float radius = read<float>("Radius (cm)");
            Sphere sphere{.diameterInCm = radius * 2};

            volume = getVolume(sphere, unit);
            break;
        }
        case 'c': {
            float sideLength = read<float>("Side Length (cm)");
            Cube cube{.edgeLengthInCm = sideLength};

            volume = getVolume(cube, unit);
            break;
        }
        case 'y': {
            float radius = read<float>("Base Radius (cm)");
            float height = read<float>("Height (cm)");
            Cylinder cylinder{.baseRadiusInCm = radius, .heightInCm = height};

            volume = getVolume(cylinder, unit);
            break;
        }
        default:
            cout << "Unknown shape '" << shape << "'" << endl;
            return -1;
    }

    cout << "Volume: " << volume;
    if (unit == CubicCm) {
        cout << "cm^3";
    } else {
        cout << "m^3";
    }

    cout << endl;
    return 0;
}
