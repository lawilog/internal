#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
  
int main(int argc, char const *argv[])
{
  if(argc <= 2)
  {
    printf("usage: %s IP port\n", argv[0]);
    return 0;
  }
  const char* ip = argv[1];
  const int port = atoi(argv[2]);
  
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
  {
    printf("failed: socket\n");
    return 1;
  }
  
  struct sockaddr_in serv_addr;
  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
    
  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) 
  {
    printf("error: Invalid address/ Address not supported\n");
    return 1;
  }

  if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("failed: connect\n");
    return 1;
  }
  printf("* socket created, connected to ip %s on port %i\n", ip, port);
  
  while(1)
  {
    time_t t; time(&t);
    struct tm* tm = localtime(&t);
    
    char zeit[128];
    strftime(zeit, sizeof(zeit), "%c", tm);
    
    printf("* sending \"%s\"... ", zeit); fflush(stdout);
    ssize_t s = send(sock, zeit, strlen(zeit), 0);
    if(s > 0)
      printf("* sent\n");
    else
    {
      printf("* failed to send\n");
      break;
    }
    
    printf("* reading... "); fflush(stdout);
    char buffer[1024] = {0};
    int valread = read(sock, buffer, 1024);
    if(valread > 0)
      printf("* read message saying: \"%s\"\n", buffer);
    else
    {
      printf("* end\n");
      break;
    }
    
    sleep(1);
  }
  
  return 0;
}
