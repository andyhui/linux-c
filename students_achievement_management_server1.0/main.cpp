#include <iostream>
#include <stdio.h>

#include "teacher.h"
#include "administrator.h"

using namespace std;

int main()
{
    teacher tc_1(10,"lixiang",1);
    administrator ad_1(20,"wangfang");
    int a_id = ad_1.get_admin_id();
    ad_1.arrange_homework(1);
    printf("hello world!\n");
    printf("the administrator's id is %d\n",a_id);
    return 0;
}
