#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" 
#define SERVER_PORT 12345

#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Enter a message: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Send the message to the server
    if (sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Sendto failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Receive the echoed message from the server
    socklen_t server_addr_len = sizeof(server_addr);
    ssize_t bytes_received = recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, &server_addr_len);
    if (bytes_received == -1) {
        perror("Recvfrom failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Echoed message from server: %.*s", (int)bytes_received, buffer);

    close(client_socket);
    return 0;
}