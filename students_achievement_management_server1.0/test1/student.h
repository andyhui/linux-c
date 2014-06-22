#include <iostream>
#include <string.h>
#include <stdio.h>
#include <mysql/mysql.h>

using namespace std;

#define MAXLEN 1024

class student{

public:
    int student_id;
    string student_name;
    string student_sex;
    string student_class;
    string birthday;

//    int modifyEmailInfo();  //修改邮箱信息
    int selectCourse(MYSQL* mysql, int cid, int sid);     //选课
    int deleteCourse(MYSQL* mysql, int cid, int sid);     //退课
    MYSQL_RES* veiwCourse(MYSQL* mysql);                      //查询所有课程
    MYSQL_RES* veiwMyCourse(MYSQL* mysql, int sid);       //课程以选查询
    MYSQL_RES* queryScore(MYSQL* mysql, int sid, int cid = -1, int hid = -1);  //成绩查询，无参数查询所有课程所有作业成绩；1个参数表示课程ID，查询课程所有作业成绩；2个参数表示查询固定课程固定作业成绩
    
    
    int getStudent_id()
    {
        return student_id;
    }
    void setStudent_id(int id)
    {
        student_id = id;
    }
        
    string getStudent_name()
    {
        return student_name;
    }
    void setStudent_name(string name)
    {
        student_name = name;
    }
        
    string getStudent_sex()
    {
        return student_sex;
    }
    void setStudent_sex(string sex)
    {
        student_sex = sex;
    }
        
    string getStudent_class()
    {
        return student_class;
    }
    void setStudent_class(string cl)
    {
        student_class = cl;
    }
        
    string getStudent_birth()
    {
        return birthday;
    }
    void setStudent_birth(string birth)
    {
        birthday = birth;
    }
};        
        
        
