#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#sripurushothaman V 192324114
#define QUEUE_KEY 1234

struct Message {
    long messageType; 
    char content[100];
};

void sender() {
    int msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Message queue creation failed");
        exit(1);
    }

    struct Message message;
    message.messageType = 1; 

    printf("Enter a message to send: ");
    fgets(message.content, sizeof(message.content), stdin);
    message.content[strcspn(message.content, "\n")] = '\0'; 

    if (msgsnd(msgid, &message, sizeof(message.content), 0) == -1) {
        perror("Message send failed");
        exit(1);
    }

    printf("Message sent: %s\n", message.content);
}

void receiver() {
    int msgid = msgget(QUEUE_KEY, 0666);
    if (msgid == -1) {
        perror("Message queue access failed");
        exit(1);
    }

    struct Message message;

    if (msgrcv(msgid, &message, sizeof(message.content), 1, 0) == -1) {
        perror("Message receive failed");
        exit(1);
    }

    printf("Message received: %s\n", message.content);

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("Message queue removal failed");
        exit(1);
    }
}

int main() {
    int choice;
    printf("Choose an option:\n1. Sender\n2. Receiver\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); 

    if (choice == 1) {
        sender();
    } else if (choice == 2) {
        receiver();
    } else {
        printf("Invalid choice. Exiting.\n");
    }

    return 0;
}
