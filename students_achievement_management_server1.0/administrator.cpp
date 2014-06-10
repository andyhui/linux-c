//主要功能包括添加新用户，例如学生，老师。
//课程管理，例如安排课程，增加课程，删除课程，修改课程，查询课程。
//当学生或老师的课程信息发生变化通过邮件通知。
//查询学生的成绩，并统计。
#include <iostream>
#include "administrator.h"

using namespace std;

int administrator::get_admin_id()
{
    return admin_id;
}

void administrator::arrange_homework(int class_id)
{
    /*布置作业*/

}

void administrator::del_course(int course_id)
{
   /*删除课程*/

}

void administrator::add_course(int course_id)
{
    /*增加课程*/

}

void administrator::update_course(int course_id)
{
    /*更新课程*/
}

void administrator::view_course(int course_id)
{
    /*浏览课程*/

}


