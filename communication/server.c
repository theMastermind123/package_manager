#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    int server_fd;

    // Create IPv4 / TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Cannot create TCP socket");
        exit(1);
    }

    // Define the bind address
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(2000);

    if (bind(server_fd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {

        perror("Failed to bind to the socket");
        close(server_fd);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) < 0) {
        perror("Cannot listen for incoming connections");
        close(server_fd);
        exit(1);
    }

    printf("Server listening on 0.0.0.0:2000\n");

    // Accept a connection
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_fd = accept( server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_fd < 0) {
        perror("Cannot accept client connection");
        close(server_fd);
        exit(1);
    }

    printf("Client connected!\n");

    // Send and receive messages
    char receive_buffer[1024];
    char send_buffer[1024];

    while (1) {


        int received_bytes = recv(client_fd, receive_buffer, sizeof(receive_buffer) - 1, 0);

        if (received_bytes <= 0) {
            printf("Client disconnected\n");
            break;
        }

        receive_buffer[received_bytes] = '\0';


        if (!fgets(send_buffer, sizeof(send_buffer), stdin)) {
            break;
        }

        send(client_fd, send_buffer, strlen(send_buffer), 0);

		printf("Client: %s", receive_buffer);

    }

    close(client_fd);
    close(server_fd);

    return 0;
}
