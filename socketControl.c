#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "inputCmd.h"



#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int socketGetCommand(struct inputCommander *socketMsg)
{
    int c_fd;
    struct sockaddr_in c_addr;
    memset(&c_addr,0,sizeof(c_addr));
    int sof=sizeof(struct sockaddr_in);



    int n_read=read(c_fd,socketMsg->command,sizeof(socketMsg->command));
        if(n_read==-1)
        {
            perror("read");
        }else
        {
            printf("read from clinet: %d\n",n_read);
        }

    return n_read;


}

int socketInit(struct inputCommander *socketMsg,char *ipAdress,char *port)
{
    int s_fd;
	int c_fd;

    struct sockaddr_in s_addr;


    memset(&s_addr,0,sizeof(s_addr));

	//1.socket
	//int socket(int domain, int type, int protocol);
	s_fd=socket(AF_INET,SOCK_STREAM,0);
	if (s_fd==-1)
	{
		perror("socket");
		exit(-1);
	}
    
    s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(atoi(socketMsg->port));
	inet_aton(socketMsg->ipAdress,(struct in_addr *)&s_addr.sin_addr);
    
	//2.bind
	//       int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
	bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));

	//3.listen
	listen(s_fd,10);
    printf("socketServer listening\n");

    socketMsg->sfd=s_fd;
    
    return s_fd;


}
struct inputCommander socketControl=
{   .commandName="socketServer",
    .command={'\0'},
    .port="8082",
    .ipAdress="192.168.31.166",
    .Init=socketInit,
    .getCommand=socketGetCommand,
    .log={'\0'},
    .next=NULL
};


struct inputCommander* addsocketControlToInputCommandLink(struct inputCommander* phead)

{

    if (phead==NULL){
        return &socketControl;

    }
    else{

    socketControl.next=phead;
    phead=&socketControl;
    }


}


