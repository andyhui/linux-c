#ifndef DETAIL_H
#define DETAIL_H

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>

class Detail:public QWidget{
    Q_OBJECT
public:
    Detail(QWidget *parent = 0, Qt::WindowFlags f3 = 0);

    QLabel *labelCountry;
    QLabel *labelProvince;
    QLabel *labelCity;
    QLabel *labelIndividual;

    QComboBox *comboCountry;
    QComboBox *comboProvince;

    QLineEdit *lineCity;

    QTextEdit *textIndividual;
};

#endif // DETAIL_H
