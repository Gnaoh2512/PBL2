#include "LoanAccount.h"

LoanAccount::LoanAccount(int accountId, std::string username, std::string createdDate, double balance, bool isFlagged, bool isFrozen, double currLoan)
    : BankAccount(accountId, username, createdDate, balance, isFlagged, isFrozen), currentLoan(currLoan) {}

void LoanAccount::displayInfo() {
    std::cout << "Loan Account - Account Id: " << accountId 
              << ", Created Date: " << createdDate
              << ", Balance: " << balance
              << ", Loan Limit: " << loanLimit
              << ", Late Payment Interest Rate: " << latePaymentInterestRate * 100 << "%"
              << ", Current Loan: " << currentLoan
              << ", Is Flagged: " << (isFlagged ? "Yes" : "No")
              << ", Is Frozen: " << (isFrozen ? "Yes" : "No") << std::endl;
}

std::string LoanAccount::getAccountType() {
    return "loan";
}

std::string LoanAccount::getData() {
    std::ostringstream oss;
    oss << accountId << "|"
        << username << "|"
        << "loan|"
        << createdDate << "|"
        << balance << "|"
        << (isFlagged ? "1" : "0") << "|"
        << (isFrozen ? "1" : "0") << "|" << currentLoan << std::endl;
    return oss.str();
}

bool LoanAccount::withdraw(double amount) {
    if (loanLimit - amount - currentLoan < 0) {
        std::cout << "Exceeded loan limit." << std::endl;
        return false;
    } else {
        currentLoan += amount;
        std::cout << "Withdraw succeeded. Current loan: $" << currentLoan << std::endl;
        return true;
    }
}

bool LoanAccount::transfer(double amount, BankAccount& bankAcc) {
    if (loanLimit - amount - currentLoan < 0) {
        std::cout << "Exceeded loan limit." << std::endl;
        return false;
    } else {
        bankAcc.getTransfered(amount);
        currentLoan += amount;
        std::cout << "Transfer succeeded. Current loan: $" << currentLoan << std::endl;
        return true;
    }
}

void LoanAccount::monthlyUpdate() {
    if (balance >= currentLoan) {
        cout << balance << " " << currentLoan;
        balance -= currentLoan;
        currentLoan = 0;
        isFlagged = false;
    } else {
        if (isFrozen) return;
        currentLoan -= balance;
        balance = 0;
        currentLoan += currentLoan * latePaymentInterestRate;
        if (currentLoan >= 10000 && isFlagged) isFrozen = true;
        if (currentLoan >= 10000) isFlagged = true;
        else isFlagged = false;
    }
}