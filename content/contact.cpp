#include "contact.h"
#include <QGridLayout>

Contact::Contact(QWidget *parent, Qt::WindowFlags f2):QWidget(parent,f2){

    labelEmail = new QLabel(tr("Email:"));
    labelAddress = new QLabel(tr("Address:"));
    labelZipCode = new QLabel(tr("Zip Code:"));
    labelMobile = new QLabel(tr("Mobile:"));
    labelOffice = new QLabel(tr("Office:"));

    lineEmail = new QLineEdit;
    lineAddress = new QLineEdit;
    lineZipCode = new QLineEdit;
    lineMobile = new QLineEdit;
    lineOffice = new QLineEdit;

    check = new QCheckBox;
    check->setText(tr("Rev Msg"));

    QGridLayout *mainLayout2 = new QGridLayout(this);
    mainLayout2->addWidget(labelEmail,0,0);
    mainLayout2->addWidget(lineEmail,0,1);
    mainLayout2->addWidget(labelAddress,1,0);
    mainLayout2->addWidget(lineAddress,1,1);
    mainLayout2->addWidget(labelZipCode,2,0);
    mainLayout2->addWidget(lineZipCode,2,1);
    mainLayout2->addWidget(labelMobile,3,0);
    mainLayout2->addWidget(lineMobile,3,1);
    mainLayout2->addWidget(check,3,2);
    mainLayout2->addWidget(labelOffice,4,0);
    mainLayout2->addWidget(lineOffice,4,1);
    mainLayout2->setMargin(15);
    mainLayout2->setSpacing(15);
    mainLayout2->setColumnStretch(0,1);
    mainLayout2->setColumnStretch(1,3);
    mainLayout2->setColumnStretch(2,1);
}
