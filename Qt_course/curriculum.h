#ifndef CURRICULUM_H
#define CURRICULUM_H

#include <QWidget>

class QCalendarWidget;
class QTableWidget;
class QRadioButton;
class QDateTimeEdit;
class QLabel;
class HScrollLabel;

class Curriculum : public QWidget
{
    Q_OBJECT

public:
    Curriculum(QWidget *parent = 0);
    ~Curriculum();

signals:

public slots:
    void DrawWeeklyCurriculum();
    void DrawDailyCurriculum();

private:
    QRadioButton *weeklyView;
    QRadioButton *monthlyView;
    QDateTimeEdit *now;
    QCalendarWidget *calendar;
    QTableWidget *weeklyArea;
    QTableWidget *dailyArea;
    QLabel *headIcon;
    HScrollLabel *notice;

    void InitComponents();
    void SetTableHeaders();
};

#endif // CURRICULUM_H
