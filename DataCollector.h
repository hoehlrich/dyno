#ifndef DATA_COLLECTOR
#define DATA_COLLECTOR

#include <ftd2xx.h>
#include <vector>
#include <atomic>
#include "Rotation.h"

class DataCollector {
    public:
        ~DataCollector();
        DataCollector(int ftdiPort, vector<Rotation> *rotations);
        void collectDataUntilKeyPressed();
    private:
        DWORD bytesInQueue;
        EVENT_HANDLE eh;
        FT_STATUS ftStatus;
        FT_HANDLE ftHandle;
        int iport;
        atomic_bool exit;
        vector<Rotation> *rotationData;
        void collectData();
};

#endif
