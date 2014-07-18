#include <iostream>
#include <stdio.h>
#include <string.h>
#include "teacher.h"
#include <mysql/mysql.h>

using namespace std;

const int MAXLEN = 1024;

MYSQL_RES* teacher::view_courses(MYSQL* mysql, int cid)
{
	/*显示课程号，查询课程*/
	char buf[MAXLEN] = {0};
	int res = 0;
	MYSQL_RES* resPtr;
	sprintf(buf,"select * from student where id in (select sid in select_course where cid = %d)\n", cid);
	res = mysql_query(mysql,buf);
	if(res == 0)
	{
		resPtr = mysql_store_result(mysql);
        return resPtr;
	}
	else
	{
	    return NULL;
	}
	/*显示所有的学生信息*/
}

int teacher::arrange_homework(MYSQL* mysql, char* name, char* time, int cid)
{
	/*安排课后作业,写作业id，课程号，布置时间*/
	printf("in the arrange_homework \n");
	//printf("name is %s cid is %d \n",name,cid);
	char buf[MAXLEN] = {0};
    char* command;
	int res = 0;
    MYSQL_RES* resPtr;
	sprintf(buf,"select * from homework where name = '%s' and cid = %d\n", name,cid);
    command = strtok(buf,"\n");
	res = mysql_query(mysql,command);
    resPtr = mysql_store_result(mysql);
	if(resPtr->row_count != 0)
	{
		printf("the homework is exist\n");
		return 1;
	}
	else
	{
	    printf("the homework is not exist\n");
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into homework (name, arrange_time, cid) values ('%s','%s',%d)\n", name,time,cid);
		command = strtok(buf,"\n");
		res = mysql_query(mysql,command);
       //         resPtr = mysql_store_result(); 
		if(res == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

int teacher::get_points(MYSQL* mysql, int student_id,int homework_id,int score)
{
	/*学生成绩录入,给一个学生的某个作业打个分数*/
	char buf[MAXLEN] = {0};
        MYSQL_RES* resPtr;
        char* command;
	int res = 0;
	sprintf(buf,"select * from home do_homework where sid = %d and hid = %d\n", student_id,homework_id);
    command = strtok(buf,"\n");
	res = mysql_query(mysql,command);
    resPtr = mysql_store_result(mysql);
	if(resPtr->row_count == 0)
	{
		printf("the students's homework is not in the table\n");
		return 1;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into do_homework values (%d,%d,%d)\n", student_id,homework_id,score);
		command = strtok(buf,"\n");
		res = mysql_query(mysql,command);
		if(res == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}
