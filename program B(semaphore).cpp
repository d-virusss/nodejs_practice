#include <Windows.h>
#include <stdio.h>
#define MAX_Thread 20

int count;

DWORD WINAPI IncrCount(LPVOID IpParam)
{
    int k;
    for (k = 0; k < 10000; k++)
        count++;
    return 0; // thread ����
}
DWORD WINAPI DecrCount(LPVOID IpParam)
{
    int k;
    for (k = 0; k < 10000; k++)
        count--;
    return 0; // thread ����
}

int main(void)
{
    DWORD ID[MAX_Thread], Param[MAX_Thread];
    for (int i = 0; i < MAX_Thread; i++) {
        Param[i] = i + 1; // CreateThread���� thread�Լ��� IncrCoung / DecrCount�� �����ִ� �Ű�����
        //���������� ��������� ������ thread�� �����ϱ� ���� �뵵
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