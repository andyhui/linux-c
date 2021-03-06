#include "student.h"
using namespace std;
//#include "course.h"
//#include "homework.h"
//#include "select_course.h"



//int student::modifyEmailInfo()
//{
    //修改邮箱信息
//}

/*学生选课，在数据库select_course中查看是否已选此课程，没有则插入课程id,学生id*/
int student::selectCourse(MYSQL* mysql, int cid, int sid)
{
    MYSQL_RES* resPtr;
    char buf[MAXLEN] = {0};
    char *command;
    
    /*查询是否选过此课程*/
    sprintf(buf, "select * from select_course where cid = %d and sid = %d\n", cid, sid);
    command = strtok(buf, "\n");
    mysql_query(mysql, command);
    
    resPtr = mysql_store_result(mysql);
    if(resPtr->row_count == 0)
    {
        /*选课,sql插入*/
        sprintf(buf, "insert into select_course values (%d, %d)\n", cid, sid);
        command = strtok(buf, "\n");
        mysql_query(mysql, command);
        return 0;
    }
    else
    {
        //printf("you have selected this course\n");
        return 1;
    }
}


/*删除已选课程*/
int student::deleteCourse(MYSQL* mysql, int cid, int sid)
{
     //退课
    int res; 
    char buf[MAXLEN] = {0};
    char *command;
    
    sprintf(buf, "select * from select_course where cid = %d and sid = %d\n", cid, sid);
    command = strtok(buf, "\n");
    res = mysql_query(mysql, command);
    
    if(!res)
    {
        MYSQL_RES* resPtr;
        resPtr = mysql_store_result(mysql);
        if (resPtr)
        {
            if(resPtr->row_count == 0)
            {
                printf("you did not select this course\n");
                return 1;
            }
            else
            {
                sprintf(buf, "delete from select_course where cid = %d and sid = %d\n", cid, sid);
                command = strtok(buf, "\n");
                res = mysql_query(mysql, command);
            }
            mysql_free_result(resPtr);
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("exec error\n");
        return 1;
    }
}

/*课程所有查询信息*/
MYSQL_RES* student::veiwCourse(MYSQL* mysql)
{
    MYSQL_RES* resPtr;
    char buf[MAXLEN] = {0};
    char *command;
    
    sprintf(buf, "select * from course");
    command = strtok(buf, "\n");
    mysql_query(mysql, command);
    
    resPtr = mysql_store_result(mysql);
    return resPtr;
}


/*查询所选课程信息*/
MYSQL_RES* student::veiwMyCourse(MYSQL* mysql, int sid)
{
    MYSQL_RES* resPtr;
    char buf[MAXLEN] = {0};
    char *command;
    
    sprintf(buf, "select * from course where id in (select cid from select_course where sid = %d)\n",sid);
    command = strtok(buf, "\n");
    mysql_query(mysql, command);
    
    resPtr = mysql_store_result(mysql);
    return resPtr;
}

MYSQL_RES* student::queryScore(MYSQL* mysql, int sid, int cid, int hid)
{

    MYSQL_RES* resPtr;
    char buf[MAXLEN] = {0};
    char *command;
    
    if(cid == -1 && hid == -1)      /*默认查看所有课程*/  
    {
        veiwMyCourse(mysql, sid);
    }
    else if(hid == -1)              /*查看某一课程所有作业成绩*/
    {
        sprintf(buf, "select hname, score from do_homework where sid = %d\
            and hid in (select hid from homework where cid = %d)\n",sid, cid);
        command = strtok(buf, "\n");
        mysql_query(mysql, command);
    
        resPtr = mysql_store_result(mysql);
        return resPtr;
    }
    else                            /*查看单一作业信息*/
    {
        sprintf(buf, "select hname, score from do_homework where sid = %d\
            and hid = %d\n",sid, hid);
        command = strtok(buf, "\n");
        mysql_query(mysql, command);
    
        resPtr = mysql_store_result(mysql);
        return resPtr;
    }
}


