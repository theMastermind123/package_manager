#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    int client_fd;
    int port = 2000;

    char *server_address = "127.0.0.1";

    char send_buffer[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    struct sockaddr_in server_addr;

    // Create IPv4 / TCP socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Cannot create TCP socket");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_address, &server_addr.sin_addr) <= 0) {
        perror("inet_pton error");
        close(client_fd);
        exit(1);
    }

    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Can't connect");
        close(client_fd);
        exit(1);
    }

    printf("Connected to %s:%d\n", server_address, port);

    while (1) {

        if (!fgets(send_buffer, sizeof(send_buffer), stdin)) {
            break;
        }

        // Send user input
        send(client_fd, send_buffer, strlen(send_buffer), 0);

        // Receive response
        int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received <= 0) {
            printf("Server disconnected\n");
            break;
        }

        buffer[bytes_received] = '\0';

        printf("Server: %s", buffer);
    }

    close(client_fd);

    return 0;
}
