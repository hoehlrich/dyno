#ifndef DATA_COLLECTOR
#define DATA_COLLECTOR

#include <iostream>
#include <ftd2xx.h>
#include <chrono>

using namespace std;

class DataCollector {
    public:
        ~DataCollector();
        DataCollector(int ftdiPort);
        void collectData(void (*pushTimestamp)(chrono::time_point<chrono::high_resolution_clock>));
    private:
        DWORD bytesInQueue = 0;
        EVENT_HANDLE eh;
        FT_STATUS ftStatus;
        FT_HANDLE ftHandle;
        int iport;
};

void DataCollector::collectData(void (*pushTimestamp)(chrono::time_point<chrono::high_resolution_clock>)) {
    pthread_mutex_init(&eh.eMutex, NULL);
    pthread_cond_init(&eh.eCondVar, NULL);

    chrono::time_point<chrono::high_resolution_clock> start, end;
    while (1) {
        ftStatus = FT_SetEventNotification(ftHandle, FT_EVENT_RXCHAR, (PVOID) &eh);
        if (ftStatus != FT_OK) {
            cout << "Failed to set events" << endl;
            return;
        }

        pthread_mutex_lock(&eh.eMutex);
        pthread_cond_wait(&eh.eCondVar, &eh.eMutex);
        pthread_mutex_unlock(&eh.eMutex);

        FT_GetQueueStatus(ftHandle, &bytesInQueue);
        pushTimestamp(chrono::high_resolution_clock::now());

        // need some exit condition (maybe C-D EOF interrupt??)
    }
}

DataCollector::DataCollector(int ftdiPort) {
    iport = ftdiPort;
    ftStatus = FT_Open(iport, &ftHandle);
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
