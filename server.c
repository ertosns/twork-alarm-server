#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int port = 4321;
//alarm-gpio pin17(lights) pin27(kettle/coffee-machine)
char *CMD_TMPLATE = "alarm-gpio %d %d";

void error(char *msg) {
  printf("Err! %s\n", msg);
}

void flag(int type) {
  int CMD_LEN = strlen(CMD_TMPLATE)-1;
  char buffer[CMD_LEN];
  bzero((void*)&buffer[0],CMD_LEN);
  sprintf(buffer, CMD_TMPLATE, (type>=1)?1:0, (type==2)?1:0);
  printf("gpioing: %s\n",buffer);
  system(buffer);
}

void server() {
  int sockfd, newsockfd, n;
  socklen_t clilen;
  char buffer[1];
  struct sockaddr_in saddr, cli_addr;
  
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error("socket failed");

  bzero((char*) &saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;
  printf("binding...\n");
  if (bind(sockfd,
	   (struct sockaddr*) &saddr,
	   sizeof(struct  sockaddr)) < 0) {
    error("bind failed");
    exit(0);
  }
  
  for (;;) {
    // should binding loop as well?why?
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    printf("port: (%d), listening...\n", port);
    newsockfd = accept(sockfd,
		       (struct sockaddr*) &cli_addr,
		       &clilen);
    if (newsockfd < 0)
      error("failed to accepted connection");

    bzero(buffer, 1);
    read(newsockfd, buffer, 1);
    flag(atoi(&buffer[0]));
    close(newsockfd);
    printf("---------------------------------------\n");
  }  
}

int main() {
  server();
}
