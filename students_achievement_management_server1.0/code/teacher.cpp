#include <iostream>
#include <stdio.h>
#include <string.h>
#include "teacher.h"
#include <mysql.h>
//#include "sql_api.h"

using namespace std;

//const char* database = "CourseSystem";
MYSQL* database;
const int MAXLEN = 1024;

MYSQL_RES* teacher::view_courses(int class_id)
{
	/*显示课程号，查询课程*/
	char buf[MAXLEN] = {0};
	int res = 0;
	MYSQL_RES* resPtr;
	sprintf(buf,"select * from student where id = %d\n", class_id);
	res = mysql_query(database,buf);
	if(res == 0)
	{
		resPtr = mysql_store_result(database);
                return resPtr;
	}
	/*显示所有的学生信息*/
}

bool teacher::arrange_homework(int homework_id,char* name ,char* time, int cid)
{
	/*安排课后作业,写作业id，课程号，布置时间*/
	char buf[MAXLEN] = {0};
        char* command;
	int res = 0;
        MYSQL_RES* resPtr;
	sprintf(buf,"select * from home homework where id = %d and cid = %d\n", homework_id,cid);
        commad = strtok(buf,"\n");
	res = mysql_query(database,command);
        resPtr = mysql_store_result(database);
	if(resPtr.row_count != 0)
	{
		printf("the homework is exist\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into homework values (%d,%s,%s,%d)\n", homework_id,name,time,cid);
		res = mysql_query(database,buf);
       //         resPtr = mysql_store_result(); 
		if(res == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool teacher::get_points(int student_id,int homework_id,int score)
{
	/*学生成绩录入,给一个学生的某个作业打个分数*/
	char buf[MAXLEN] = {0};
        MYSQL_RES* resPtr;
        char* command;
	int res = 0;
	sprintf(buf,"select * from home do_homework where sid = %d and hid = %d\n", student_id,homework_id);
        command = strtok(buf,"\n");
	res = mysql_query(database,command);
        resPtr = mysql_store_result(database);
	if(resPtr.row_count == 0)
	{
		printf("the students's homework is not in the table\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into do_homework values (%d,%d,%d)\n", student_id,homework_id,score);
		command = strtok(buf,"\n");
		res = mysql_query(database,command);
		if(res == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
