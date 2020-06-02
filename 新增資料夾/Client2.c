#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>
#define PORT 2323

int count = 0;
int main(){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024] = "Hello from client PID:";
    char buffer[1024] = {0};
    int PID = getpid();
    char pid [1024];
    sprintf(pid ,"%d",PID);
    strcat(hello,pid);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer);
    while(1){

        printf("Enter:");
        scanf("%s",&buffer);
        send(sock,buffer,strlen(buffer),0);
        if(!strcmp(buffer,"exit")){
          close(sock);
          printf("Disconnect to Server\n");
          exit(1);
        }

    }
}

