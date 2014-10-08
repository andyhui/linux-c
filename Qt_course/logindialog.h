#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QRadioButton;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    int mysock;

signals:

private slots:
    void Login();

private:
    QLineEdit* userEdit;
    QLineEdit* passwdEdit;
    QPushButton* loginButton;
    QRadioButton* radio[3];

    void PrintWarning(QString str);
};

#endif // LOGINDIALOG_H
