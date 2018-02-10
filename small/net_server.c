// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[])
{
  if(argc <= 1)
  {
    printf("usage: %s port\n", argv[0]);
    return 0;
  }
  const int port = atoi(argv[1]);
  
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(server_fd == 0)
  {
    printf("failed: socket\n");
    return 1;
  }
    
  int opt = 1;
  if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    printf("failed: setsockopt\n");
    return 1;
  }
  
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
  {
    printf("failed: bind\n");
    return 1;
  }
  printf("# socket created, listening on port %i\n", port);
  
  if(listen(server_fd, 3) < 0)
  {
    printf("failed: listen\n");
    return 1;
  }
  
  int addrlen = sizeof(address);
  unsigned totlen = 0;
  while(1)
  {
    printf("# accepting... "); fflush(stdout);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if(new_socket < 0)
    {
      printf("failed: accept\n");
      return 1;
    }
    printf("# accepted\n");
    
    while(1)
    {
      printf("# reading... "); fflush(stdout);
      char buffer[1024] = {0};
      ssize_t len = read(new_socket, buffer, sizeof(buffer));
      if(len <= 0)
      {
        printf("# disconnect\n");
        break;
      }
      totlen += len;
      printf("# read message saying: \"%s\" (%u bytes since startup)\n", buffer, totlen);
      
      printf("# sending echo... "); fflush(stdout);
      ssize_t s = send(new_socket, buffer, len, 0); // echo the message back
      if(s > 0)
        printf("# sent\n");
      else
      {
        printf("# failed to send\n");
        break;
      }
    }
  }
  
  return 0;
}
