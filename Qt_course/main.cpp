#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QListWidget>
//#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    MainWindow mainWin;
#if defined(Q_OS_SYMBIAN)
    mainWin.showMaximized();
#else
    mainWin.show();
#endif


    return a.exec();
/*
    Course w;
    w.show();
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    QListWidget *list = new QListWidget;
    list->addItem(QObject::tr("administartor"));
    list->addItem(QObject::tr("teacher"));
    list->addItem(QObject::tr("student"));
    splitter->addWidget(list);
    Course *course = new Course;
    splitter->addWidget(course);
    splitter->setOpaqueResize(true);
    splitter->show();
    splitter->setWindowTitle(QObject::tr("Change User Info"));

    QObject::connect(list,SIGNAL(currentRowChanged(int)),course->stack,SLOT(setCurrentIndex(int)));
*/

}
