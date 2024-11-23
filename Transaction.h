#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>

using namespace std;

class Transaction {
protected:
    uint64_t transactionId;
    string transactionDate, transactionType, username;
    int fromAccountId, toAccountId;
    double amount;

public:
    
    Transaction(uint64_t transId, const string &type,  const string &username, int fromAcc, int toAcc, double amt, const string &date);

    int getTransactionId() const { return transactionId; };
    string getTransactionDate() const { return transactionDate; };
    string getTransactionType() const { return transactionType; };
    string getUsername() const { return username; };
    int getFromAccountId() const { return fromAccountId; };
    int getToAccountId() const { return toAccountId; };
    double getAmount() const { return amount; };
    
    string getData() const;
    void displayInfo() const;
    static uint64_t generateUniqueTransactionId();
};

#endif // TRANSACTION_H