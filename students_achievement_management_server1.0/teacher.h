#ifndef _TEACHER_H_
#define _TEACHER_H_
#include <iostream>
#include <mysql.h>
using namespace std;

class teacher
{
public:
	int teacher_id;
	string teacher_name;
	string teacher_sex;
        string phone;
        string title;
        string department;
        string birthday;

	teacher();
	teacher(int t_id,string t_name,string
			t_sex,string t_phone,string t_title,string
			t_department,string
			t_birthday):teacher_id(t_id),teacher_name(t_name),teacher_sex(t_sex),phone(t_phone),title(t_title),department(t_department),birthday(t_birthday){}
	~teacher(){}

public:
	MYSQL_RES* view_courses(int class_id);
	bool arrange_homework(int homework_id,char* name,char* time,int cid);
	bool get_points(int student_id,int homework_id,int score);
	
};

#endif
