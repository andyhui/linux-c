//主要功能包括添加新用户，例如学生，老师。
//课程管理，例如安排课程，增加课程，删除课程，修改课程，查询课程。
//当学生或老师的课程信息发生变化通过邮件通知。
//查询学生的成绩，并统计。
//create table if not exists course(
//       id           int      not null   primary key,
//       name         char(20) not null,
//       credit       int      not null,
//       tid          int      not null,
//       course_type  char(20) not null)


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "administrator.h"
#include "jwsmtp/jwsmtp.h"

using namespace std;
MYSQL* database;
const int MAXLEN = 1024;

int administrator::get_admin_id()
{
    return admin_id;
}

//void administrator::arrange_homework(int class_id)
//{
//    /*布置作业*/
//
//}

//管理老師信息
void administrator::del_teacher(int teacher_id)
{
   /*管理教师信息,根据教师id删除教师信息*/
   char buf[MAXLEN] = {0};
   char* command;
   int res = 0;
   MYSQL_RES* resPtr;
   sprintf(buf,"select * from teacher where id = %d\n",teacher_id);
   command = strtok(buf,"\n");
   res = mysql_query(database,command);
   resPtr = mysql_store_result(database);
   if(resPtr->row_count == 0)
   {
       cout << "没有这個老師" << endl;
   }
   else
   {
      memset(buf,'\0',MAXLEN);
      sprintf(buf,"delete * from teacher where id = %d\n",teacher_id);
      command = strtok(buf,"\n");
      res = mysql_query(database,command);
   }
}

bool administrator::add_teacher(int teacher_id,char* name,char*
		teacher_sex,char* teacher_phone,char* teacher_title,char*
		teacher_department,char* birthday)
{
    /*增加老师信息,加入教师号，教师名，教师性别，教师电话，教师职称，教师学院，教师生日*/
    
	char buf[MAXLEN] = {0};
	char* command;
	int res = 0;
	MYSQL_RES* resPtr;
	sprintf(buf,"select * from teacher where id = %d\n", teacher_id);
	command = strtok(buf,"\n");
	res = mysql_query(database,command);
	resPtr = mysql_store_result(database);
	if(resPtr->row_count != 0)
	{
		printf("老師已經存在\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into teacher values \
(%d,%s,%s,%s,%s,%s,%s)\n",teacher_id,name,teacher_sex,teacher_phone,teacher_title,teacher_department,birthday);
		command = strtok(buf,"\n");
		res = mysql_query(database,command);
		//resPtr = mysql_store_result(); 
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

//管理學生信息
void administrator::del_student(int student_id)
{
   /*删除学生信息,根据学生id删除学生信息*/
   char buf[MAXLEN] = {0};
   char* command;
   int res = 0;
   MYSQL_RES* resPtr;
   sprintf(buf,"select * from student where id = %d\n",student_id);
   command = strtok(buf,"\n");
   res = mysql_query(database,command);
   resPtr = mysql_store_result(database);
   if(resPtr->row_count == 0)
   {
       cout << "沒有這個學生" << endl;
   }
   else
   {
      memset(buf,'\0',MAXLEN);
      sprintf(buf,"delete * from student where id = %d\n",student_id);
      command = strtok(buf,"\n");
      res = mysql_query(database,command);
   }
}

bool administrator::add_student(int student_id,char* name,char* student_sex,char* student_class,char* student_birthday)
{
    /*增加学生信息,根据學生号，学生名称，学生性别，学生班级，学生生日*/
    
	char buf[MAXLEN] = {0};
	char* command;
	int res = 0;
	MYSQL_RES* resPtr;
	sprintf(buf,"select * from student where id = %d\n", student_id);
	command = strtok(buf,"\n");
	res = mysql_query(database,command);
	resPtr = mysql_store_result(database);
	if(resPtr->row_count != 0)
	{
		printf("這個學生已經存在\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into student values (%d,%s,%s,%s,%s)\n", student_id,name,student_sex,student_class,student_birthday);
		command = strtok(buf,"\n");
		res = mysql_query(database,command);
		//resPtr = mysql_store_result(); 
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

//管理員管理課程
void administrator::del_course(int course_id)
{
   /*删除课程,根据课程id删除课程课程信息*/
   char buf[MAXLEN] = {0};
   char* command;
   int res = 0;
   MYSQL_RES* resPtr;
   sprintf(buf,"select * from course where id = %d\n",course_id);
   command = strtok(buf,"\n");
   res = mysql_query(database,command);
   resPtr = mysql_store_result(database);
   if(resPtr->row_count == 0)
   {
       cout << "没有这个课程" << endl;
   }
   else
   {
      memset(buf,'\0',MAXLEN);
      sprintf(buf,"delete * from course where id = %d\n",course_id);
      command = strtok(buf,"\n");
      res = mysql_query(database,command);
   }
}

bool administrator::add_course(int course_id,char* name,int credit,int course_hours,int tid,char* course_type)
{
    /*增加课程,根据课程号，课程名称，课程学分，课程学时，教师id，课程类型，加入课程*/
    
	char buf[MAXLEN] = {0};
	char* command;
	int res = 0;
	MYSQL_RES* resPtr;
	sprintf(buf,"select * from course where id = %d\n", course_id);
	command = strtok(buf,"\n");
	res = mysql_query(database,command);
	resPtr = mysql_store_result(database);
	if(resPtr->row_count != 0)
	{
		printf("the homework is exist\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"insert into course values (%d,%s,%d,%d,%d,%s)\n", course_id,name,credit,course_hours,tid,course_type);
		command = strtok(buf,"\n");
		res = mysql_query(database,command);
		//resPtr = mysql_store_result(); 
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


bool administrator::update_course(int course_id,char* name,int credit,int course_hours,int t_id,char* course_type)
{
	/*更新课程,修改课程信息，根据课程id，修改课程名，课程学分，课程学时，教师id，课程类型*/
        //修改學時
       int res;
       char buf[MAXLEN] = {0};
       char* command;

	MYSQL_RES* resPtr;
	sprintf(buf,"select * from course where id = %d\n", course_id);
	command = strtok(buf,"\n");
	res = mysql_query(database,command);
	resPtr = mysql_store_result(database);
	if(resPtr->row_count == 0)
	{
		printf("the course is not exist\n");
		return false;
	}
	else
	{
		memset(buf,'\0',MAXLEN);
		sprintf(buf,"UPDATE course SET course_hours = %d,name = %s,credit = %d,course_hours = %d,t_id = %d,course_type = %s where id =	%d\n",course_hours,name,credit,course_hours,t_id,course_type,course_id);
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

MYSQL_RES* administrator::view_course(int course_id)
{
	/*浏览课程,根据课程id，查询课程名，课程学分，课程学时，教师id，课程类型*/
	/*显示课程号，查询课程*/
	char buf[MAXLEN] = {0};
        char* command;
	int res = 0;
	MYSQL_RES* resPtr;
	sprintf(buf,"select * from course where id = %d\n", course_id);
        command = strtok(buf,"\n");
	res = mysql_query(database,command);
	if(res == 0)
	{
		resPtr = mysql_store_result(database);
                return resPtr;
	}
	/*显示所有的学生信息*/


}

bool email_notice(char* to_email_address,char* from_email_address,char* passwd,char* subject,char* message,char* email_server)
{
	jwsmtp::mailer m(to_email_address,from_email_address,subject,message,email_server,jwsmtp::mailer::SMTP_PORT,false); 
	m.username(from_email_address); 
	m.password(passwd);
	m.send();
	cout << m.response() << endl;
        char* command;
        char t[200];
        memset(t,0,200);
        strcpy(t,m.response().c_str());
        command = strtok(t," ");
	if(strcmp(command,"250") == 0)
	{
		cout <<"email send ok" << endl;
		return true;
	}
	else
	{
		cout << "email send error ,please check your setting" << endl;
		return false;
	}
}
