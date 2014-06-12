#include <iostream>
#include "class_type.h"

using namespace std;

class teacher
{
public:
	int teacher_id;
	string teacher_name;
	int teacher_sec;

	teacher();
	teacher(int t_id,string t_name,int
t_sec):teacher_id(t_id),teacher_name(t_name),teacher_sec(t_sec){}
	~teacher(){}

public:
	void view_courses(int class_id);
	bool arrange_homework(int homework_id,char* name,char* time,int cid);
	bool get_points(int student_id,int homework_id,int score);
	
};
