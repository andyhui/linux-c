#include <QtGui>
#include "AllClass.h"

/**布局
 * ----------
 * |        |
 * |        |
 * |        |
 * |        |
 * ----------
 **/

AllClass::AllClass(QWidget *parent):QWidget(parent)
{
    QGridLayout *mainlayout = new QGridLayout;
    setLayout(mainlayout);

    QGridLayout *vLayout = new QGridLayout;

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

    mainlayout->addLayout(vLayout,0,0);

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
