#ifndef REGULARACCOUNT_H
#define REGULARACCOUNT_H

#include "BankAccount.h"
#include <iostream>
#include <string>
#include <sstream>

class RegularAccount : public BankAccount {
private:
    double monthlyFee = 5;
    double transactionFee = 1;

public:
    RegularAccount(int accountId = 404, std::string username = "username", std::string createdDate = getCurrentDate(), double balance = 0, bool isFlagged = false, bool isFrozen = false);

    void displayInfo() override;
    std::string getData() override;
    std::string getAccountType() override;
    bool withdraw(double amount) override;
    bool transfer(double amount, BankAccount& bankAcc) override;
    void monthlyUpdate() override;
};

#endif // REGULARACCOUNT_H