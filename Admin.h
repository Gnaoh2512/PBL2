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

    ~Admin() override {};

    void displayInfo() override {
        cout << "Admin Account: " << name << endl;
    }

    string getData() override {
        ostringstream oss;
        oss << "Admin|"
            << name << "|"
            << username << "|"
            << password << endl;
        return oss.str();
    }

    void freezeBankAccount(LinkedList<BankAccount>& bankAccs);
    void unFreezeBankAccount(LinkedList<BankAccount>& bankAccs);
    void viewBankAccountInfo(LinkedList<BankAccount>& bankAccs) const;
    void deleteBankAccount(LinkedList<BankAccount>& bankAccs);
    void viewUserInfo(LinkedList<Account>& accs) const;
    void viewUserTransactionHistory(LinkedList<Account>& accs) const;
    void deleteUser(LinkedList<Account>& accs);
    void displayActions(LinkedList<Account> &accs, LinkedList<BankAccount> &bankAccs);
};

#endif // ADMIN_H