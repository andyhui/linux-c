#include <stdio.h>      
#include <sys/socket.h> 
#include <unistd.h>
#include <stdlib.h>
#include "HandleTCPClient.h"
using namespace std;
#define RCVBUFSIZE 2048   
#define size 100

void DieWithError(const char *errorMessage);

void HandleAdmin(MYSQL* mysql, int clntSocket, administrator admin)
{
    MYSQL_RES* resPtr;
    char echoBuffer[RCVBUFSIZE];        
    int recvMsgSize;
    
    for(;;)
    {
        if (echoBuffer[2]==1)//管理员添加课程
		{
		    int cid;
		    char name[size];
		    int credit;
		    int course_hours;
		    int tid;
		    char course_type[size];
		    
		    memcpy(&cid, echoBuffer+3, sizeof(cid));
		    memcpy(name, echoBuffer+7, size);
		    memcpy(&credit, echoBuffer+7+size, 4);
		    memcpy(&course_hours, echoBuffer+11+size, 4);
		    memcpy(&tid, echoBuffer+15+size, 4);
		    memcpy(course_type, echoBuffer+19+size, size);
		    
			if(admin.add_course(mysql, cid, name, credit, course_hours, tid, course_type))
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

		else if (echoBuffer[2]==2)//管理员删除课程
		{
            int course_id;
			memcpy(&course_id, &echoBuffer[3], sizeof(course_id));

			if(admin.del_course(mysql, course_id))//失败
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
		else if (echoBuffer[2]==3)//更改
		{
		    int cid;
		    char name[size];
		    int credit;
		    int course_hours;
		    int tid;
		    char course_type[size];
		    
		    memcpy(&cid, echoBuffer+3, sizeof(cid));
		    memcpy(name, echoBuffer+7, size);
		    memcpy(&credit, echoBuffer+7+size, 4);
		    memcpy(&course_hours, echoBuffer+11+size, 4);
		    memcpy(&tid, echoBuffer+15+size, 4);
		    memcpy(course_type, echoBuffer+19+size, size);
		    
			if(admin.update_course(mysql, cid, name, credit, course_hours, tid, course_type))//参数未设定
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

/*		else if (echoBuffer[2]==4)//admin_view_course
		{
			//do sth
    		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
           	 	DieWithError("send() failed");		
		}*/

		else if (echoBuffer[2]==5)//增加老师
		{
		    int tid;
		    char name[size];
		    char teach_sex[size];
		    char phone[size];
		    char title[size];
		    char department[size];
		    char birth[size];
		    
		    memcpy(&tid, echoBuffer+3, sizeof(tid));
		    memcpy(name, echoBuffer+7, size);
		    memcpy(teach_sex, echoBuffer+7+size, size);
		    memcpy(phone, echoBuffer+7+2*size, size);
		    memcpy(title, echoBuffer+7+3*size, size);
		    memcpy(department, echoBuffer+7+4*size, size);
		    memcpy(birth, echoBuffer+7+5*size, size);
		    
			if(admin.add_teacher(mysql, tid, name, teach_sex, phone, title, department, birth))//参数未设定
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
		else if (echoBuffer[2]==6)//删除老师
		{
			int teacherId;
			memcpy(&teacherId, &echoBuffer[3], sizeof(teacherId));

			if(admin.del_teacher(mysql, teacherId))//失败,加id
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
		else if (echoBuffer[2]==7)//增加学生
		{
            int sid;
            char name[size];
            char sex[size];
            char classid[size];
            char birth[size];
            
            memcpy(&sid, echoBuffer+3, 4);
            memcpy(name, echoBuffer+7, size);
            memcpy(sex, echoBuffer+7+size, size);
            memcpy(classid, echoBuffer+7+2*size, size);
            memcpy(birth, echoBuffer+7+3*size, size);
            
			if(admin.add_student(mysql, sid, name, sex, classid, birth))//未完成，参数未加
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
		else if (echoBuffer[2]==8)//删除学生
		{
			int studentId;
			memcpy(&studentId, &echoBuffer[3], sizeof(studentId));

			if(admin.del_student(mysql, studentId))//失败,加id
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

		else if (echoBuffer[2]==9)//logout
		{
			Logout(mysql);
			exit(0);
		}

		else if (echoBuffer[2]==10)//增加可注册ID
		{
			int addId;
			memcpy(&addId, &echoBuffer[3], sizeof(addId));

			if(AddUserInfo(mysql, addId))//失败,加id
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

		else if (echoBuffer[2]==11)//删除可注册ID
		{
			int deleteId;
			memcpy(&deleteId, &echoBuffer[3], sizeof(deleteId));

			if(DeleteUserInfo(mysql, deleteId))//失败,加id
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
