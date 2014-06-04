#include <iostream>
#include <string>

using namespace std;

class class_type
{
private:
    int class_id;
    string class_name;
    string facult;
public:
    class_type();
    ~class_type(){}
    string get_class_name();
    int get_class_id();
};
