#include <iostream>
#include "class_type.h"

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
t_sex,string t_phone,string t_title,string t_department,string t_birthdary):teacher_id(t_id),teacher_name(t_name),teacher_sec(t_sec),phone(t_phone),title(t_title),department(t_department),birthday(t_birthday){}
	~teacher(){}

public:
	void view_courses(int class_id);
	bool arrange_homework(int homework_id,char* name,char* time,int cid);
	bool get_points(int student_id,int homework_id,int score);
	
};
