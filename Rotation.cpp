#include <chrono>
#include <iomanip>
#include <iostream>
#include "Rotation.h"

using namespace std;

Rotation::Rotation(chrono::time_point<chrono::high_resolution_clock> start,
        chrono::time_point<chrono::high_resolution_clock> end) {
        rotationDuration = chrono::duration_cast<chrono::microseconds>(end - start);
        velocity = new double;
        *velocity = (double) (2.0 * 3.14159) / (rotationDuration.count() / 1e+6);
        acceleration = nullptr;
        torque = nullptr;
        relativeTimestamp = nullptr;
}

Rotation::Rotation(chrono::duration<uint64_t, micro> duration) {
    rotationDuration = duration;
    velocity = new double;
    *velocity = (double) (2.0 * 3.14159) / (rotationDuration.count() / 1e+6);
    acceleration = nullptr;
    torque = nullptr;
    relativeTimestamp = nullptr;
}

void Rotation::calculate(Rotation& prevRotation, Rotation& nextRotation) {
    relativeTimestamp =  new chrono::duration<double>(*prevRotation.relativeTimestamp + chrono::duration_cast<chrono::duration<double>>(prevRotation.rotationDuration));
    if (prevRotation.velocity != nullptr && nextRotation.velocity != nullptr) {
        acceleration = new double;
        torque = new double;
        *acceleration = (*nextRotation.velocity - *prevRotation.velocity) / (rotationDuration.count() / 1e+6);
        *torque = I * *acceleration;
    }
}

double radPerSecToRPM(double radPerSec) {
    return radPerSec * 60 / (2.0 * 3.14159);
}

ostream& operator<<(ostream& os, const Rotation& rotation) {
    os << left << fixed << setprecision(3) << rotation.rotationDuration.count() / 1e+6;
    if (rotation.relativeTimestamp != nullptr)
        os << "\t\t" << left << defaultfloat << setw(5) << setprecision(3) << rotation.relativeTimestamp->count();
    if (rotation.velocity != nullptr)
        os << "\t\t" << left << defaultfloat << setw(5) << setprecision(4) << radPerSecToRPM(*rotation.velocity) ;
    if (rotation.acceleration != nullptr)
        os << "\t\t" << left << defaultfloat << setw(5) << setprecision(4) << *rotation.acceleration;
    if (rotation.torque != nullptr)
        os << "\t\t" << left << defaultfloat << setw(5) << setprecision(4) <<  *rotation.torque;
    return os;
}

