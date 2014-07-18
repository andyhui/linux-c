#include <stdio.h>      
#include <sys/socket.h> 
#include <unistd.h>
#include <stdlib.h>
#include "HandleTCPClient.h"

using namespace std;
#define RCVBUFSIZE 2048   
#define size 100

void DieWithError(const char *errorMessage);

void HandleTeacher(MYSQL* mysql, int clntSocket, teacher teacher1)
{
    char echoBuffer[RCVBUFSIZE];        
    int recvMsgSize;
    for(;;)
    {
        memset(echoBuffer, 0, RCVBUFSIZE);
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
        if (echoBuffer[2]==1)//老师布置作业
		{
		    char name[size];
		    char time[size];
		    int cid;
		    
		    memcpy(name, echoBuffer+3, size);
		    memcpy(time, echoBuffer+size+3, size);
		    memcpy(&cid, echoBuffer+(2*size)+3, sizeof(cid));
		    
			if(teacher1.arrange_homework(mysql, name, time, cid))
			{
				memset(echoBuffer, 0, RCVBUFSIZE);				
           	    echoBuffer[0] = 1;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");	    
			}
			else
			{
				memset(echoBuffer, 0, RCVBUFSIZE);	
           	    echoBuffer[0] = 0;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");		
			}
		}

		else if (echoBuffer[2]==2)//老师打分
		{
		    int sid;
		    int hid;
		    int score;
		    
		    memcpy(&sid, echoBuffer+3, 4);
		    memcpy(&hid, echoBuffer+7, 4);
		    memcpy(&score, echoBuffer+11, 4);
		    
			if(teacher1.get_points(mysql, sid, hid, score))
			{
				memset(echoBuffer, 0, RCVBUFSIZE);				
           	    echoBuffer[0] = 1;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");	    
			}
			else
			{
				memset(echoBuffer, 0, RCVBUFSIZE);	
           	    echoBuffer[0] = 0;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");		
			}	
		}
		else if (echoBuffer[2]==3)//老师查看选此课程学生情况
		{

		    int cid;
            MYSQL_RES* resPtr;
			memcpy(&cid, echoBuffer+3, sizeof(cid));

    		resPtr = teacher1.view_courses(mysql, cid);
    		if (resPtr)
    		{
        		if(resPtr->row_count == 0)
        		{
					memset(echoBuffer, 0, RCVBUFSIZE);				
           	    	echoBuffer[0] = 1;
           	    	if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    	DieWithError("send() failed");	
        		}
        	    else
        	    {
                    memset(echoBuffer, 0, RCVBUFSIZE);	
           	        echoBuffer[0] = 0;
            	    MYSQL_ROW row;
            	    int i;
            	    int numrow = mysql_num_rows(resPtr);
            	    int numcolumn = mysql_field_count(mysql);
            	    echoBuffer[1] = numrow;
            	    echoBuffer[2] = numcolumn;
            	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	        DieWithError("send() failed");	
           	 	    
            	    while((row = mysql_fetch_row(resPtr)))
            	    {
                	    for(i = 0; i < numcolumn; i++)
                	    {
                    	    sprintf(echoBuffer, "%s", row[i]);
                    	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	                DieWithError("send() failed");	
                	    }
            	    }
        	    }
        	    mysql_free_result(resPtr);
        	}
		}

		else if (echoBuffer[2]==4)//logout
		{
			Logout(mysql);
			exit(0);
		}

		else if  (echoBuffer[2]==5)//更换email
		{
			char addr[size]={0};
			memcpy(addr, echoBuffer+3, size);

			if(ChangeMailAddr(mysql, teacher1.teacher_id, addr))//失败
			{
				memset(echoBuffer, 0, RCVBUFSIZE);				
           	    echoBuffer[0] = 1;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");	    
			}
			else
			{
				memset(echoBuffer, 0, RCVBUFSIZE);	
           	    echoBuffer[0] = 0;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");		
			}
			
		}

		else if  (echoBuffer[2]==6)//更换密码
		{
			char pw[size]={0};
			memcpy(pw, echoBuffer+3, size);

			if(ChangeMailAddr(mysql, teacher1.teacher_id, pw))//失败
			{
				memset(echoBuffer, 0, RCVBUFSIZE);				
           	    echoBuffer[0] = 1;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");	    
			}
			else
			{
				memset(echoBuffer, 0, RCVBUFSIZE);	
           	    echoBuffer[0] = 0;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");		
			}
			
		}
	}
}
