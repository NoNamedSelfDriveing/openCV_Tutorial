#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>		// added ver.2
#include <netdb.h>				// added ver.2
#include <string.h>

#define SIZE sizeof(struct sockaddr_in)

void closesock(int sig);

int sockfd_connect;

int main(int argc, char *argv[]){
    int sockfd;
    char msg[50];
    struct utsname info;
    struct sockaddr_in server = {AF_INET, 5000, INADDR_ANY};
    struct sockaddr_in client;			// added ver.2
    int client_len = SIZE;				// added ver.2
    struct sigaction act;
    struct hostent *hent;				// added ver.2

    uname(&info);
    printf("node name : %s\n", info.nodename);
    // print <node name> added ver.2

    /*
       hent = gethostbyname(info.nodename);
       printf("official name : %s\n", hent->h_name);
    // print <hent->h_name (official name)> added ver.2
    */

    act.sa_handler = closesock;
    sigfillset(&(act.sa_mask));
    sigaction(SIGPIPE, &act, NULL);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("fail to call socket\n");
        exit(1);
    }

    if(bind(sockfd, (struct sockaddr *)&server, SIZE) == -1){
        printf("fail to call bind\n");
        exit(2);
    }

    if(listen(sockfd, 5) == -1){
        printf("fail to call listen()\n");
        exit(3);
    }

    while(1){
        if((sockfd_connect = accept(sockfd, NULL,NULL)) == -1){
            printf("fail to call accept()\n");
            exit(4);
        }

        printf("accepted\n");
        while(recv(sockfd_connect, &msg, 500, 0) > 0){
            send(sockfd_connect, &msg, 500, 0);
            printf("\nRecv : %s\n", msg);
        }

        printf("close(sockfd_connect)\n");
        close(sockfd_connect);

    }
}

void respond_service(sockfd_connect)
{
    char msg[500];
}
