#include <stdio.h>      
#include <sys/socket.h> 
#include <unistd.h>  
#include <stdlib.h>
#include "HandleTCPClient.h"
using namespace std;
#define RCVBUFSIZE 2048   
#define size 100

void DieWithError(const char *errorMessage);

void HandleStudent(MYSQL* mysql, int clntSocket, student stu)
{
    MYSQL_RES* resPtr;
    char echoBuffer[RCVBUFSIZE];        
    int recvMsgSize;
    int sid = stu.student_id;
    for(;;)
    {
        memset(echoBuffer, 0, RCVBUFSIZE);
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
        if (echoBuffer[2]==1)//student_select_course
		{
		    int courseId;
			memcpy(&courseId, &echoBuffer[3], sizeof(courseId));

			if(stu.selectCourse(mysql, courseId, sid))//失败
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

		else if (echoBuffer[2]==2)//student_delete_course
		{
            int courseId;
			memcpy(&courseId, &echoBuffer[3], sizeof(courseId));

			if(stu.deleteCourse(mysql, courseId, sid))//失败
			{
				memset(echoBuffer, 0, RCVBUFSIZE);				
           	    echoBuffer[0] = 1;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");	    
			}
			else//成功
			{
				memset(echoBuffer, 0, RCVBUFSIZE);	
           	    echoBuffer[0] = 0;
           	    if (send(clntSocket, echoBuffer, RCVBUFSIZE, 0) != RCVBUFSIZE)
           	 	    DieWithError("send() failed");		
			}

		}
		else if (echoBuffer[2]==3)//student_view_course
		{
    		resPtr = stu.veiwCourse(mysql);
    		if (resPtr)
    		{
        		if(resPtr->row_count == 0)
        		{
					memset(echoBuffer, 0, RCVBUFSIZE);				
           	    	echoBuffer[0] = 1;//失败
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
		else if (echoBuffer[2]==4)//student_view_score
		{
    		resPtr = stu.queryScore(mysql, stu.student_id);//查看所有课程成绩
    		if (resPtr)
    		{
        		if(resPtr->row_count == 0)
        		{
					memset(echoBuffer, 0, RCVBUFSIZE);				
           	    	echoBuffer[0] = 1;//失败
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

		else if (echoBuffer[2]==5)//logout
		{
			Logout(mysql);
			exit(0);
		}

		else if  (echoBuffer[2]==6)//更换email
		{
			char addr[size]={0};
			memcpy(addr, &echoBuffer[3], size);

			if(ChangeMailAddr(mysql, sid, addr))//失败
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

		else if  (echoBuffer[2]==7)//更换密码
		{
			char pw[size]={0};
			memcpy(pw, &echoBuffer[3], size);

			if(ChangeMailAddr(mysql, sid, pw))//失败
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
