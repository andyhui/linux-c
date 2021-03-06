#ifndef SQL_API_H
#include "sql_api.h"
#endif

#include <stdio.h>
#include <string.h>

int MysqlConnect(MYSQL* mysql, UserAuthority userxxx)
{
    mysql_init(mysql);

    if (userxxx == 1)
    {
        if (!mysql_real_connect(mysql, "localhost",
                               "admin", "admin123",
                               "CouresSystem", 0,
                               NULL, 0))
        {
            return 1;
        }
    }
    else if (userxxx == 2)
    {
        if (!mysql_real_connect(mysql, "localhost",
                               "teacher", "teacher123",
                               "CouresSystem", 0,
                               NULL, 0))
        {
            return 1;
        }
    }
    else if (userxxx == 3)
    {
        if (!mysql_real_connect(mysql, "localhost",
                               "student", "student123",
                               "CouresSystem", 0,
                               NULL, 0))
        {
            return 1;
        }
    }

    return 0;
}

MYSQL_RES* MysqlSelect(MYSQL* mysql, char* column,
                       char* table, char* condition)
{
    MYSQL_RES* resPtr;

    int res;
    char buf[MAXLEN] = {0};
    char* command;

    if (condition != NULL)
    {
        sprintf(buf, "SELECT %s FROM %s WHERE %s\n",
                            column, table, condition);
    }
    else
    {
        sprintf(buf, "SELECT %s FROM %s\n", column, table);
    }
    command = strtok(buf, "\n");

    res = mysql_query(mysql, command);
    if(!res)
    {
        resPtr = mysql_store_result(mysql);
        if (resPtr)
        {
            return resPtr;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

int MysqlInsert(MYSQL* mysql, char* table, char* column, char* values)
{
    int res;
    char buf[MAXLEN] = {0};
    char* command;

    if (column != NULL)
    {
        sprintf(buf, "INSERT INTO %s (%s) VALUES (%s)\n",
                                    table, column, values);
    }
    else
    {
        sprintf(buf, "INSERT INTO %s VALUES (%s)\n", table, values);
    }
    command = strtok(buf, "\n");

    res = mysql_query(mysql, command);
    if(!res)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int MysqlUpdate(MYSQL* mysql, char* table, char* content, char* condition)
{
    int res;
    char buf[MAXLEN] = {0};
    char* command;

    sprintf(buf, "UPDATE %s SET %s WHERE %s\n", table, content, condition);
    command = strtok(buf, "\n");

    res = mysql_query(mysql, command);
    if(!res)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int MysqlSort(MYSQL* mysql, char* column, char* table,
                            char* condition, char* content)
{
    MYSQL_RES* resPtr;

    int res;
    char buf[MAXLEN] = {0};
    char* command;

    if (condition != NULL)
    {
        sprintf(buf, "SELECT %s FROM %s WHERE %s ORDER BY %s\n",
                            column, table, condition, content);
    }
    else
    {
        sprintf(buf, "SELECT %s FROM %s ORDER BY %s\n",
                            column, table, content);
    }
    command = strtok(buf, "\n");

    res = mysql_query(mysql, command);
    if(!res)
    {
        resPtr = mysql_store_result(mysql);
        if (resPtr)
        {
            return resPtr;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

int MysqlDelete(MYSQL* mysql, char* table, char* condition)
{
    int res;
    char buf[MAXLEN] = {0};
    char* command;

    if (content != NULL)
    {
        sprintf(buf, "DELETE FROM %s WHERE %s\n", table, condition);
    }
    else
    {
        sprintf(buf, "DELETE FROM %s\n", table);
    }
    command = strtok(buf, "\n");

    res = mysql_query(mysql, command);
    if(!res)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void MysqlClose(MYSQL* mysql, MYSQL_RES* resPtr)
{
    if (resPtr != NULL)
    {
        mysql_free_result(resPtr);
    }
    mysql_close(mysql);
}


