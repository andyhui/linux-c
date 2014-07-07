#include "content.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include <QApplication>

Content::Content(QWidget *parent, Qt::WindowFlags f):QFrame(parent,f){

    base = new BaseInfo;
    cont = new Contact;
    detail = new Detail;
    stack = new QStackedWidget;
    stack->addWidget(base);
    stack->addWidget(cont);
    stack->addWidget(detail);
    stack->setFrameStyle(QFrame::Panel|QFrame::Raised);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    buttonAmend = new QPushButton;
    buttonAmend->setText(tr("Amend"));
    buttonClose = new QPushButton;
    buttonClose->setText(tr("Close"));
    bottomLayout->addStretch();
    bottomLayout->addWidget(buttonAmend);
    bottomLayout->addWidget(buttonClose);
    bottomLayout->setMargin(10);
    bottomLayout->setSpacing(10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stack);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(10);

    connect(buttonClose,SIGNAL(clicked()),qApp,SLOT(quit()));
}
