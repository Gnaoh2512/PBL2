#ifndef USER_H
#define USER_H

#include "Account.h"
#include "Transaction.h"
#include "LoanAccount.h"
#include "RegularAccount.h"
#include "SavingAccount.h"
#include "LinkedList.h"
#include "TimeUtils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>

using namespace std;

class User : public Account {
    LinkedList<Transaction> transactionHistory;
    LinkedList<BankAccount> userBankAccounts;

public:
    User(const string& name, const string& user, const string& pass)
        : Account(name, user, pass) {}

    ~User() override {
        userBankAccounts.clear();
        transactionHistory.clear();
    }

    void displayInfo() override {
        cout << "Name: " << name << "| Username: " << username << "| Password: " << password << endl;
    }

    void displayBankAccountsInfo();

    string getData() override {
        ostringstream oss;
        oss << "User|"
            << name << "|"
            << username << "|"
            << password << endl;
        return oss.str();
    }

    void deposit();
    void withdraw();
    void transfer(LinkedList<BankAccount> &bankAccs);
    void changePassword();
    void showTransactionHistory();
    void saveTransactionHistory();
    void loadTransactionHistory();
    void recordTransaction(const string& transactionType, double amount, long toAccId, BankAccount& bankAccount);
    void createBankAccount(SortedLinkedList<int>& usedAccountIds, LinkedList<BankAccount> &bankAccs);
    void loadBankAccount(LinkedList<BankAccount> &bankAccs);
    void showBankAccount();
    void displayActions(SortedLinkedList<int>& usedAccountIds, LinkedList<BankAccount> &bankAccs);
};

#endif // USER_H