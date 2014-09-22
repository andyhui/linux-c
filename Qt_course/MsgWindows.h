#ifndef MSGWINWDOWS_H
#define MSGWINWDOWS_H

#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QGridLayout>

class MsgWindows:public QWidget
{
    Q_OBJECT
public:
    MsgWindows(QWidget *parent = 0);
private:
    QLabel *scrollLabel;
    //QIcon *headerIcon;
    //QIcon *stateIcon;
    QLabel *headerIcon;
    QLabel *stateIcon;
    QLabel *stateLabel;
    QLabel *introDuction;

    QStackedWidget *content;

    QPushButton *introButton;
    QPushButton *chartButton;
    QPushButton *marksButton;


public slots:
    void changeHeaderIcon();


};

#endif // MSGWINWDOWS_H
