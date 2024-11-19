#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <iostream>
#include <string>

using namespace std;

class Admin : public Account {
public:
    Admin(const string& name, const string& user, const string& pass)
    : Account(name, user, pass) {}

    ~Admin() {};

    void displayInfo() override {
        cout << "Admin Account: " << name << endl;
    };

    string getData() override {
        ostringstream oss;
        oss << "Admin|"
            << name << "|"
            << username << "|"
            << password << endl;
        return oss.str();
    }

    void freezeBankAccount(BankAccNode* bankAccHead);
    void unFreezeBankAccount(BankAccNode* bankAccHead);
    void viewBankAccountInfo(BankAccNode* bankAccHead) const;
    void deleteBankAccount(BankAccNode*& head);
    void viewUserInfo(Node* head) const;
    void viewUserTransactionHistory(Node* head) const;
    void deleteUser(Node*& head);
    void displayActions(Node* head, BankAccNode* bankAccHead);
};

#endif // ADMIN_H