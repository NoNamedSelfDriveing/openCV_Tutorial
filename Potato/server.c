#include <sys/poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>		// added ver.2
#include <netdb.h>				// added ver.2
#include <string.h>
#include <arpa/inet.h>

#define SIZE sizeof(struct sockaddr_in)
#define MAX_CONN 1000
#define MAX_MSG 500

struct pollfd events[MAX_CONN];

void closesock(int sig);

int sock_service(int slot)
{
    int i;
    char buf[MAX_MSG];
    int cli_sock = events[slot].fd;

    if(recv(cli_sock, buf, MAX_MSG, 0) < 0)
        perror("client recv");

    printf("[%d] : %s\n", events[slot], buf);

    if(send(cli_sock, buf, MAX_MSG, 0) < 0)
        perror("server send");

    for(i = 0; i<MAX_CONN; i++){
        fprintf(stdout, "%d\n", events[i]);
    }
}

int main(int argc, char *argv[]){
    int sockfd, poll_state, sockfd_connect, i, slot = 1, client_sock;
    char msg[MAX_MSG];
    struct utsname info;
    struct sockaddr_in server = {AF_INET, 5000, INADDR_ANY};
    struct sockaddr_in client;			// added ver.2
    int client_len = sizeof(client);		// added ver.2
    struct sigaction act;
    struct hostent *hent;			// added ver.2 
    uname(&info);
    printf("HOST name : %s\n", info.nodename);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("fail to call socket\n");
        exit(1);
    }

    if(bind(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
        printf("fail to call bind\n");
        exit(2);
    }

    if(listen(sockfd, MAX_CONN) == -1)
    {
        printf("fail to call listen()\n");
        exit(3);
    }

    //server gate events[0]
    events[0].fd = sockfd;
    events[0].events = POLLIN;
    events[0].revents = 0;

    for(i = 1; i < MAX_CONN; i++) events[i].fd = -1;

    while(1)
    {
        poll_state = poll((struct pollfd*)&events, 
                MAX_CONN,
                1000);


        if(events[0].revents & POLLIN){
            if( (client_sock = accept(sockfd, (struct sockaddr*)&client, &client_len)) < 0){
                perror("Gate accept()");
                exit(404);
            }

            fprintf(stdout, "----------Accepted\n");
            fprintf(stdout, "IP : %s\n", inet_ntoa(client.sin_addr));
            events[slot].fd = client_sock;
            events[slot++].events = POLLIN;

            if(slot > MAX_CONN){
                for( i = 1; i < MAX_CONN; i++){
                    if(events[i].fd == -1)
                        slot = i;
                }
            }
        }

        else{
            for(i = 1; i < MAX_CONN; i++){
                if(events[i].revents&POLLIN){
                    sock_service(i);
                }
            }
        }
    }
}
