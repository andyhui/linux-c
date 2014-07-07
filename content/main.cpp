#include <QtGui/QApplication>
#include "content.h"
#include <QSplitter>
#include <QListWidget>
#include <QObject>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator trans;
    trans.load("../combineLayout/combine_zh.qm");
    app.installTranslator(&trans);
//    Content w;
//    w.show();

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    QListWidget *list = new QListWidget;
    list->addItem(QObject::tr("administartor"));
    list->addItem(QObject::tr("teacher"));
    list->addItem(QObject::tr("student"));
    splitter->addWidget(list);
    Content *content = new Content;
    splitter->addWidget(content);
    splitter->setOpaqueResize(true);
    splitter->show();
    splitter->setWindowTitle(QObject::tr("Change User Info"));

    QObject::connect(list,SIGNAL(currentRowChanged(int)),content->stack,SLOT(setCurrentIndex(int)));
    
    return app.exec();
}
