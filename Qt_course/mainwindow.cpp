#include <QtGui>
#include <QSizePolicy>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    addIconGrupBox();
    showCurriculum();

    createActions();
    createMenus();

    QGridLayout *mainLayout = new QGridLayout;

    stack = new QStackedWidget;

    list = new QListWidget;
    //msgW = new MsgWindows;
    list->insertItem(0,QObject::tr("课程"));
    list->insertItem(1,QObject::tr("课程表"));
    //list->addItem(QObject::tr("课程填报"));
    //list->addItem(QObject::tr("通讯&聊天"));
    //list->addItem(QObject::tr("设置"));
    QSizePolicy qtSp(QSizePolicy::Preferred,QSizePolicy::Preferred,QSizePolicy::PushButton);
    list->setSizePolicy(qtSp);

    /*
    QVBoxLayout *vChooseMenu = new QVBoxLayout;
    course = new QPushButton(tr("课程"),this);
    courseTable = new QPushButton(tr("课程表"),this);
    chooseCourse = new QPushButton(tr("课程填报"),this);
    communicate = new QPushButton(tr("通讯&聊天"),this);
    setting = new QPushButton(tr("设置"),this);
    //vChooseMenu->setSpacing(4);
    vChooseMenu->addStretch(2);
    vChooseMenu->addWidget(course,0,Qt::AlignTop);
    vChooseMenu->addWidget(courseTable,0,Qt::AlignTop);
    vChooseMenu->addWidget(chooseCourse,0,Qt::AlignTop);
    vChooseMenu->addWidget(communicate,0,Qt::AlignTop);
    vChooseMenu->addWidget(setting,0,Qt::AlignTop);
    vChooseMenu->addStretch(26);
    //vChooseMenu->setSizePolicy(qtSp);
    */


    stack->addWidget(classGroupBox);
    stack->addWidget(curriculumGroupBox);

    mainLayout->addWidget(list,0,0);
    //mainLayout->addLayout(vChooseMenu,0,0);
    //mainLayout->addWidget(stack,0,Qt::AlignHCenter);
    mainLayout->addWidget(stack,0,1);
    //mainLayout->addWidget(msgW,0,2);

    centralWidget->setLayout(mainLayout);

    setWindowTitle(tr("select course"));

    connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));

}
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Icons"),
            tr("The <b>Icons</b> example illustrates how Qt renders an icon in "
               "different modes (active, normal, disabled, and selected) and "
               "states (on and off) based on a set of images."));
}

void MainWindow::addIconGrupBox()
{
    //classGroupBox = new QGroupBox(tr("select course"));
    classGroupBox = new QGroupBox();

    stackClass = new StackClass;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackClass);
    classGroupBox->setLayout(layout);
}

void MainWindow::showCurriculum()
{
    curriculumGroupBox = new QGroupBox(tr("curriculum"));

    curriculum = new Curriculum;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(curriculum);
    curriculumGroupBox->setLayout(layout);
}

void MainWindow::createActions()
{
    addImagesAct = new QAction(tr("&Add Images..."), this);
    addImagesAct->setShortcut(tr("Ctrl+A"));
    connect(addImagesAct, SIGNAL(triggered()), this, SLOT(addImages()));

    removeAllImagesAct = new QAction(tr("&Remove All Images"), this);
    removeAllImagesAct->setShortcut(tr("Ctrl+R"));
    connect(removeAllImagesAct, SIGNAL(triggered()),
            this, SLOT(removeAllImages()));

    exitAct = new QAction(tr("&Quit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    /*styleActionGroup = new QActionGroup(this);
    foreach (QString styleName, QStyleFactory::keys()) {
        QAction *action = new QAction(styleActionGroup);
        action->setText(tr("%1 Style").arg(styleName));
        action->setData(styleName);
        action->setCheckable(true);
        connect(action, SIGNAL(triggered(bool)), this, SLOT(changeStyle(bool)));
    }
    */

    guessModeStateAct = new QAction(tr("&Guess Image Mode/State"), this);
    guessModeStateAct->setCheckable(true);
    guessModeStateAct->setChecked(true);

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(addImagesAct);
    fileMenu->addAction(removeAllImagesAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("编辑"));
    /*foreach (QAction *action, styleActionGroup->actions())
        viewMenu->addAction(action);*/
    viewMenu->addSeparator();
    viewMenu->addAction(guessModeStateAct);

    viewMenu = menuBar()->addMenu(tr("共享"));
    /*foreach (QAction *action, styleActionGroup->actions())
        viewMenu->addAction(action);*/
    viewMenu->addSeparator();
    viewMenu->addAction(guessModeStateAct);

    viewMenu = menuBar()->addMenu(tr("显示"));
    /*foreach (QAction *action, styleActionGroup->actions())
        viewMenu->addAction(action);*/
    viewMenu->addSeparator();
    //viewMenu->addAction(guessModeStateAct);

    viewMenu = menuBar()->addMenu(tr("窗口"));
    /*foreach (QAction *action, styleActionGroup->actions())
        viewMenu->addAction(action);*/
    viewMenu->addSeparator();
    //viewMenu->addAction(guessModeStateAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::addImages()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                    tr("Open Images"), "",
                                    tr("Images (*.png *.xpm *.jpg);;"
                                       "All Files (*)"));
    if (!fileNames.isEmpty()) {
        foreach (QString fileName, fileNames) {
            //int row = imagesTable->rowCount();
            //imagesTable->setRowCount(row + 1);


            QString imageName = QFileInfo(fileName).baseName();

            QTableWidgetItem *item0 = new QTableWidgetItem(imageName);
            item0->setData(Qt::UserRole, fileName);
            item0->setFlags(item0->flags() & ~Qt::ItemIsEditable);



            QTableWidgetItem *item1 = new QTableWidgetItem(tr("Normal"));

            QTableWidgetItem *item2 = new QTableWidgetItem(tr("Off"));

            if (guessModeStateAct->isChecked()) {
                if (fileName.contains("_act")) {
                    item1->setText(tr("Active"));
                } else if (fileName.contains("_dis")) {
                    item1->setText(tr("Disabled"));
                } else if (fileName.contains("_sel")) {
                    item1->setText(tr("Selected"));
                }

                if (fileName.contains("_on"))
                    item2->setText(tr("On"));

            }

            //imagesTable->setItem(row, 0, item0);

            //imagesTable->setItem(row, 1, item1);
            //imagesTable->setItem(row, 2, item2);
            //imagesTable->openPersistentEditor(item1);
            //imagesTable->openPersistentEditor(item2);

            item0->setCheckState(Qt::Checked);
        }
    }
}

void MainWindow::removeAllImages()
{
    //imagesTable->setRowCount(0);
    //changeIcon();
}

/*void MainWindow::createContextMenu()
{
    imagesTable->setContextMenuPolicy(Qt::ActionsContextMenu);
    imagesTable->addAction(addImagesAct);
    imagesTable->addAction(removeAllImagesAct);
}

void MainWindow::changeIcon()
{
    QIcon icon;

    for (int row = 0; row < imagesTable->rowCount(); ++row) {
        QTableWidgetItem *item0 = imagesTable->item(row, 0);
        QTableWidgetItem *item1 = imagesTable->item(row, 1);
        QTableWidgetItem *item2 = imagesTable->item(row, 2);

        if (item0->checkState() == Qt::Checked) {
            QIcon::Mode mode;
            if (item1->text() == tr("Normal")) {
                mode = QIcon::Normal;
            } else if (item1->text() == tr("Active")) {
                mode = QIcon::Active;
            } else if (item1->text() == tr("Disabled")) {
                mode = QIcon::Disabled;
            } else {
                mode = QIcon::Selected;
            }

            QIcon::State state;
            if (item2->text() == tr("On")) {
                state = QIcon::On;
            } else {
                state = QIcon::Off;

            }

            QString fileName = item0->data(Qt::UserRole).toString();
            QImage image(fileName);
            if (!image.isNull())
                icon.addPixmap(QPixmap::fromImage(image), mode, state);
        }
    }
    previewArea->setIcon(icon);
}
*/
