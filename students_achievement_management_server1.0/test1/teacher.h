#include <iostream>
#include <mysql/mysql.h>
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

	teacher(){}
//	teacher(int t_id,string t_name,string
///			t_sex,string t_phone,string t_title,string
//			t_department,string
//			t_birthday):teacher_id(t_id),teacher_name(t_name),teacher_sex(t_sex),phone(t_phone),title(t_title),department(t_department),birthday(t_birthday){}
	~teacher(){}

public:
	MYSQL_RES* view_courses(MYSQL* mysql, int cid);
	int arrange_homework(MYSQL* mysql, char* name, char* time,int cid);
	int get_points(MYSQL* mysql, int student_id,int homework_id,int score);
	
};
