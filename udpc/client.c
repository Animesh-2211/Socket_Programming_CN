#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
  int client_socket;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE];

  // Create socket
  if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Configure server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address");
    exit(EXIT_FAILURE);
  }

  while (1) {
    printf("Enter a message: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Send data to server
    sendto(client_socket, buffer, strlen(buffer), 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));
  }

  close(client_socket);
  return 0;
}