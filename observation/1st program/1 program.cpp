#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunction(LPVOID param) {
    printf("Child Thread:\n");
    printf("Thread ID: %lu\n", GetCurrentThreadId());
    return 0;
}

int main() {
    HANDLE thread;
    DWORD threadID;

    printf("Parent Process:\n");
    printf("Process ID: %lu\n", GetCurrentProcessId());
    thread = CreateThread(NULL, 0, threadFunction, NULL, 0, &threadID);

    if (thread == NULL) {
        printf("Thread creation failed. Error: %lu\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(thread, INFINITE);

    CloseHandle(thread);

    return 0;
}

