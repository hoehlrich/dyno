#ifndef ROTATION
#define ROTATION

#define I   0.129

#include <chrono>
#include <ratio>
#include <stdint.h>
#include <iostream>
#include <iomanip>

using namespace std;

class Rotation {
    public:
        Rotation(chrono::time_point<chrono::high_resolution_clock> start,
                chrono::time_point<chrono::high_resolution_clock> end);
        Rotation(chrono::duration<uint64_t, micro> duration);
        void calculate(Rotation& prevRotation, Rotation& nextRotation);
        chrono::duration<uint64_t, micro> rotationDuration;
        double *velocity;
        double *acceleration;
        double *torque;
};

double radPerSecToRPM(double radPerSec);
ostream& operator<<(ostream& os, const Rotation& rotation);

#endif
