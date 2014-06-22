#ifndef HANDLE_TCP_CLIENT_H
#define HANDLE_TCP_CLIENT_H

#include "teacher.h"
#include "student.h"
#include "administrator.h"
#include "RegAndLog.h"

void HandleTCPClient(int clntSocket);

void HandleAdmin(MYSQL* mysql, int clntSocket, administrator admin);

void HandleStudent(MYSQL* mysql, int clntSocket, student stu);

void HandleTeacher(MYSQL* mysql, int clntSocket, teacher teacher1);

#endif
