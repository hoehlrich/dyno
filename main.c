#include <ftd2xx.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    DWORD dwBytesInQueue = 0;
    EVENT_HANDLE eh;
    FT_STATUS ftStatus;
    FT_HANDLE ftHandle;
    int iport;

    if (argc > 1) {
        sscanf(argv[1], "%d", &iport);
    } else {
        iport = 0;
    }

    pthread_mutex_init(&eh.eMutex, NULL);
    pthread_cond_init(&eh.eCondVar, NULL);

    ftStatus = FT_Open(iport, &ftHandle);
    if (ftStatus != FT_OK) {
        /*
           This can fail if the ftdi_sio driver is loaded
           use lsmod to check this and rmmod ftdi_sio to remove
           also rmmod usbserial
           */
        printf("FT_Open(%d) failed\n", iport);
        return 1;
    }

    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    if (ftStatus != FT_OK) {
        printf("Failed to set flow control\n");
    }

    struct timeval start, end;
    int i = 0;
    while (1) {
        ftStatus = FT_SetEventNotification(ftHandle, FT_EVENT_RXCHAR, (PVOID)&eh);
        if (ftStatus != FT_OK) {
            printf("Failed to set events\n");
            return 1;
        }

        pthread_mutex_lock(&eh.eMutex);
        pthread_cond_wait(&eh.eCondVar, &eh.eMutex);
        pthread_mutex_unlock(&eh.eMutex);
        if (i == 0) {
            gettimeofday(&start, NULL);
            i++;
            continue;
        }

        FT_GetQueueStatus(ftHandle, &dwBytesInQueue);
        gettimeofday(&end, NULL);
        long int delta =
            (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
        printf("rotation took %ldus = %lfs\n", delta, delta / 1.0e6);
        start = end;

        i++;
        printf("%d\n", i);
    }

    FT_Close(ftHandle);

    return 0;
}
