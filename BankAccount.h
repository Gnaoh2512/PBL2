#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "SortedLinkedList.h"
#include <string>
#include <sstream>

using namespace std;

class BankAccount {
protected:
    int accountId;
    string username;
    string createdDate;
    double balance;
    bool isFrozen;
    bool isFlagged;

public:
    BankAccount(int accountId, string username, string createdDate, double balance = 0, bool isFlagged = false, bool isFrozen = false) : accountId(accountId), username(username), balance(balance), createdDate(createdDate), isFlagged(isFlagged), isFrozen(isFrozen) {}
    
    double getBalance() const { return balance; }
    string getCreatedDate() const { return createdDate; }
    bool getIsFrozen() const { return isFrozen; }
    bool getIsFlagged() const { return isFlagged; }
    string getUsername() const { return username; }
    int getAccountId() const { return accountId; }
    void freeze() { isFrozen = true; }
    void unFreeze() { isFrozen = false; }
    void setAccountId(int Id) { accountId = Id; }
    void deposit(double amount) {
        BankAccount::balance += amount;
        std::cout << "Deposit succeeded. Current balance: $" << balance << std::endl;
    }

    static int generateAccountId(SortedLinkedList<int>& usedAccountIds);
    static string getCurrentDate();

    virtual void displayInfo() = 0;
    virtual string getData() = 0;
    virtual string getAccountType() = 0;
    virtual bool withdraw(double amount) = 0;
    virtual void monthlyUpdate() = 0;
};

struct BankAccNode {
    BankAccount* account;
    BankAccNode* next;
    BankAccNode(BankAccount* acc, BankAccNode* nxt = nullptr) : account(acc), next(nxt) {}
};

#endif // BANKACCOUNT_H