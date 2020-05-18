#include <Windows.h>
#include <stdio.h>
#define MAX_Thread 2

int count;

DWORD WINAPI IncrCount(LPVOID IpParam)
{
    int k;
    for (k = 0; k < 500000; k++)
        count++;
    return 0; // thread 종료
}
DWORD WINAPI DecrCount(LPVOID IpParam)
{
    int k;
    for (k = 0; k < 500000; k++)
        count--;
    return 0; // thread 종료
}

int main(void)
{
    DWORD ID[MAX_Thread], Param[2] = { 1,2 };
    HANDLE hndl[MAX_Thread];
    int k;

    hndl[0] = CreateThread(NULL, 0, IncrCount, &Param[0], 0, &ID[0]);
    hndl[1] = CreateThread(NULL, 0, DecrCount, &Param[1], 0, &ID[1]);
    for (k = 0; k < MAX_Thread; k++) {
        if (hndl[k] == NULL) {
            printf("Creating Threads failed\n");
            return -1;
        }
    }
    WaitForMultipleObjects(MAX_Thread, hndl, TRUE, INFINITE);
    printf("final value of count = %d \n", count);
    for (k = 0; k < MAX_Thread; k++) {
        CloseHandle(hndl[k]);
    }
    return 0;
}