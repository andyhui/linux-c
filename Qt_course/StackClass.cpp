#include <QtGui>
#include "StackClass.h"

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

StackClass::StackClass(QWidget *parent):QWidget(parent)
{
    QGridLayout *mainlayout = new QGridLayout;
    setLayout(mainlayout);

    showAllClassGroup();
    showMyClassGroup();
    showTreeGroup();

    /*右边布局*/
    msgW = new MsgWindows;
    QGridLayout *rightLayout = new QGridLayout;
    rightLayout->addWidget(msgW);

    /*中间列按钮*/
    QVBoxLayout *middleLayout = new QVBoxLayout;
    allClassButton = new QPushButton(tr("所有课程"),this);
    myClassButton = new QPushButton(tr("我的课程"),this);
    smallView= new QPushButton(tr("缩略图"),this);
    treeView =new QPushButton(tr("树状图"),this);
    middleLayout->addWidget(allClassButton);
    middleLayout->addWidget(myClassButton);
    middleLayout->addWidget(smallView);
    middleLayout->addWidget(treeView);
    middleLayout->addStretch();

    /*左部上边列按钮*/
    QHBoxLayout  *hLayout = new QHBoxLayout;
    createButton = new QPushButton(tr("创建"),this);
    deleteButton = new QPushButton(tr("删除"),this);
    otherButton = new QPushButton(tr("其他"),this);
    searEdit = new QLineEdit(tr("search"));
    searchButton = new QPushButton(tr("搜索"),this);
    hLayout->addWidget(createButton);
    hLayout->addWidget(deleteButton);
    hLayout->addWidget(otherButton);
    hLayout->addStretch();
    hLayout->addWidget(searEdit);
    hLayout->addWidget(searchButton);

    /*左下部分布局*/
    stack = new QStackedWidget;
    stack->addWidget(allClassGroup);
    stack->addWidget(myClassGroup);
    //stack->addWidget(myClass);
    stack->addWidget(treeGroup);
    //stack->addWidget(tree);

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addLayout(hLayout,0,0);
    leftLayout->addWidget(stack,1,0);
    //leftLayout->addLayout(vLayout,1,0);

    mainlayout->addLayout(leftLayout,0,0,0,8);
    mainlayout->addLayout(middleLayout,0,8,0,1);
    mainlayout->addLayout(rightLayout,0,9,0,4);

    QObject::connect(allClassButton, SIGNAL(clicked()),
                     this, SLOT(changeToAllStack()));

    QObject::connect(myClassButton, SIGNAL(clicked()),
            this, SLOT(changeToMyStack()));

    QObject::connect(treeView, SIGNAL(clicked()),
            this, SLOT(changeToTreeViewStack()));


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


QLabel* StackClass::createHeaderLabel(const QString &text)
{
    QLabel *label = new QLabel(tr("<b>%1</b>").arg(text));
    label->setAlignment(Qt::AlignCenter);
    return label;
}

QLabel* StackClass::createPixmapLabel()
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

void StackClass::showAllClassGroup()
{
    allClassGroup = new QGroupBox(tr("所有课程"));
    allClass = new AllClass;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(allClass);
    allClassGroup->setLayout(layout);

}

void StackClass::showMyClassGroup()
{
    myClassGroup = new QGroupBox(tr("我的课程"));
    myClass = new MyClass;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myClass);
    myClassGroup->setLayout(layout);

}

void StackClass::showTreeGroup()
{
    //treeGroup = new QGroupBox(tr("树形图"));
    treeGroup = new QGroupBox();
    tree = new TreeCourse;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tree);
    treeGroup->setLayout(layout);
}

void StackClass::changeToAllStack()
{
    stack->setCurrentIndex(0);
}
void StackClass::changeToMyStack()
{
    stack->setCurrentIndex(1);
}

void StackClass::changeToTreeViewStack()
{
    stack->setCurrentIndex(2);
}

