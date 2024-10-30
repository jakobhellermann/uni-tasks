#include <iostream>
#include <cmath>

using namespace std;

// Enumerator for units
enum Unit {
    CubicCm, // cm^3
    CubicMeter // m^3
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

float getVolume(Cube cube) {
    return cube.edgeLengthInCm * cube.edgeLengthInCm * cube.edgeLengthInCm;
}

float getVolume(Cylinder cube) {
    float base = M_PI * cube.baseRadiusInCm * cube.baseRadiusInCm;
    return base * cube.heightInCm;
}

float getVolume(Sphere cube) {
    float radius = cube.diameterInCm / 2;
    return (4.0f / 3.0f) * static_cast<float>(M_PI) * radius * radius * radius;
}


float getVolume(Sphere shape, Unit unit) {
    switch (unit) {
        case CubicCm:
            return getVolume(shape);
        case CubicMeter:
            return getVolume(shape) * CM_CUBED_TO_M_CUBED;
        default:
            return -1;
    }
}

float getVolume(Cube shape, Unit unit) {
    switch (unit) {
        case CubicCm:
            return getVolume(shape);
        case CubicMeter:
            return getVolume(shape) * CM_CUBED_TO_M_CUBED;
        default:
            return -1;
    }
}

float getVolume(Cylinder shape, Unit unit) {
    switch (unit) {
        case CubicCm:
            return getVolume(shape);
        case CubicMeter:
            return getVolume(shape) * CM_CUBED_TO_M_CUBED;
        default:
            return -1;
    }
}


/*template<typename T>
float getVolume(T shape, Unit unit) {
    switch (unit) {
        case CubicCm:
            return getVolume(shape);
        case CubicMeter:
            return getVolume(shape) * CM_CUBED_TO_M_CUBED;
        default:
            return -1;
    }
}*/

template<typename T>
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
            float radius = read<float>("Radius");
            Sphere sphere{.diameterInCm = radius * 2};

            volume = getVolume(sphere, unit);
            break;
        }
        case 'c': {
            float sideLength = read<float>("Side Length");
            Cube cube{.edgeLengthInCm = sideLength};

            volume = getVolume(cube, unit);
            break;
        }
        case 'y': {
            float radius = read<float>("Base Radius");
            float height = read<float>("Height");
            Cylinder cylinder{.baseRadiusInCm = radius, .heightInCm = height};

            volume = getVolume(cylinder, unit);
            break;
        }
        default:
            cout << "Unknown shape '" << shape << "'" << endl;
            return -1;
    }

    cout << "Volume: " << volume << endl;
    return 0;
}
