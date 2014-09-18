#ifndef ALLCLASS_H
#define ALLCLASS_H

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>

class AllClass :public QWidget{
    Q_OBJECT
public:
    AllClass(QWidget *parent = 0);

private:
    QLabel *createHeaderLabel(const QString &text);
    QLabel *createPixmapLabel();

};

#endif // ALLCLASS_H
