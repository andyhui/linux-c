#include "MsgWindows.h"

MsgWindows::MsgWindows(QWidget *parent):QWidget(parent)
{
    histogramItem = new Histogram;

    //histogramItem->Paint();

    stateIcon = new QLabel(QObject::trUtf8("小图片"));
    stateIcon->setAlignment(Qt::AlignCenter);
    stateLabel = new QLabel(QObject::trUtf8("状态"));
    stateLabel->setAlignment(Qt::AlignCenter);
    introDuction = new QLabel(QObject::trUtf8("简介"));
    introDuction->setAlignment(Qt::AlignCenter);
    introDuction->setFrameStyle(1);

    QGridLayout *headArea = new QGridLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;

    scrollLabel = new QLabel(QObject::trUtf8("滚动新闻"));
    scrollLabel->setMargin(15);
    scrollLabel->setFrameStyle(3);
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
    headerIcon->setAlignment(Qt::AlignCenter);
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    headerIcon->setSizePolicy(spRight);
    topLayout->addWidget(headerIcon);


    QGridLayout *stateLayout = new QGridLayout;
    //stateLayout->addWidget(stateIcon,0,0,1,1);
    //stateLayout->addWidget(stateLabel,1,0,1,1);
    //stateLayout->addWidget(introDuction,0,1,2,1);
   // introDuction->setMinimumSize(10,100);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(stateIcon);
    vlayout->addWidget(stateLabel);
    //introDuction->setBaseSize(20,100);
   // stateLayout->addWidget(stateIcon,0,0);
    //stateIcon->
   // stateLayout->addWidget(stateLabel,1,0);
    //stateIcon
    stateLayout->addLayout(vlayout,0,0);
    stateLayout->addWidget(introDuction,0,1);


    headArea->addLayout(topLayout,0,0,4,4);
    headArea->addLayout(stateLayout,4,0,2,4);
    //headArea->addWidget(introDuction,1,2,2,2);

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


