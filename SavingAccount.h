#ifndef SAVINGACCOUNT_H
#define SAVINGACCOUNT_H

#include "BankAccount.h"
#include <string>
#include <sstream>
#include <iostream>

class SavingAccount : public BankAccount {
private:
    float interestRate = 0.05;
    double minimumBalance = 100;

public:
    SavingAccount(int accountId = 404, std::string username = "username", std::string createdDate = getCurrentDate(), double balance = 0, bool isFlagged = false, bool isFrozen = false);

    void displayInfo() override;
    std::string getData() override;
    std::string getAccountType() override;
    bool withdraw(double amount) override;
    bool transfer(double amount, BankAccount& bankAcc) override;
    void monthlyUpdate() override;
};

#endif // SAVINGACCOUNT_H