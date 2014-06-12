#include <iostream>
#include <stdio.h>
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
    sql.connectMySQL("localhost","root","root","database",0);
    int a_id = ad_1.get_admin_id();
    ad_1.arrange_homework(1);
    printf("hello world!\n");
    printf("the administrator's id is %d\n",a_id);
    return 0;
}
