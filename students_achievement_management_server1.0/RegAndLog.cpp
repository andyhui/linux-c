#include "RegAndLog.h"

#include <iostream>
#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define BUFLEN 256

using namespace std;

int RegisterAccount(MYSQL* mysql, int id, const char* mailAddr,
                    const char* passwd, int permission)
{
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    const char* pattern1 = "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$";
    const char* pattern2 = "^\\w{6,16}$";
    regex_t mailAddrReg, passwdReg;
    char buf[BUFLEN] = {0};
    char* command = NULL;
    MYSQL_RES* resPtr;
    MYSQL_ROW resRow;

    regcomp(&mailAddrReg, pattern1, REG_EXTENDED);
    regcomp(&passwdReg, pattern2, REG_EXTENDED);

    if (REG_NOMATCH == regexec(&mailAddrReg, mailAddr, nmatch, pmatch, 0) ||
        REG_NOMATCH == regexec(&passwdReg, passwd, nmatch, pmatch, 0))
    {
        cout<<"请正确填写邮箱地址和密码\n"<<endl;
        regfree(&mailAddrReg);
        regfree(&passwdReg);
        return 1;
    }
    else
    {
        mysql_init(mysql);

        // 管理员
        if (permission == 1)
        {
            mysql_real_connect(mysql, "localhost", "admin", "admin123",
                                    "coursesystem", 0, NULL, 0);
        }
        // 教师
        else if (permission == 2)
        {
            mysql_real_connect(mysql, "localhost", "teacher", "teacher123",
                                    "coursesystem", 0, NULL, 0);
        }
        // 学生
        else
        {
            mysql_real_connect(mysql, "localhost", "student", "student123",
                                    "coursesystem", 0, NULL, 0);
        }

        sprintf(buf, "select mailaddr from registerinfo where id=%d\n", id);
        command = strtok(buf, "\n");
        mysql_query(mysql, command);

        resPtr = mysql_store_result(mysql);
        if (mysql_num_rows(resPtr) == 0)
        {
            cout<<"没有你的信息，请咨询管理处\n"<<endl;
            mysql_free_result(resPtr);
            mysql_close(mysql);
            regfree(&mailAddrReg);
            regfree(&passwdReg);
            return 1;
        }
        else
        {
            resRow = mysql_fetch_row(resPtr);
            if (resRow[0] != NULL)
            {
                cout<<"邮箱已被注册\n"<<endl;
                mysql_free_result(resPtr);
                mysql_close(mysql);
                regfree(&mailAddrReg);
                regfree(&passwdReg);
                return 1;
            }
            else
            {
                memset(buf, 0, BUFLEN);
                sprintf(buf,
          "update registerinfo set mailaddr='%s', passwd='%s' where id=%d\n",
                        mailAddr, passwd, id);
                command = strtok(buf, "\n");
                mysql_query(mysql, command);
            }
        }
    }
    mysql_free_result(resPtr);
    mysql_close(mysql);
    regfree(&mailAddrReg);
    regfree(&passwdReg);

    return 0;
}


// 如login成功则必须logout
int Login(MYSQL* mysql, int id, const char* passwd, int permission)
{
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    const char* pattern = "^\\w{6,16}$";
    regex_t passwdReg;
    char buf[BUFLEN] = {0};
    char* command = NULL;
    MYSQL_RES* resPtr;
    MYSQL_ROW resRow;

    regcomp(&passwdReg, pattern, REG_EXTENDED);

    if (REG_NOMATCH == regexec(&passwdReg, passwd, nmatch, pmatch, 0))
    {
        cout<<"用户名或密码错误，格式不对\n"<<endl;
        regfree(&passwdReg);
        return 1;
    }
    else
    {
        mysql_init(mysql);

        char value = 1;
        mysql_options(mysql, MYSQL_OPT_RECONNECT, &value);

        // 管理员
        if (permission == 1)
        {
            mysql_real_connect(mysql, "localhost", "admin", "admin123",
                                    "coursesystem", 0, NULL, 0);
        }
        // 教师
        else if (permission == 2)
        {
            mysql_real_connect(mysql, "localhost", "teacher", "teacher123",
                                    "coursesystem", 0, NULL, 0);
        }
        // 学生
        else
        {
            mysql_real_connect(mysql, "localhost", "student", "student123",
                                    "coursesystem", 0, NULL, 0);
        }

        sprintf(buf,
                "select passwd from registerinfo where id=%d\n",
                id);
        command = strtok(buf, "\n");
        mysql_query(mysql, command);

        resPtr = mysql_store_result(mysql);
        if (mysql_num_rows(resPtr) == 0)
        {
            cout<<"用户名或密码错误，查无\n"<<endl;
            mysql_free_result(resPtr);
            mysql_close(mysql);
            regfree(&passwdReg);
            return 1;
        }
        else
        {
            resRow = mysql_fetch_row(resPtr);
            if (resRow[0] == NULL)
            {
                cout<<"用户名或密码错误\n"<<endl;
                mysql_free_result(resPtr);
                mysql_close(mysql);
                regfree(&passwdReg);
                return 1;
            }
            else
            {
                if (strcmp(passwd, resRow[0]) != 0)
                {
                    cout<<"用户名或密码错误\n"<<endl;
                    mysql_free_result(resPtr);
                    mysql_close(mysql);
                    regfree(&passwdReg);
                    return 1;
                }
            }
        }
    }
    mysql_free_result(resPtr);
    regfree(&passwdReg);

    return 0;
}

int ChangeMailAddr(MYSQL* mysql, int id, const char* mailAddr)
{
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    const char* pattern = "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$";
    regex_t mailAddrReg;
    char buf[BUFLEN] = {0};
    char* command = NULL;
    MYSQL_RES* resPtr;

    regcomp(&mailAddrReg, pattern, REG_EXTENDED);

    if (REG_NOMATCH == regexec(&mailAddrReg, mailAddr, nmatch, pmatch, 0))
    {
        cout<<"邮箱地址格式错误\n"<<endl;
        regfree(&mailAddrReg);
        return 1;
    }
    else
    {
        sprintf(buf,
                "update registerinfo set mailaddr='%s' where id=%d\n",
                mailAddr, id);
        command = strtok(buf, "\n");
        mysql_query(mysql, command);
    }

    regfree(&mailAddrReg);

    return 0;
}

int ChangePasswd(MYSQL* mysql, int id, const char* passwd)
{
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    const char* pattern = "^\\w{6,16}$";
    regex_t passwdReg;
    char buf[BUFLEN] = {0};
    char* command = NULL;
    MYSQL_RES* resPtr;

    regcomp(&passwdReg, pattern, REG_EXTENDED);

    if (REG_NOMATCH == regexec(&passwdReg, passwd, nmatch, pmatch, 0))
    {
        cout<<"密码格式错误\n"<<endl;
        regfree(&passwdReg);
        return 1;
    }
    else
    {
        sprintf(buf,
                "update registerinfo set passwd='%s' where id=%d\n",
                passwd, id);
        command = strtok(buf, "\n");
        mysql_query(mysql, command);
    }

    regfree(&passwdReg);

    return 0;
}

void Logout(MYSQL* mysql)
{
    mysql_close(mysql);
}

//int main()
//{
//    MYSQL mysql;
//
//    //RegisterAccount(&mysql, 10203, "zhou@sina.com", "123123", 3);
//
//    if(0 == Login(&mysql, 10203, "123123123", 3))
//    {
//        ChangePasswd(&mysql, 10203, "123123123");
//        printf("changed\n");
//        Logout(&mysql);
//    }
//    
//    if(0 == Login(&mysql, 10203, "123123123123", 3))
//    {
//        printf("hello\n");
//        Logout(&mysql);
//    }
//    return 0;
//}
