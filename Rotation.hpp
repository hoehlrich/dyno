#ifndef ROTATION
#define ROTATION

#include <chrono>
#include <ratio>
#include <stdint.h>
#include <iomanip>
#include <iostream>
#include <ctime>

#define I   0.129

using namespace std;

class Rotation {
    public:
        Rotation(chrono::time_point<chrono::high_resolution_clock> start,
                chrono::time_point<chrono::high_resolution_clock> end);
        void calculate(Rotation& prevRotation, Rotation& nextRotation);
        chrono::time_point<chrono::high_resolution_clock> start;
        chrono::time_point<chrono::high_resolution_clock> end;
        chrono::duration<uint64_t, micro> rotationDuration;
        double *velocity;
        double *acceleration;
        double *torque;
};


Rotation::Rotation(chrono::time_point<chrono::high_resolution_clock> startTime,
        chrono::time_point<chrono::high_resolution_clock> endTime) {
        start = startTime;
        end = endTime;
        rotationDuration = chrono::duration_cast<chrono::microseconds>(end - start);
        velocity = new double;
        *velocity = (double) (2.0 * 3.14159) / rotationDuration.count();
        acceleration = nullptr;
        torque = nullptr;
}

void Rotation::calculate(Rotation& prevRotation, Rotation& nextRotation) {
    if (prevRotation.velocity != nullptr && nextRotation.velocity != nullptr) {
        acceleration = new double;
        torque = new double;
        *acceleration = (*nextRotation.velocity - *velocity) / rotationDuration.count();
        *torque = I * *acceleration;
    }
}

double radPerSecToRPM(double radPerSec) {
    return radPerSec * 60 / (2.0 * 3.14159);
}

ostream& operator<<(ostream& os, const Rotation& rotation) {
    const time_t start = chrono::system_clock::to_time_t(rotation.start);
    os << put_time(localtime(&start), "%H:%M:%S") << "    "
        << right << fixed << setprecision(3) << rotation.rotationDuration.count() / 1e+6 << 's';
    return os;
}

#endif
