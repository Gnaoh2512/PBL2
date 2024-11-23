#ifndef USER_H
#define USER_H

#include "Account.h"
#include "Transaction.h"
#include "LoanAccount.h"
#include "RegularAccount.h"
#include "SavingAccount.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>

using namespace std;

struct TransactionNode {
    Transaction* transaction;
    TransactionNode* next;
    TransactionNode(Transaction* trans, TransactionNode* nxt = nullptr) : transaction(trans), next(nxt) {}
};

class User : public Account {
    TransactionNode* transactionHistoryHead = nullptr;
    BankAccNode* bankAccountHead = nullptr;

public:
    User(const string& name, const string& user, const string& pass)
        : Account(name, user, pass) {}

    ~User() {
        TransactionNode* currentTransaction = transactionHistoryHead;
        while (currentTransaction != nullptr) {
            TransactionNode* temp = currentTransaction;
            currentTransaction = currentTransaction->next;
            delete temp->transaction;
            delete temp;
        }

        BankAccNode* currentAccount = bankAccountHead;
        while (currentAccount != nullptr) {
            BankAccNode* temp = currentAccount;
            currentAccount = currentAccount->next;
            delete temp->account;
            delete temp;
        }
    }

    void displayInfo() override {
        cout << "Name: " << name << endl;
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
    void transfer(BankAccNode* bankAccHead);
    void changePassword();
    void showTransactionHistory();
    void saveTransactionHistory();
    void loadTransactionHistory();
    void recordTransaction(const string& transactionType, double amount, long toAccId, BankAccount& bankAccount);
    void createBankAccount(SortedLinkedList<int>& usedAccountIds, BankAccNode* bankAccHead, BankAccNode* bankAccTail);
    void loadBankAccount(BankAccNode* bankAccHead);
    void showBankAccount();
    void displayActions(SortedLinkedList<int>& usedAccountIds, BankAccNode* bankAccHead, BankAccNode* bankAccTail);
};

#endif // USER_H