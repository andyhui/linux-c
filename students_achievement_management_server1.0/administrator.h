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

   void arrange_homework(int class_id);
   void del_course(int course_id);
   void add_course(int course_id);
   void update_course(int course_id);
   void view_course(int course_id);

   int get_admin_id();
   
};
