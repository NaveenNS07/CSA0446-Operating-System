#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF_SIZE 1024  

int main() {
    int src_fd, dest_fd;          
    ssize_t bytes_read, bytes_written;
    char buffer[BUF_SIZE];        

    src_fd = open("source.txt", O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);  
        return 1;
    }

    while ((bytes_read = read(src_fd, buffer, BUF_SIZE)) > 0) {
        ssize_t total_written = 0;
        while (total_written < bytes_read) {
            bytes_written = write(dest_fd, buffer + total_written, bytes_read - total_written);
            if (bytes_written == -1) {
                perror("Error writing to destination file");
                close(src_fd);
                close(dest_fd);
                return 1;
            }
            total_written += bytes_written;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading source file");
        close(src_fd);
        close(dest_fd);
        return 1;
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
    return 0;
}

