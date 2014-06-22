//#ifndef REG_LOG_H
//#define REG_LOG_H

#include <mysql/mysql.h>


int RegisterAccount(MYSQL* mysql, int id, char* emailAddr,
                    char* passwd, int permission);

int Login(MYSQL* mysql, int id, char* passwd, int permission);

int ChangeMailAddr(MYSQL* mysql, int id, char* mailAddr);

int ChangePasswd(MYSQL* mysql, int id, char* passwd);

int AddUserInfo(MYSQL* mysql, int id);

int DeleteUserInfo(MYSQL* mysql, int id);

void Logout(MYSQL* mysql);

//#endif
