#include "curriculum.h"
#include "hscrolllabel.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QFrame>
#include <QString>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QCalendarWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QDateTimeEdit>
#include <QSizePolicy>

Curriculum::Curriculum(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 600);
    InitComponents();
    QGridLayout *layout = new QGridLayout(this);

    //QHBoxLayout *hLayout = new QHBoxLayout;
    //hLayout->addWidget();
    //hLayout->addLayout();

    //weeklyView->setGeometry(10, 10, 200, 50);
    //monthlyView->setGeometry(220, 10, 200, 50);
    //now->setGeometry(430, 10, 200, 50);
    //notice->setGeometry(640, 10, 250, 100);
    //headIcon->setGeometry(900, 10, 100, 100);
    //weeklyArea->setGeometry(10, 70, 620, 690);
    //calendar->setGeometry(640, 120, 360, 200);
    //dailyArea->setGeometry(640, 330, 360, 430);
    layout->setMargin(5);
    layout->addWidget(weeklyView, 0, 0, 1, 3);
    layout->addWidget(monthlyView, 0, 3, 1, 3);
    layout->addWidget(now, 0, 6, 1, 4);
    layout->addWidget(notice, 0, 10, 2, 4);
    layout->addWidget(headIcon, 0, 14, 2, 2);
    layout->addWidget(weeklyArea, 1, 0, 11, 10);
    layout->addWidget(calendar, 2, 10, 4, 6);
    layout->addWidget(dailyArea, 6, 10, 6, 6);
}

Curriculum::~Curriculum()
{
    delete weeklyView;
    delete monthlyView;
    delete now;
    delete notice;
    delete headIcon;
    delete weeklyArea;
    delete calendar;
    delete dailyArea;
}

void Curriculum::InitComponents()
{
    weeklyView = new QRadioButton("周课表");
    weeklyView->setChecked(true);
    monthlyView = new QRadioButton("月课表");
    now = new QDateTimeEdit(QDateTime::currentDateTime());
    notice = new HScrollLabel;
    notice->setMaximumSize(256, 128);
    notice->setText("我还不知道怎么获得天气，先测试水平滚动字幕，动态通知什么的再优化。");
    notice->setAlignment(Qt::AlignCenter);
    notice->setFrameStyle(1);
    headIcon = new QLabel("头像");
    headIcon->setAlignment(Qt::AlignCenter);
    headIcon->setFrameStyle(1);

    calendar = new QCalendarWidget;

    dailyArea = new QTableWidget(16, 2);
    dailyArea->setMinimumSize(200, 300);
    //dailyArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    dailyArea->setFrameStyle(QFrame::NoFrame);
    dailyArea->setShowGrid(false);
    dailyArea->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dailyArea->setSelectionMode(QAbstractItemView::NoSelection);
    dailyArea->horizontalHeader()->setVisible(false);
    dailyArea->verticalHeader()->setVisible(false);

    weeklyArea = new QTableWidget(17, 8);
    weeklyArea->setMinimumSize(300, 300);
    weeklyArea->setFrameStyle(QFrame::NoFrame);
    weeklyArea->setShowGrid(false);
    weeklyArea->setEditTriggers(QAbstractItemView::NoEditTriggers);
    weeklyArea->setSelectionMode(QAbstractItemView::NoSelection);
    weeklyArea->horizontalHeader()->setVisible(false);
    weeklyArea->verticalHeader()->setVisible(false);

    SetTableHeaders();

    dailyArea->setItem(0, 1, new QTableWidgetItem());
    dailyArea->setSpan(0, 1, dailyArea->rowCount(), 1);
    DrawDailyCurriculum();

    weeklyArea->setItem(1, 1, new QTableWidgetItem());
    weeklyArea->setSpan(1, 1, weeklyArea->rowCount()-1, 7);
    DrawWeeklyCurriculum();
}

void Curriculum::SetTableHeaders()
{
    QString t;
    int i, j;

    // set headers of weekly table
    weeklyArea->setItem(0, 1, new QTableWidgetItem("星期日"));
    weeklyArea->setItem(0, 2, new QTableWidgetItem("星期一"));
    weeklyArea->setItem(0, 3, new QTableWidgetItem("星期二"));
    weeklyArea->setItem(0, 4, new QTableWidgetItem("星期三"));
    weeklyArea->setItem(0, 5, new QTableWidgetItem("星期四"));
    weeklyArea->setItem(0, 6, new QTableWidgetItem("星期五"));
    weeklyArea->setItem(0, 7, new QTableWidgetItem("星期六"));

    for (i = 0; i < weeklyArea->columnCount()-1; i++)
    {
        if (i > 0)
        {
            weeklyArea->setColumnWidth(i, 100);
            weeklyArea->item(0, i)->setTextAlignment(Qt::AlignCenter);
        }
        else
        {
            weeklyArea->setColumnWidth(i, 80);
        }
    }

    for (i = 0; i < weeklyArea->rowCount()-1; i++)
    {
        weeklyArea->setRowHeight(i, 40);
        if (i > 0)
        {
            j = i + 6;
            if (j < 12)
            {
                t = QString("上午%1时").arg(j);
            }
            else if (j > 12)
            {
                j -= 12;
                t = QString("下午%1时").arg(j);
            }
            else
            {
                t = QString("中午%1时").arg(j);
            }

            weeklyArea->setItem(i, 0, new QTableWidgetItem(t));
            weeklyArea->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }
    weeklyArea->setRowHeight(weeklyArea->rowCount()-1, 20);


    // set headers of daily table
    dailyArea->setItem(0, 0, new QTableWidgetItem("全天"));
    dailyArea->item(0, 0)->setTextAlignment(Qt::AlignCenter);
    dailyArea->setColumnWidth(0, 80);
    dailyArea->setColumnWidth(1, 200);

    for (i = 0; i < dailyArea->rowCount()-1; i++)
    {
        dailyArea->setRowHeight(i, 40);
        if (i > 0)
        {
            j = i + 7;
            if (j < 12)
            {
                t = QString("上午%1时").arg(j);
            }
            else if (j > 12)
            {
                j -= 12;
                t = QString("下午%1时").arg(j);
            }
            else
            {
                t = QString("中午%1时").arg(j);
            }

            dailyArea->setItem(i, 0, new QTableWidgetItem(t));
            dailyArea->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }
    dailyArea->setRowHeight(dailyArea->rowCount()-1, 20);
}

void Curriculum::DrawWeeklyCurriculum()
{
    QPixmap pixmap(700, 620);
    QPainter painter(&pixmap);
    QPen pen;

    int x1 = 2;
    int y1 = 0;
    int dx1 = 94;
    int dx2 = 100;
    int dy2 = 20;
    int y2;
    int i, j;

    pixmap.fill();
    pen.setColor(Qt::gray);
    pen.setWidth(4);
    painter.setPen(pen);
    for (j = 0; j < 7; j++)
    {
        painter.drawLine(x1 + dx2*j, y1, x1 + dx1 + dx2*j, y1);
    }

    pen.setWidth(1);
    painter.setPen(pen);
    y2 = y1 - 20;
    for(i = 0; i < weeklyArea->rowCount()-2; i++)
    {
        y2 += dy2*2;
        for (j = 0; j < 7; j++)
        {
            painter.drawLine(x1 + dx2*j, y2, x1 + dx1 + dx2*j, y2);
        }
    }

    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    y2 = y1;
    for(i = 0; i < weeklyArea->rowCount()-2; i++)
    {
        y2 += dy2*2;
        for (j = 0; j < 7; j++)
        {
            painter.drawLine(x1 + dx2*j, y2, x1 + dx1 + dx2*j, y2);
        }
    }

    weeklyArea->item(1,1)->setBackground(QBrush(pixmap));
}

void Curriculum::DrawDailyCurriculum()
{
    QPixmap pixmap(200, 620);
    QPainter painter(&pixmap);
    QPen pen;

    int x1 = 0;
    int y1 = 0;
    int dx = 200;
    int dy = 20;
    int y2;
    int i;

    pixmap.fill();
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    painter.setPen(pen);
    y2 = y1 + dy;
    painter.drawLine(x1, y2, x1 +dx, y2);

    //y2 = y1 + dy;
    pen.setWidth(1);
    painter.setPen(pen);
    for (i = 0; i < dailyArea->rowCount()-2; i++)
    {
        y2 += dy*2;
        painter.drawLine(x1, y2, x1 + dx, y2);
    }

    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    y2 = y1;
    for(i = 0; i < dailyArea->rowCount()-1; i++)
    {
        y2 += dy*2;
        painter.drawLine(x1, y2, x1 + dx, y2);
    }

    dailyArea->item(0, 1)->setBackground(QBrush(pixmap));
}
