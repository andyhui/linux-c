#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>    
#include <string.h>   
#include <unistd.h>     
#include "Infor.h"

#define RCVBUFSIZE 2048
#define size 100

void DieWithError(char *errorMessage);




int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr; 
    unsigned short echoServPort; 
    char *servIP;  
    char *echoString;  
    char echoBuffer[RCVBUFSIZE]; 
    unsigned int echoStringLen;  
    int bytesRcvd, totalBytesRcvd;
	unsigned char len;

	char cm1[size]="student_login";
	char cm2[size]="student_select_course";
	char cm3[size]="student_delete_course";
	char cm4[size]="student_view_course";
	char cm5[size]="student_view_score";

	char cm6[size]="teacher_login";
	char cm7[size]="teacher_arrage_homework";
	char cm8[size]="teacher_set_point";
	char cm9[size]="teacher_view_course";

	char cm10[size]="admin_login";
	char cm11[size]="admin_add_course";
	char cm12[size]="admin_delete_course";
	char cm13[size]="admin_change_course";
	char cm14[size]="admin_view_course";
	char cm15[size]="admin_add_teacher";
	char cm16[size]="admin_delete_teacher";
	char cm17[size]="admin_add_student";
	char cm18[size]="admin_delete_teacher";

    if ((argc < 2) || (argc > 3)) 
    {
       fprintf(stderr, "Usage: %s <Server IP> [<Echo Port>]\n",
               argv[0]);
       exit(1);
    }

    servIP = argv[1];

    if (argc == 3)
        echoServPort = atoi(argv[2]); 
    else
        echoServPort = 8888; 

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    memset(&echoServAddr, 0, sizeof(echoServAddr)); 
    echoServAddr.sin_family      = AF_INET;           
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   
    echoServAddr.sin_port        = htons(echoServPort); 


    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

	
	for(;;)
	{	
		int state;
		char a[size]={0};
		int b;
		char c[size]={0};
		scanf("%s %d %d", a,&b,c);
		
		if(memcmp(cm1, a,size)==0)
			state = 1;
		else if(memcmp(cm2, a,size) ==0)
			state = 2;
		else if(memcmp(cm3, a,size) ==0)
			state = 3;
		else if(memcmp(cm4, a,size) ==0)
			state = 4;
		else if(memcmp(cm5, a,size) ==0)
			state = 5;
		else if(memcmp(cm6, a,size) ==0)
			state = 6;
		else if(memcmp(cm7, a,size) ==0)
			state = 7;
		else if(memcmp(cm8, a,size) ==0)
			state = 8;
		else if(memcmp(cm9, a,size) ==0)
			state = 9;
		else if(memcmp(cm10, a,size) ==0)
			state = 10;
		else if(memcmp(cm11, a,size) ==0)
			state = 11;
		else if(memcmp(cm12, a,size) ==0)
			state = 12;
		else if(memcmp(cm12, a,size) ==0)
			state = 13;
		else if(memcmp(cm12, a,size) ==0)
			state = 14;
		else if(memcmp(cm12, a,size) ==0)
			state = 15;
		else if(memcmp(cm12, a,size) ==0)
			state = 16;
		else if(memcmp(cm12, a,size) ==0)
			state = 17;
		else if(memcmp(cm12, a,size) ==0)
			state = 18;


		switch (state)
		{
			case 1://student login
				userInfor.userId = b;
				userInfor.password = c;

				echoStringLen = sizeof(struct USERINFOR);
				echoBuffer[1]=1;
				echoBuffer[1]=0;						
				memcpy(echoBuffer+3, &userInfor.userId, sizeof(userInfor.userId));
				memcpy(echoBuffer+sizeof(userInfor.userId), &userInfor.password, sizeof(userInfor.password));
		
				//unsigned char len
				len = 
				echoBuffer[0] = len;				

				if (send(sock, echoBuffer, len, 0) != len)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
        			DieWithError("rmanecv() failed or connection closed prematurely");

				if(echoBuffer[0]==0)
					printf("login failed\n");
				else 
					printf("login success\n");
			break;
		
			case 2://student_select_course
				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=1;	
				echoBuffer[2]=1;	
			

				if (send(sock, echoBuffer, len, 0) != len)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
        			DieWithError("rmanecv() failed or connection closed prematurely");


			break;

			case 3://student_delete_course
				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=1;	
				echoBuffer[2]=2;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");


			break;

			case 4://student_view_course

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=1;	
				echoBuffer[2]=3;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
												
			break;

			case 5://student_view_score
		
				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=1;	
				echoBuffer[2]=4;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
			break;

			case 6://teacher_login
				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=2;	
				echoBuffer[2]=0;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
			break;
			
			case 7://teacher_arrage_homework
				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=2;	
				echoBuffer[2]=1;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
			break;

			case 8://teacher_set_point
				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=2;	
				echoBuffer[2]=2;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
			break;

			case 9://teacher_view_course

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=2;	
				echoBuffer[2]=3;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");

				break;

			case 10://admin_login

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=0;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
			case 11://admin_add_course

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=1;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
				break;					

			case 12://admin_delete_course

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=2;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
								
				break;
			case 13://admin_change_course

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=3;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
								
				break;
			case 14://admin_view_course

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=4;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
								
				break;
			case 15://admin_add_teacher
				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=5;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
								
				break;
			case 16://admin_delete_teacher

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=6;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
								
				break;
			case 17://admin_add_student

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=7;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
								
				break;
			case 18://admin_delete_teacher

				//unsigned char len
				len = 
				echoBuffer[0] = len;			
				echoBuffer[1]=3;	
				echoBuffer[2]=8;	


		    	if (send(sock, echoBuffer, echoStringLen, 0) != echoStringLen)
        			DieWithError("send() sent a different number of bytes than expected");

				if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            		DieWithError("recv() failed or connection closed prematurely");
								
				break;

			default:
				break;
		}
			
	}

    close(sock);
    exit(0);
}	


