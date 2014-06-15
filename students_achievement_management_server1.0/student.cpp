#include "student.h"

//#include "course.h"
//#include "homework.h"
//#include "select_course.h"



//int student::modifyEmailInfo()
//{
    //修改邮箱信息
//}

/*学生选课，在数据库select_course中查看是否已选此课程，没有则插入课程id,学生id*/
int student::selectCourse(MYSQL* mysql, int cid, student stu)
{
    MYSQL_RES* resPtr;
    int sid = stu.student_id;                  //获取学生id
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
int student::deleteCourse(MYSQL* mysql, int cid, student stu)
{
     //退课
    int res; 
    char buf[MAXLEN] = {0};
    char *command;
    int sid = stu.student_id;
    
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

/*课程查询*/
MYSQL_RES* student::veiwCourse(MYSQL* mysql, student stu)
{
    MYSQL_RES* resPtr;
    char buf[MAXLEN] = {0};
    char *command;
    int sid = stu.student_id;
    
    sprintf(buf, "select * from course where id in (select cid from select_course where sid = %d)\n",sid);
    command = strtok(buf, "\n");
    mysql_query(mysql, command);
    
    resPtr = mysql_store_result(mysql);
    return resPtr;
}

MYSQL_RES* student::queryScore(MYSQL* mysql, student stu, int cid = -1, int hid = -1)
{

    MYSQL_RES* resPtr;
    char buf[MAXLEN] = {0};
    char *command;
    int sid = stu.student_id;
    
    if(cid == -1 && hid == -1)      /*默认查看所有课程*/  
    {
        veiwCourse(mysql, stu);
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


/*int main()
{
    MYSQL mysql;
    mysql_init(&mysql);
    int res;
    MYSQL_RES* resPtr;
    
    if (!mysql_real_connect(&mysql, "localhost",
                            "root", "5526718",
                            "course_system", 0,
                             NULL, 0))
    {
        printf("error\n");
        //exit(1);
    }
    
/*    mysql_query(&mysql, "insert into course values (1, 'math', 4, 48, 1, 'Obligatory')");
    mysql_query(&mysql, "insert into course values (2, 'english', 4, 48, 2, 'Obligatory')");
    mysql_query(&mysql, "insert into course values (3, 'history', 3, 24, 3, 'Obligatory')");
    mysql_query(&mysql, "insert into course values (4, 'sex', 2, 24, 4, 'Elective')");
    
    mysql_query(&mysql, "insert into homework values (1, 'math_homework1', '20140612', 1)");
    mysql_query(&mysql, "insert into homework values (2, 'math_homework2', '20140613', 1)");
    mysql_query(&mysql, "insert into homework values (3, 'math_homework3', '20140614', 1)");
    
    mysql_query(&mysql, "insert into student values (1, 'student1', 'male', 'class1', '1990')");
    mysql_query(&mysql, "insert into student values (2, 'student2', 'female', 'class1', '1987')");
    mysql_query(&mysql, "insert into student values (3, 'student3', 'male', 'class1', '1989')");
    
    mysql_query(&mysql, "insert into select_course values (1, 1)");
    mysql_query(&mysql, "insert into select_course values (2, 1)");
    mysql_query(&mysql, "insert into select_course values (3, 1)");
    
    mysql_query(&mysql, "insert into do_homework values (1, 1, 'math_homework1', 45)");
    mysql_query(&mysql, "insert into do_homework values (2, 1, 'math_homework1', 60)");
    mysql_query(&mysql, "insert into do_homework values (3, 1, 'math_homework1', 87)");
    
    mysql_query(&mysql, "insert into do_homework values (1, 2, 'math_homework2', 60)");
    mysql_query(&mysql, "insert into do_homework values (2, 2, 'math_homework2', 60)");
    mysql_query(&mysql, "insert into do_homework values (3, 2, 'math_homework2', 60)"); 
       
    mysql_query(&mysql, "insert into do_homework values (1, 3, 'math_homework3', 90)");
    mysql_query(&mysql, "insert into do_homework values (2, 3, 'math_homework3', 90)");
    mysql_query(&mysql, "insert into do_homework values (3, 3, 'math_homework3', 90)");  
*/
/*
    student stu1;
    char name[20] = "student1";
    char sex[8] = "boy";
    char cl[10] = "class1";
    char birth[8] = "1990";
    stu1.setStudent_id(1);
    stu1.setStudent_name(name);
    stu1.setStudent_sex(sex);
    stu1.setStudent_class(cl);
    stu1.setStudent_birth(birth);     
    
    printf("======1======\n");
    res = stu1.selectCourse(&mysql, 1, stu1);
    if(res == 0)
    {
        printf("select course successfully\n");
    }
    else
    {
        printf("Operation is prohibited, you have selected this course before\n");
    }
    
    printf("======2======\n");
    res = stu1.deleteCourse(&mysql, 2, stu1);
    if(res == 0)
    {
        printf("delete course successfully\n");
    }
    else
    {
        printf("Operation is prohibited, you have not selected this course before\n");
    }
    
    printf("======3======\n");
    resPtr = stu1.veiwCourse(&mysql, stu1);
    if (resPtr)
    {
        if(resPtr->row_count == 0)
        {
            printf("no information about this course\n");
        }
        else
        {
            printf("======4======\n");
            MYSQL_ROW row;
            int i;
            while((row = mysql_fetch_row(resPtr)) != NULL)
            {
                for(i = 0; i < mysql_field_count(&mysql); i++)
                {
                    printf("%s   ", row[i]);
                }
                printf("\n");
            }
        }
        mysql_free_result(resPtr);
    }
    
    printf("======5======\n");
    resPtr = stu1.queryScore(&mysql, stu1, 1);
    if (resPtr)
    {
        if(resPtr->row_count == 0)
        {
            printf("no information about this course\n");
        }
        else
        {
            MYSQL_ROW row;
            int i;
            while((row = mysql_fetch_row(resPtr)) != NULL)
            {
                for(i = 0; i < mysql_field_count(&mysql); i++)
                {
                    printf("%s   ", row[i]);
                }
                printf("\n");
            }
        }
        mysql_free_result(resPtr);
    }
}
*/
