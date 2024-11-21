#ifndef DATA_COLLECTOR
#define DATA_COLLECTOR

#include <iostream>
#include <ftd2xx.h>
#include <vector>
#include <chrono>
#include <atomic>
#include <boost/thread.hpp>
#include "Rotation.hpp"

using namespace std;

class DataCollector {
    public:
        ~DataCollector();
        DataCollector(int ftdiPort, vector<Rotation>& rotations);
        void collectDataUntilKeyPressed();
    private:
        DWORD bytesInQueue;
        EVENT_HANDLE eh;
        FT_STATUS ftStatus;
        FT_HANDLE ftHandle;
        int iport;
        atomic_bool exit;
        vector<Rotation> rotationData;
        void collectData();
};

void DataCollector::collectDataUntilKeyPressed() {
    cout << "BEGIN DATA COLLECTION (<CR> to quit)" << endl;
    exit = false;
    boost::thread t;
    t = boost::thread(boost::bind(&DataCollector::collectData, this));
    cin.get();
    exit = true;
    cout << "END DATA COLLECTION" << endl;
}

void DataCollector::collectData() {
    pthread_mutex_init(&eh.eMutex, NULL);
    pthread_cond_init(&eh.eCondVar, NULL);

    chrono::time_point<chrono::high_resolution_clock> start, end;
    int i = 0;
    while (!exit) {
        if (exit) {
            break;
        }

        ftStatus = FT_SetEventNotification(ftHandle, FT_EVENT_RXCHAR, (PVOID) &eh);
        if (ftStatus != FT_OK) {
            cout << "Failed to set events" << endl;
            return;
        }

        pthread_mutex_lock(&eh.eMutex);
        pthread_cond_wait(&eh.eCondVar, &eh.eMutex);
        pthread_mutex_unlock(&eh.eMutex);

        if (i == 0) {
            start = chrono::high_resolution_clock::now();
        }

        FT_GetQueueStatus(ftHandle, &bytesInQueue);
        end = chrono::high_resolution_clock::now();
        Rotation r = Rotation(start, end);
        rotationData.push_back(r);
        cout << r << endl;
        start = end;
        i++;
    }
}

DataCollector::DataCollector(int ftdiPort, vector<Rotation>& rotations) {
    bytesInQueue = 0;
    iport = ftdiPort;
    ftStatus = FT_Open(iport, &ftHandle);
    rotationData = rotations;
    exit = false;
    if (ftStatus != FT_OK) {
        cout << "FT_Open(" << iport << ")failed" << endl;
        // maybe throw an error
    }

    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    if (ftStatus != FT_OK) {
        cout << "Failed to et flow control" << endl;
        // maybe throw an error (prolly not)
    }
}

DataCollector::~DataCollector() {
    FT_Close(ftHandle);
}

#endif
