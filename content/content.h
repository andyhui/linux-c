#ifndef CONTENT_H
#define CONTENT_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include "baseinfo.h"
#include "contact.h"
#include "detail.h"


namespace Ui {
class Content;
}

class Content : public QFrame
{
    Q_OBJECT
    
public:
    explicit Content(QWidget *parent = 0,Qt::WindowFlags f = 0);
    ~Content(){}

    QPushButton *buttonAmend;
    QPushButton *buttonClose;

    QStackedWidget *stack;
    BaseInfo *base;
    Contact *cont;
    Detail *detail;


    
private:
    Ui::Content *ui;
};

#endif // CONTENT_H
