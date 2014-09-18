#ifndef HSCROLLLABEL_H
#define HSCROLLLABEL_H

#include <QLabel>

class HScrollLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HScrollLabel(QWidget *parent = 0);
    virtual ~HScrollLabel(){}

public slots:
    void setText(const QString &);

signals:
    void currentTextChanged();

protected:
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
//    void hideEvent(QHideEvent *);

private slots:
    void metrics();
    void startScroll();

private:
    int offset;
    int timerId;
    int textWidth;
    bool flag;

    int getWidth();
};

#endif // HSCROLLLABEL_H
