#include "MsgWindows.h"

MsgWindows::MsgWindows(QWidget *parent):QWidget(parent)
{
    histogramItem = new Histogram;

    stateIcon = new QLabel(QObject::trUtf8("小图片"));
    stateLabel = new QLabel(QObject::trUtf8("状态"));
    introDuction = new QLabel(QObject::trUtf8("简介"));
    introDuction->setAlignment(Qt::AlignCenter);
    introDuction->setFrameStyle(1);

    QGridLayout *headArea = new QGridLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    scrollLabel = new QLabel(QObject::trUtf8("滚动新闻"));
    //scrollLabel->setAlignment(Qt::AlignCenter);
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(3);
    scrollLabel->setSizePolicy(spLeft);
    topLayout->addWidget(scrollLabel);
    //headerIcon->setFrameStyle(1);
    //headerIcon = new QIcon;
    //stateIcon = new QIcon;
    headerIcon = new QLabel(QObject::trUtf8("头像"));
    //headerIcon->setFrameStyle(1);
    //headerIcon->setAlignment(Qt::AlignCenter);
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    headerIcon->setSizePolicy(spRight);
    topLayout->addWidget(headerIcon);

    QVBoxLayout *stateLayout = new QVBoxLayout;
    stateLayout->addWidget(stateIcon);
    stateLayout->addWidget(stateLabel);
    headArea->addLayout(topLayout,0,0,4,2);
    headArea->addLayout(stateLayout,4,0,2,2);
    headArea->addWidget(introDuction,4,2,2,2);

    content = new QStackedWidget;

    introButton = new QPushButton(QObject::tr("简介"));
    chartButton = new QPushButton(QObject::tr("统计图"));
    marksButton = new QPushButton(QObject::tr("备注"));

    QHBoxLayout  *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(introButton);
    bottomLayout->addWidget(chartButton);
    bottomLayout->addWidget(marksButton);


    QGridLayout *mainLayout = new QGridLayout;
    setLayout(mainLayout);
    mainLayout->addLayout(headArea,0,0);
    mainLayout->addWidget(content,1,0);
    //mainLayout->addStrch();
    mainLayout->addLayout(bottomLayout,2,0);
}

void MsgWindows::changeHeaderIcon()
{
//add codes
}


