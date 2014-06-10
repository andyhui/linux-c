#include <iostream>
#include "teacher.h"
#include "mysql.h"
#include "sql_api.h"

using namespace std;

const char* database = "CourseSystem";
const int MAXLEN = 1024;

void teacher::view_courses(int class_id)
{
	/*显示课程号，查询课程*/
	char buf[MAXLEN] = {0};
	int res = 0;
	MYSQL_RES* resPtr;
	sprintf(buf,"selec * from student where id = %s\n", class_id);
	res = mysql_query(database,buf);
	if(res == 0)
	{
		resPtr = mysql_store_result(database);
	}
	/*显示所有的学生信息*/
}

bool teacher::arrange_homework(int homework_id,char* name ,char* time, int cid)
{
	/*安排课后作业,写作业id，课程号，布置时间*/
	char buf[MAXLEN] = {0};
	int res = 0;
	sprintf(buf,"select * from home homework where id = %s and cid = %s\n", homework_id,cid);
	res = mysql_query(database,buf);
	if(res == 0)
	{
		printf("the homework is exist\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into homework values (%s,%s,%s,%s)\n", homework_id,name,time,cid);
		res = mysql_query(database,buf);
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
	int res = 0;
	sprintf(buf,"select * from home do_homework where sid = %s and hid = %s\n", student_id,homework_id);
	res = mysql_query(database,buf);
	if(res == 0)
	{
		printf("the homework is exist\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into do_homework values (%s,%s,%s)\n", student_id,homework_id,score);
		res = mysql_query(database,buf);
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
