#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int i=0;
int new_fd[3]={1,1,1};

int main(){
        int sockfd,numbytes;
        struct sockaddr_in my_addr;
        struct sockaddr_in their_addr;
        int sin_size;
        char buf[2048];
        char *hello ="From server";
        char *work ="5";
        char *m="stop connect to server!";

        //TCP socket
        if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
                perror("socket");
                exit(1);
        }

        //Initail, bind to port 2323
        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(2323);
        my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        bzero( &(my_addr.sin_zero), 8 );

        //binding
        if ( bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
                perror("bind");
                exit(1);
        }

        //Start listening
        if ( listen(sockfd, 10) == -1 ){
                perror("listen");
                exit(1);
        }

        //Wait for connect!
        while(1){
                new_fd[i]=0;
                sin_size = sizeof(struct sockaddr_in);
                perror("server is run");
                if ( (new_fd[i] = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) == -1 ){
                        perror("accept");
                        exit(1);
                }
                        //Receive
                        if ( (numbytes = read(new_fd[i], buf,1024 )) == -1 ){
                                perror("recv");
                                exit(1);
                        }
                        printf("Receive %d bytes\n", numbytes);
                        printf("%s\n", buf);
                        //Send back
                        if ( (numbytes = send(new_fd[i],hello , strlen(hello),0)) == -1){
                                perror("send");
                                exit(0);
                        }
                        printf("Send %d bytes\n", numbytes);
                        if(i<3){
                                i++;
                        }
                        int j=0;
                        if(i==3){
                           while(1){
                                for(j=0;j<i;j++){
                                        if ( (numbytes = send(new_fd[j],work , strlen(hello),0))==-1){
                                                perror("send");
                                                exit(0);
                                        }
                                        if ( (numbytes = read(new_fd[i], buf,1024 )) == -1 ){
                                                perror("recv");
                                                exit(1);
                                        }
                                        if(!strcmp(buf,"0")){
                                                send(new_fd[j],m,strlen(m),0);
                                        }
                                }
                                sleep(10);
                            }
                        }
        }
        close(sockfd);
        return 0;
}

