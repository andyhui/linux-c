#ifndef CONTACT_H
#define CONTACT_H

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

class Contact:public QWidget{
    Q_OBJECT
public:
    Contact(QWidget *parent = 0, Qt::WindowFlags f2 = 0);

    QLabel *labelEmail;
    QLabel *labelAddress;
    QLabel *labelZipCode;
    QLabel *labelMobile;
    QLabel *labelOffice;

    QLineEdit *lineEmail;
    QLineEdit *lineAddress;
    QLineEdit *lineZipCode;
    QLineEdit *lineMobile;
    QLineEdit *lineOffice;

    QCheckBox *check;
};

#endif // CONTACT_H
