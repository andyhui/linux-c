#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeWidget>
#include <QWidget>
#include <QHBoxLayout>

class TreeCourse:public QWidget
{
    Q_OBJECT
public:
    TreeCourse(QWidget *parent = 0);

private:
    QTreeWidget *tree;
    QTreeWidgetItem *course1;
    QTreeWidgetItem *course2;
    QTreeWidgetItem *course3;
    QTreeWidgetItem *course4;
    QTreeWidgetItem *course5;

    QTreeWidgetItem *childrenItem1;
    QTreeWidgetItem *childrenItem2;
    QTreeWidgetItem *childrenItem3;
    QTreeWidgetItem *childrenItem4;
    QTreeWidgetItem *childrenItem5;
    QTreeWidgetItem *childrenItem6;

    //void addTreeRoot(QString name, QString description);
    //void addTreeChild(QTreeWidgetItem *parent,
                          //QString name, QString description);

public slots:


};

#endif // TREEVIEW_H
