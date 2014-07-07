#include "detail.h"
#include <QGridLayout>
#include <QStringList>

Detail::Detail(QWidget *parent, Qt::WindowFlags f3):QWidget(parent,f3){

    labelCountry = new QLabel(tr("Country/Area:"));
    labelProvince = new QLabel(tr("Province:"));
    labelCity = new QLabel(tr("City:"));
    labelIndividual = new QLabel(tr("Individual:"));

    comboCountry = new QComboBox;
    QStringList listCountry;
    listCountry<<tr("China")<<tr("America")<<tr("Canada")<<tr("France")<<tr("England")<<tr("Germany")
               <<tr("Japan")<<tr("Span")<<tr("Greece")<<tr("Australia")<<tr("Russia");
    comboCountry->addItems(listCountry);
    comboProvince = new QComboBox;
    QStringList listProvince;
    listProvince<<tr("Beijing")<<tr("Shanghai")<<tr("Tianjin")<<tr("Chongqin")<<tr("Hunan")<<tr("Hubei")
                <<tr("Heilongjiang")<<tr("Jilin")<<tr("Liaoning")<<tr("Neimenggu")<<tr("Xinjiang")
                <<tr("Xizang")<<tr("Jiangsu")<<tr("Anhui")<<tr("Guangdong")<<tr("Guangxi")<<tr("Yunnan")
                <<tr("Sichuang")<<tr("Guizhou")<<tr("Hebei")<<tr("Henan")<<tr("Shanxi")<<tr("Shan xi")
                <<tr("Shandong")<<tr("Fujian");
    comboProvince->addItems(listProvince);

    lineCity = new QLineEdit;

    textIndividual = new QTextEdit;

    QGridLayout *mainLayout3 = new QGridLayout(this);
    mainLayout3->addWidget(labelCountry,0,0);
    mainLayout3->addWidget(comboCountry,0,1);
    mainLayout3->addWidget(labelProvince,1,0);
    mainLayout3->addWidget(comboProvince,1,1);
    mainLayout3->addWidget(labelCity,2,0);
    mainLayout3->addWidget(lineCity,2,1);
    mainLayout3->addWidget(labelIndividual,3,0,Qt::AlignTop);
    mainLayout3->addWidget(textIndividual,3,1);
    mainLayout3->setMargin(15);
    mainLayout3->setSpacing(15);
    mainLayout3->setColumnStretch(0,1);
    mainLayout3->setColumnStretch(1,3);
}
