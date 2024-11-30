#ifndef LOANACCOUNT_H
#define LOANACCOUNT_H

#include "BankAccount.h"
#include <iostream>
#include <sstream>
#include <string>

class LoanAccount : public BankAccount {
private:
    double loanLimit = 30000;
    double latePaymentInterestRate = 0.1;
    double currentLoan;

public:
    LoanAccount(int accountId = 404, std::string username = "username", std::string createdDate = getCurrentDate(), double balance = 0, bool isFlagged = false, bool isFrozen = false, double currLoan = 0);

    ~LoanAccount() override {};
    void displayInfo() override;
    std::string getData() override;
    std::string getAccountType() override;
    bool withdraw(double amount) override;
    bool transfer(double amount, BankAccount& bankAcc) override;
    void monthlyUpdate() override;
};

#endif // LOANACCOUNT_H