#include <iostream>

using namespace std;

class administrator
{

private:
   int admin_id;
   string admin_name;
public:
   administrator();
   administrator(int a_id,string a_name):admin_id(a_id),admin_name(a_name){}
   ~administrator(){}

//   void arrange_homework(int class_id);
   void del_student(int student_id);
   bool add_student(int student_id,char* name,char* student_sex,char*
		   student_sex,char* student_class,char* student_birthday);
   void del_teacher(int teacher_id);
   bool add_teacher(int teacher_id,char* name,char* teach_sex,char*
		   teacher_phone,char* teacher_title,char*
		   teacher_department,char* birthday);
   void del_course(int course_id);
   bool add_course(int course_id,char* name,int credit,int course_hours,int
		   tid,char* course_type);
   bool update_course(int course_id,char* name,int credit,int course_hours,int
		   tid,char* course_type);
   void view_course(int course_id);

   bool email_notice(char* to_email_address,char* from_email_address,char*
		   passwd,char* subject,char* message,char* email_server);

   int get_admin_id();
};
