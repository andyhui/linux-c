#include "hscrolllabel.h"
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>

HScrollLabel::HScrollLabel(QWidget *parent) :
    QLabel(parent)
{
    flag = false;
    offset = 0;
    timerId = 0;
    textWidth = 0;

    connect(this, SIGNAL(currentTextChanged()), this, SLOT(metrics()));
}

void HScrollLabel::setText(const QString &curText)
{
    if (text() != curText)
    {
        QLabel::setText(curText);
        QLabel::setAlignment(Qt::AlignCenter);
        emit currentTextChanged();
    }
}

void HScrollLabel::startScroll()
{
    timerId = startTimer(50);
}

void HScrollLabel::metrics()
{
    flag = false;
    offset = 0;
    textWidth = 0;

    if(getWidth() < width())
    {
        return;
    }

    flag = true;
    textWidth = getWidth() +width();
    QTimer::singleShot(500, this, SLOT(startScroll()));
}

int HScrollLabel::getWidth()
{
    int fm_width = fontMetrics().width(text());
    return  fm_width;
}

void HScrollLabel::showEvent(QShowEvent *)
{
    metrics();
}

void HScrollLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//if (textWidth < 1) return;

    if(!flag)
    {
        painter.drawText(0, 0, width(), height() ,
        Qt::AlignHCenter | Qt::AlignVCenter, text());

        return;
    }

    int x = -offset ;
    while (x < width())
    {
        painter.drawText(x, 0, textWidth, height() ,
        Qt::AlignHCenter | Qt::AlignVCenter, text());
        x += textWidth;
    }
}

void HScrollLabel::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        offset += 2;
        if (offset >= textWidth)
        {
            offset = 0;
        }
        scroll(-1, 0);            // 这里是从右向左滚动
    }
    else
    {
        QWidget::timerEvent(event);
    }
}

//void HScrollLabel::hideEvent(QHideEvent *)
//{
//    offset = 0;
//    if (timerId)
//    {
//        killTimer(timerId);
//    }
//}
