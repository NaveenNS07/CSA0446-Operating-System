#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#sripurushothaman
#define SHM_KEY 1234 // Key for shared memory
#define SHM_SIZE 1024 // Shared memory size

struct SharedData {
    char message[100];
    int flag; // 0 = empty, 1 = data available
};

void writer() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory creation failed");
        exit(1);
    }

    struct SharedData *shared = (struct SharedData *)shmat(shmid, NULL, 0);
    if (shared == (void *)-1) {
        perror("Shared memory attachment failed");
        exit(1);
    }

    printf("Writer: Enter a message: ");
    fgets(shared->message, sizeof(shared->message), stdin);
    shared->message[strcspn(shared->message, "\n")] = '\0'; // Remove newline character
    shared->flag = 1; // Indicate data is ready

    printf("Writer: Message written to shared memory: %s\n", shared->message);

    shmdt(shared); // Detach shared memory
}

void reader() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("Shared memory access failed");
        exit(1);
    }

    struct SharedData *shared = (struct SharedData *)shmat(shmid, NULL, 0);
    if (shared == (void *)-1) {
        perror("Shared memory attachment failed");
        exit(1);
    }

    printf("Reader: Waiting for data...\n");

    // Wait until writer sets flag to 1
    while (shared->flag == 0);

    printf("Reader: Message read from shared memory: %s\n", shared->message);
    shared->flag = 0; // Reset flag after reading

    shmdt(shared); // Detach shared memory

    // Remove shared memory segment
    shmctl(shmid, IPC_RMID, NULL);
}

int main() {
    int choice;
    printf("Choose an option:\n1. Writer\n2. Reader\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline left by scanf

    if (choice == 1) {
        writer();
    } else if (choice == 2) {
        reader();
    } else {
        printf("Invalid choice. Exiting.\n");
    }

    return 0;
}
