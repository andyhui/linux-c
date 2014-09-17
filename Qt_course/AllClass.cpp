#include <QtGui>
#include "AllClass.h"

/**布局
 * --------------
 * |        |   |
 * ----------   |
 * |        |   |
 * |        |   |
 * |        |   |
 * |        |   |
 * --------------
 **/

AllClass::AllClass(QWidget *parent):QWidget(parent)
{
    QGridLayout *mainlayout = new QGridLayout;
    setLayout(mainlayout);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    QGridLayout *vLayout = new QGridLayout;

    createButton = new QPushButton(tr("创建"),this);
    deleteButton = new QPushButton(tr("删除"),this);
    otherButton = new QPushButton(tr("其他"),this);
    searchButton = new QPushButton(tr("搜素"),this);

    allClassButton = new QPushButton(tr("所有课程"),this);
    myClassButton = new QPushButton(tr("我的课程"),this);
    smallView= new QPushButton(tr("缩略图"),this);
    treeView =new QPushButton(tr("树状图"),this);
    rightLayout->addWidget(allClassButton);
    rightLayout->addWidget(myClassButton);
    rightLayout->addWidget(smallView);
    rightLayout->addWidget(treeView);
    rightLayout->addStretch();

    searEdit = new QLineEdit(tr("search"));

    QHBoxLayout  *hLayout = new QHBoxLayout;
    hLayout->addWidget(createButton);
    hLayout->addWidget(deleteButton);
    hLayout->addWidget(otherButton);
    hLayout->addStretch();
    hLayout->addWidget(searEdit);
    hLayout->addWidget(searchButton);

    QVBoxLayout *layout1    = new QVBoxLayout;
    QVBoxLayout *layout2    = new QVBoxLayout;
    QVBoxLayout *layout3    = new QVBoxLayout;
    QVBoxLayout *layout4    = new QVBoxLayout;

    layout1->addWidget(createPixmapLabel(),0,0);
    layout1->addWidget(createHeaderLabel(tr("数学")),1,0);
    layout1->addWidget(createPixmapLabel(),2,0);
    layout1->addWidget(createHeaderLabel(tr("数学")),3,0);
    layout1->addWidget(createPixmapLabel(),4,0);
    layout1->addWidget(createHeaderLabel(tr("数学")),5,0);
    layout1->addWidget(createPixmapLabel(),6,0);
    layout1->addWidget(createHeaderLabel(tr("数学")),7,0);

    layout2->addWidget(createPixmapLabel(),0,0);
    layout2->addWidget(createHeaderLabel(tr("语文")),1,0);
    layout2->addWidget(createPixmapLabel(),2,0);
    layout2->addWidget(createHeaderLabel(tr("语文")),3,0);
    layout2->addWidget(createPixmapLabel(),4,0);
    layout2->addWidget(createHeaderLabel(tr("数学")),5,0);
    layout2->addWidget(createPixmapLabel(),6,0);
    layout2->addWidget(createHeaderLabel(tr("数学")),7,0);

    layout3->addWidget(createPixmapLabel(),0,0);
    layout3->addWidget(createHeaderLabel(tr("美术")),1,0);
    layout3->addWidget(createPixmapLabel(),2,0);
    layout3->addWidget(createHeaderLabel(tr("数学")),3,0);
    layout3->addWidget(createPixmapLabel(),4,0);
    layout3->addWidget(createHeaderLabel(tr("语文")),5,0);
    layout3->addWidget(createPixmapLabel(),6,0);
    layout3->addWidget(createHeaderLabel(tr("历史")),7,0);

    layout4->addWidget(createPixmapLabel(),0,0);
    layout4->addWidget(createHeaderLabel(tr("英语")),1,0);
    layout4->addWidget(createPixmapLabel(),2,0);
    layout4->addWidget(createHeaderLabel(tr("数学")),3,0);
    layout4->addWidget(createPixmapLabel(),4,0);
    layout4->addWidget(createHeaderLabel(tr("政治")),5,0);
    layout4->addWidget(createPixmapLabel(),6,0);
    layout4->addWidget(createHeaderLabel(tr("物理")),7,0);

    vLayout->addLayout(layout1,0,0);
    vLayout->addLayout(layout2,0,1);
    vLayout->addLayout(layout3,0,2);
    vLayout->addLayout(layout4,0,3);

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addLayout(hLayout,0,0);
    leftLayout->addLayout(vLayout,1,0);

    mainlayout->addLayout(leftLayout,0,0);
    mainlayout->addLayout(rightLayout,0,1);


    //stateLabels[0] = createHeaderLabel(tr("数学"));
    //stateLabels[1] = createHeaderLabel(tr("语文"));
    //stateLabels[2] = createHeaderLabel(tr("美术"));
    //stateLabels[3] = createHeaderLabel(tr("英语"));
    //Q_ASSERT(NumStates == 4);

    //layout->addWidget();
/*
    for (int i = 0; i < NumStates; i ++) {
        for (int j = 0; j < NumStates; ++j) {
            //pixmapLabels[i][j] = createPixmapLabel("shuxue");
            //mainlayout->addWidget(pixmapLabels[i][j], i, j);
            stateLabels[i][j] = createPixmapLabel("shuxue");
            mainlayout->addWidget(stateLabels[i][j],i,j);
        }
    }
    /*
    layout1->addWidget(stateLabels[0],0,0,1,1);
    layout1->addWidget(stateLabels[1],0,1,1,1);
    layout1->addWidget(stateLabels[2],0,2,1,1);
    layout1->addWidget(stateLabels[3],0,3,1,1);
    mainlayout->addWidget(stateLabels[0],1,0,1,1);
    mainlayout->addWidget(stateLabels[1],1,1,1,1);
    mainlayout->addWidget(stateLabels[2],1,2,1,1);
    mainlayout->addWidget(stateLabels[3],1,3,1,1);
    //mainlayout->addWidget(stateLabels[4],j,i,1,1);
    /*
    for(int i = 0; i < NumStates;i++)
    {
        for(int j = 0;j < NumStates;++j)
        {
            mainlayout->addWidget(stateLabels[j],j,i,1,1);
            mainlayout->addWidget(stateLabels[j+1],j,i+1,1,1);
        }
    }*/
}


QLabel* AllClass::createHeaderLabel(const QString &text)
{
    QLabel *label = new QLabel(tr("<b>%1</b>").arg(text));
    label->setAlignment(Qt::AlignCenter);
    return label;
}

QLabel* AllClass::createPixmapLabel()
{
    QLabel *label = new QLabel;
    //QLabel *label = new QLabel(tr("<b>%1</b>").arg(text));
    label->setEnabled(false);
    label->setAlignment(Qt::AlignCenter);
    label->setFrameShape(QFrame::Box);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setBackgroundRole(QPalette::Base);
    label->setAutoFillBackground(true);
    label->setMinimumSize(132, 132);
    return label;

}
