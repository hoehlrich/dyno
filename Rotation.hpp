#ifndef ROTATION
#define ROTATION

#include <chrono>
#include <stdint.h>
#include <iomanip>
#include <iostream>

#define I   0.129

using namespace std;

class Rotation {
    public:
        Rotation(chrono::time_point<chrono::high_resolution_clock> start,
                chrono::time_point<chrono::high_resolution_clock> end);
        void calculate(Rotation& prevRotation, Rotation& nextRotation);
    private:
        chrono::time_point<chrono::high_resolution_clock> start;
        chrono::time_point<chrono::high_resolution_clock> end;
        chrono::duration<uint64_t, micro> rotationDuration;
        double *velocity;
        double *acceleration;
        double *torque;
};

Rotation::Rotation(chrono::time_point<chrono::high_resolution_clock> start,
        chrono::time_point<chrono::high_resolution_clock> end) {
        
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
    // os << setw(4) << put_time(localtime(&rotation.start), "%c") << " to " << put_time(localtime(&rotation.end), "%H:%M:%S") << endl;
}

#endif
