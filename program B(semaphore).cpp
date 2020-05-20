#include <Windows.h>
#include <stdio.h>
#define MAX_Thread 20

int count;

DWORD WINAPI IncrCount(LPVOID IpParam)
{
    int k;
    for (k = 0; k < 10000; k++)
        count++;
    return 0; // thread 종료
}
DWORD WINAPI DecrCount(LPVOID IpParam)
{
    int k;
    for (k = 0; k < 10000; k++)
        count--;
    return 0; // thread 종료
}

int main(void)
{
    DWORD ID[MAX_Thread], Param[MAX_Thread];
    for (int i = 0; i < MAX_Thread; i++) {
        Param[i] = i + 1; // CreateThread에서 thread함수인 IncrCoung / DecrCount로 보내주는 매개변수
        //실질적으로 사용하지는 않지만 thread를 구별하기 위한 용도
    }
    HANDLE hndl[MAX_Thread];
    int k;

    for (int i = 0; i < MAX_Thread; i+=2) {
        hndl[i] = CreateThread(NULL, 0, IncrCount, &Param[0], 0, &ID[0]);
        hndl[i+1] = CreateThread(NULL, 0, DecrCount, &Param[1], 0, &ID[1]);
    }
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