#include "TreeView.h"

TreeCourse::TreeCourse(QWidget *parent):QWidget(parent)
{
    tree = new QTreeWidget;
    tree->setColumnCount(1);
    tree->setHeaderLabel(tr("课程"));
    course1 = new QTreeWidgetItem(QStringList(tr("语文")));
    tree->addTopLevelItem(course1);
    course2 = new QTreeWidgetItem(QStringList(tr("历史")));
    tree->addTopLevelItem(course2);
    course3 = new QTreeWidgetItem(QStringList(tr("艺术")));
    tree->addTopLevelItem(course3);
    course4 = new QTreeWidgetItem(QStringList(tr("英语")));
    tree->addTopLevelItem(course4);
    course5 = new QTreeWidgetItem(QStringList(tr("数学")));
    tree->addTopLevelItem(course5);

    childrenItem1 = new QTreeWidgetItem(QStringList("现代文学"));
    childrenItem2 = new QTreeWidgetItem(QStringList("古文学"));
    course1->addChild(childrenItem1);
    course1->addChild(childrenItem2);

    childrenItem5 = new QTreeWidgetItem(QStringList("现代史"));
    childrenItem6 = new QTreeWidgetItem(QStringList("古代史"));
    course2->addChild(childrenItem5);
    course2->addChild(childrenItem6);

    childrenItem3 = new QTreeWidgetItem(QStringList("油画"));
    childrenItem4 = new QTreeWidgetItem(QStringList("水彩"));
    course3->addChild(childrenItem3);
    course3->addChild(childrenItem4);




    // Add root nodes
    //addTreeRoot("A", "Root_first");
    //addTreeRoot("B", "Root_second");
    //addTreeRoot("C", "Root_third");
    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(tree);

    //QHBoxLayout *mainLayout = new QHBoxLayout;


    QGridLayout *mainlayout = new QGridLayout;
    setLayout(mainlayout);
    mainlayout->addLayout(leftLayout,0,0);

}

/*
void TreeCourse::addTreeRoot(QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    addTreeChild(treeItem, name + "A", "Child_first");
    addTreeChild(treeItem, name + "B", "Child_second");
}

void TreeCourse::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
}
*/
