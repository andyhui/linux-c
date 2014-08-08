#include <stdio.h>
#include "msg_server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <wait.h>
#include <errno.h>
#include <sys/select.h>


#define MAXPENDING 5
#define PORT 9999
#define DEBUG 1

#define max(a,b) a>b?a:b

void HandleTCPClient(int clntSocket);

void HandleUDPClient(int udp_sock);


static void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    while((pid = waitpid(-1,&stat,WNOHANG)) >0)
    {
        printf("child %d terminated\n",pid);
    }
    return;
}


static int process_broacast(int servport)
{
    int udp_sock,listenfd,connfd,maxfdp1,nready;
    pid_t childpid;

    fd_set rset;
    socklen_t len;

    int ret = -1;

    const int on = 1;
    int recvMsgSize = -1;
    struct sockaddr_in serv_addr;//服务器端地址
    struct sockaddr_in cliaddr;//客户端地址

    //char hname[128];
    //struct hostent *hent;

    listenfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(servport);


    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    {
        fprintf(stderr,"bind failed.\n");
        exit(1);
    }

    if(listen(listenfd,MAXPENDING) <0)
    {
        fprintf(stderr,"listen failed.\n");
        exit(1);
    }


    if((udp_sock = socket(AF_INET,SOCK_DGRAM,0)) < 0)//建立socket
    {
        printf("create socket error! \t\n");
        exit(-1);
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(servport);


    if((ret = bind(udp_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))) < 0)
    {
        fprintf(stderr,"bind error! \t\n");
        exit(1);
    }

    //gethostname(hname,sizeof(hname));
    //hent = gethostent();

    /**
    int i;
    for(i = 0;hent->h_addr_list[i];i++)
    {
        printf("address is :%s\t",inet_ntoa(*(struct
                        in_addr*)(hent->h_addr_list[i])));
    }

    char *serv_ip = inet_ntoa(*(struct in_addr *)(hent->h_addr_list[0]));

#ifdef DEBUG
    printf("the server ip is: %s\n",serv_ip);
#endif
    **/


    signal(SIGCHLD,sig_chld);

    FD_ZERO(&rset);

    maxfdp1 = max(listenfd,udp_sock) + 1;

    for(;;)
    {
        FD_SET(listenfd,&rset);
        FD_SET(udp_sock,&rset);
        if((nready = select(maxfdp1,&rset,NULL,NULL,NULL)) < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
            else
            {
                fprintf(stderr,"select error.\n");
                exit(1);
            }
        }
        if(FD_ISSET(listenfd,&rset))
        {
            printf("tcp start.\n");
            len = sizeof(cliaddr);
            if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len)) < 0)
            {
                fprintf(stderr,"connect failed.\n");
                exit(1);
            }

            if(0==(childpid = fork()))
            {
                close(listenfd);

                printf("Handling TCP client %s\n",inet_ntoa(cliaddr.sin_addr));

                HandleTCPClient(connfd);

                exit(0);

            }
            close(connfd);
        }

        if(FD_ISSET(udp_sock,&rset))
        {
            HandleUDPClient(udp_sock);
        }

    }
    exit(0);
}

static int process_tcp(unsigned short servPort)
{
    pid_t childpid;
    int servSock;
    int clntSock;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;

    unsigned int clntLen;

    if((servSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
    {
        fprintf(stderr,"create socket error \n");
    }

    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);

    if(bind(servSock,(struct sockaddr *)&servAddr,sizeof(servAddr)) < 0)
    {
        fprintf(stderr,"bind failed!\t\n");
    }

    if(listen(servSock,MAXPENDING) < 0)
    {
        fprintf(stderr,"listen failed! \t\n");
    }

    signal(SIGCHLD,sig_chld);//函数指针做函数参数

    for(;;)
    {
        clntLen = sizeof(clntAddr);

        if((clntSock = accept(servSock,(struct sockaddr *)&clntAddr,&clntLen)) < 0)
        {
            fprintf(stderr,"accept client error! \n");
        }

        if((childpid = fork()) == 0)
        {
            close(servSock);

            printf("Handling client %s\n",inet_ntoa(clntAddr.sin_addr));

            HandleTCPClient(clntSock);

            exit(0);
        }
        close(clntSock);

    }
}

int main(int argc,char *argv[])
{
    unsigned short servport;
    if(argc != 2)
    {
        fprintf(stderr,"Usage : %s <Server Port> \n",argv[0]);
        exit(1);
    }

    servport = atoi(argv[1]);

    process_broacast(servport);

#if 0

    signal(SIGCHLD,sig_chld);
    //process_broacast(servport);

    if((processId = fork()) < 0)
    {
        fprintf(stderr,"fork process error: %d \n",processId);
        exit(1);
    }
    else if(processId == 0)
    {
        process_tcp(tcp_port);
        exit(0);
    }
    else
    {
        process_broacast(servport);
        sleep(10);
        exit(0);
    }
    exit(0);
#endif
}
