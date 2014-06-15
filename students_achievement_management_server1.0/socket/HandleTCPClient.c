#include <stdio.h>      
#include <sys/socket.h> 
#include <unistd.h>     

#define RCVBUFSIZE 2048   

void DieWithError(char *errorMessage);

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];        
    int recvMsgSize;                   

 	unsigned char len;
	
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

  	len = echoBuffer[0];
	//student
	if(echoBuffer[1]==1)
	{
		if(echoBuffer[2]==0)//student_login
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");
		}
		else if (echoBuffer[2]==1)//student_select_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}

		else if (echoBuffer[2]==2)//student_delete_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==3)//student_view_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==4)//student_view_score
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
			
	} 

	//teacher 
	else if(echoBuffer[1]==2)
	{
		if(echoBuffer[2]==0)//teacher_login
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");
		}
		else if (echoBuffer[2]==1)//teacher_arrage_homework
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}

		else if (echoBuffer[2]==2)//teacher_set_point
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==3)//teacher_view_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}

	}

	//admin
	else if(echoBuffer[1]==3)
	{

		if(echoBuffer[2]==0)//admin_login
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");
		}
		else if (echoBuffer[2]==1)//admin_add_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}

		else if (echoBuffer[2]==2)//admin_delete_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==3)//admin_change_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==4)//admin_view_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==5)//admin_add_teacher
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==6)//admin_delete_teacher
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==7)//admin_add_student
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}
		else if (echoBuffer[2]==8)//admin_delete_teacher
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}

	}






    close(clntSocket);  
}
