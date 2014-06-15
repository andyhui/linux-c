#include <iostream>
#include <stdio.h>
#include <string.h>
#include <mysql.h>

#include "teacher.h"
#include "administrator.h"
#include "MySQLInterface.h"

using namespace std;

int main()
{
    teacher tc_1(10,"lixiang",1);
    administrator ad_1(20,"wangfang");
    MySQLInterface sql;
    MYSQL mysql_instance;
    sql.connectMySQL("localhost","root","root","CourseSystem",0);
    string database = "CourseSystem";
    sql.createDatabase(database);
    const string query = "create table if not exists TableStudent(ID \
        char(12) not null primary key,Name  char(20) not null,Sex   char(8) \
        not null,Class char(10) not null,DateOfBirth char(8) not null);";
    sql.createdbTable(query);
    int a_id = ad_1.get_admin_id();
    ad_1.arrange_homework(1);
    printf("hello world!\n");
    printf("the administrator's id is %d\n",a_id);
    return 0;
}
