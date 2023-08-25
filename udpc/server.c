#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
  int server_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);
  char buffer[BUFFER_SIZE];

  // Create socket
  if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Configure server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Bind socket to address
  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) == -1) {
    perror("Binding failed");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", PORT);

  while (1) {
    // Receive data from client
    int bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE, 0,
                                  (struct sockaddr *)&client_addr, &client_len);
    if (bytes_received == -1) {
      perror("Error receiving data");
      continue;
    }

    buffer[bytes_received] = '\0';
    printf("Received from %s:%d: %s", inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port), buffer);
  }

  close(server_socket);
  return 0;
}