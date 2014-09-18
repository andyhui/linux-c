#ifndef MYCLASS_H
#define MYCLASS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

class MyClass:public QWidget{
    Q_OBJECT
public:
    MyClass(QWidget *parent = 0);

private:
    QLabel* createPixmapLabel();
    QLabel* createHeaderLabel(const QString &text);


public slots:

};

#endif // MYCLASS_H
