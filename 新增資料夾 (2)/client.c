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
int client(int PID)
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024] = "Hello from client PID:";
    char buffer[1024] = {0};
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
}

void split(int x,int y){
    pid_t child_PID;

    child_PID = fork();
     if(count<1){
        switch(child_PID){
            case -1:
                printf("fork error!");
            case 0:
               //printf("hello, X=%d , Y=%d , now_pid=%d\r\n",x,y++,getpid());
                break;
            default:
                //printf("hello, X=%d , Y=%d , now_pid=%d\r\n",x,y++,getpid());
                //printf("hello, X=%d , Y=%d , child_pid=%d\r\n",x,y++,child_PID);
                client(child_PID);
                count++;
                sleep(10);
        }
      }
}
int main(){
        int x = 0,y = 0;
        //printf("hello, X=%d , Y=%d , now_pid=%d \r\n",x,y++,getpid());
        split(x,y);
        split(x,y);
        split(x,y);
        while(1);
        return 0;

}
