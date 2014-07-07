#ifndef BASEINFO_H
#define BASEINFO_H

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>

class BaseInfo:public QWidget{
    Q_OBJECT
public:
    BaseInfo(QWidget *parent = 0, Qt::WindowFlags f1 = 0);

    /*about administrator*/
    QLabel *labelCourseId;
    QLabel *labelCourseName;
    QLabel *labelCoursePoints;
    QLabel *labelCourseTeacher;
    QLabel *labelCourseTimes;

    QLineEdit *lineCourseId;
    QLineEdit *lineCourseName;
    QLineEdit *lineCoursePoints;
    QLineEdit *lineCourseTeacher;
    QLineEdit *lineCourseTimes;

    /*about teacher*/
    QLabel *labelTeacherId;
    QLabel *labelTeacherName;
    QLabel *labelTeacherCourse;
    QLabel *labelTeacherJobTitle;

    QLabel *lineTeacherId;
    QLabel *lineTeacherName;
    QLabel *lineTeacherCourse;
    QLabel *lineTeacherJobTitle;

    /*about student */
    QLabel *labelStudentId;
    QLabel *labelStudentName;
    QLabel *labelStudentAge;
    QLabel *labelStudentSex;

    QLabel *lineStudentId;
    QLabel *lineStudentName;
    QLabel *lineStudentAge;
    QLabel *lineStudentSex;

    //QTextEdit *textDepart;
    //QTextEdit *textIndivd;

    QPushButton *buttonAddCourse;
    QPushButton *buttonDeleteCourse;
    QPushButton *buttonUpdateCourse;
    QPushButton *buttonInquiryCourse;

    QPushButton *buttonAddTeacher;
    QPushButton *buttonDeleteTeacher;

    QPushButton *buttonAddStudent;
    QPushButton *buttonDeleteStudent;


    QComboBox *comboSex;
};

#endif // BASEINFO_H
