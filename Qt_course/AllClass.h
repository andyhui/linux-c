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

    QPushButton class4;
    QPushButton class5;
    QPushButton class6;
    QPushButton class7;
    QPushButton class8;
    QPushButton class9;
    QPushButton class10;
    QPushButton class11;
    QPushButton class12;
    QPushButton class13;
    QPushButton class14;
    QPushButton class15;
    QPushButton class16;

private:
    QLabel *createHeaderLabel(const QString &text);
    QLabel *createPixmapLabel();

    enum { NumModes = 4, NumStates = 4 };

    QLabel *stateLabels[NumStates][NumStates];
    //QLabel *modeLabels[NumModes];
    QLabel *pixmapLabels[NumModes][NumStates];

    QPushButton *createButton;
    QPushButton *deleteButton;
    QPushButton *otherButton;
    QPushButton *searchButton;

    QPushButton *allClassButton;
    QPushButton *myClassButton;
    QPushButton *smallView;
    QPushButton *treeView;

    QLineEdit *searEdit;



};

#endif // ALLCLASS_H
