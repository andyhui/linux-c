#ifndef SQL_API_H
#define SQL_API_H

#include <mysql.h>

enum UserAuthority
{
    admin = 1,
    teacher = 2,
    student = 3
};

int MysqlConnect(MYSQL* mysql, UserAuthority userxxx);

MYSQL_RES* MysqlSelect(MYSQL* mysql, char* column,
                       char* table, char* condition);

int MysqlInsert(MYSQL* mysql, char* table, char* column, char* values);

int MysqlUpdate(MYSQL* mysql, char* table, char* content, char* condition);

int MysqlSort(MYSQL* mysql, char* column, char* table,
                            char* condition, char* content);

int MysqlDelete(MYSQL* mysql, char* table, char* condition);

void MysqlClose(MYSQL* mysql);

#endif
