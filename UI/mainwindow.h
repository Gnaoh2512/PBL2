#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Account.h"
#include "../User.h"
#include "../Admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLogin();
    void handleSignUp();

private:
    Ui::MainWindow *ui;
    Account* loggedInAccount = nullptr;
    Node* accHead = nullptr;
    Node* accTail = nullptr;

    void addAccountToList(Account* account);
};

#endif // MAINWINDOW_H
