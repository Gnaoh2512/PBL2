#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::handleLogin);
    connect(ui->signUpButton, &QPushButton::clicked, this, &MainWindow::handleSignUp);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleLogin() {
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    Node* temp = accHead;
    while (temp) {
        if (temp->account->getUsername() == username.toStdString() &&
            temp->account->verifyPassword(password.toStdString())) {
            loggedInAccount = temp->account;
            QMessageBox::information(this, "Login Successful", "Welcome!");
            // Navigate to the next screen (e.g., User/Admin dashboard)
            return;
        }
        temp = temp->next;
    }

    QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
}

void MainWindow::handleSignUp() {
    QString name = ui->nameInput->text();
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString confirmPassword = ui->confirmPasswordInput->text();

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Sign Up Failed", "Passwords do not match.");
        return;
    }

    // Check if username already exists
    Node* temp = accHead;
    while (temp) {
        if (temp->account->getUsername() == username.toStdString()) {
            QMessageBox::warning(this, "Sign Up Failed", "Username is already taken.");
            return;
        }
        temp = temp->next;
    }

    User* newUser = new User(name.toStdString(), username.toStdString(), password.toStdString());
    addAccountToList(newUser);
    QMessageBox::information(this, "Sign Up Successful", "Account created successfully!");
}

void MainWindow::addAccountToList(Account* account) {
    Node* newNode = new Node(account, nullptr);
    if (!accHead) {
        accHead = newNode;
        accTail = newNode;
    } else {
        accTail->next = newNode;
        accTail = newNode;
    }
}
