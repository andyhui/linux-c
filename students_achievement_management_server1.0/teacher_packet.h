#ifndef _TEACHER_PACKET_H_
#define _TEACHER_PACKET_H_
#include <iostream>

using namespace std;

class packet
{
public:
    packet();
    ~packet();

public:
    char* send_msg_teacher_log(int* len);
    char* send_msg_arrange_homework(int* len);
    char* send_msg_scores(int* len);
}

#endif
