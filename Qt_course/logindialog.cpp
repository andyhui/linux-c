#include "logindialog.h"
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <sys/socket.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include <QRadioButton>

#define BUFSIZE 2048
#define SIZE 100

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(800, 600);

    userEdit = new QLineEdit("学号", this);
    userEdit->setGeometry(300, 250, 200, 30);
    passwdEdit = new QLineEdit("密码", this);
    passwdEdit->setGeometry(300, 300, 200, 30);
    passwdEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("登录",this);
    loginButton->setGeometry(350, 400, 100, 30);

    radio[0] = new QRadioButton("学生", this);
    radio[0]->setGeometry(280, 350, 60, 30);
    radio[0]->setChecked(true);
    radio[1] = new QRadioButton("老师", this);
    radio[1]->setGeometry(350, 350, 60, 30);
    radio[2] = new QRadioButton("管理员", this);
    radio[2]->setGeometry(420, 350, 100, 30);

    connect(loginButton, SIGNAL(clicked()), this, SLOT(Login()));
}

LoginDialog::~LoginDialog()
{
    delete userEdit;
    delete passwdEdit;
    delete loginButton;

    for(int i=0; i<3; i++)
    {
        delete radio[i];
    }
}

void LoginDialog::Login()
{
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    //const char* pattern1 =
    //    "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*{,60}$";
    const char* pattern2 = "^\\w{6,16}$";
    regex_t passwdReg;
    char buf[BUFSIZE] = {0};
    QByteArray userBa = userEdit->text().toLatin1();
    QByteArray passwdBa = passwdEdit->text().toLatin1();
    char* userCh = userBa.data();
    char* passwdCh = passwdBa.data();

    // 检查用户名和密码格式
    //regcomp(&mailAddrReg, pattern1, REG_EXTENDED);
    regcomp(&passwdReg, pattern2, REG_EXTENDED);

    if (REG_NOMATCH == regexec(&passwdReg, passwdCh, nmatch, pmatch, 0))
    {
        PrintWarning("请正确填写用户名和密码");
    }
    else
    {
        char passwd[SIZE]={0};
        int userId = atoi(userCh);
        sprintf(passwd, "%s", passwdCh);
        buf[0] = 0;
        if (radio[0]->isChecked())
        {
            buf[1] = 1;
        }
        if (radio[1]->isChecked())
        {
            buf[1] = 2;
        }
        if (radio[2]->isChecked())
        {
            buf[1] = 3;
        }
        buf[2] = 0;
        memcpy(buf+3, &userId, 4);
        memcpy(buf+7, passwd, SIZE);
        if (send(mysock, buf, BUFSIZE, 0) != BUFSIZE)
        {
            PrintWarning("发送失败");
        }
        else
        {
            memset(buf, 0, BUFSIZE);
            if (recv(mysock, buf, BUFSIZE, 0) != BUFSIZE)
            {
                PrintWarning("接收失败");
            }
            else
            {
                if (buf[0] != 1)
                {
                    PrintWarning("登录失败，请重新填入用户名和密码");
                }
                else
                {
                    accept();
                    close();
                }
            }
        }
    }
}

void LoginDialog::PrintWarning(QString str)
{
    QMessageBox::warning(this, "警告", str);

    userEdit->clear();
    passwdEdit->clear();
    userEdit->setFocus();
}
