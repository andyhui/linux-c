#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <QApplication>
#include <QMessageBox>
#include "logindialog.h"
#include "mainwindow.h"

void PrintWarning(QString str)
{
    QMessageBox::warning(NULL, "警告", str);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int sock;
    struct sockaddr_in echoServAddr;
    unsigned short echoServPort = 8977;
    const char* servIP = "127.0.0.1";


    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        PrintWarning("socket() failed");
        return(1);
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family      = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port        = htons(echoServPort);

    if (connect(sock, (struct sockaddr *) &echoServAddr,
            sizeof(echoServAddr)) < 0)
    {
         PrintWarning("connect() failed");
         return(1);
    }

    LoginDialog loginDialog;
    loginDialog.mysock = sock;
    if(loginDialog.exec()==QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        int rslt = a.exec();
        close(sock);
        return rslt;
    }
    else
    {
        close(sock);
        return 0;
    }
}
