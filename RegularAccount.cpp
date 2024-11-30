#include "RegularAccount.h"

RegularAccount::RegularAccount(int accountId, std::string username, std::string createdDate, double balance, bool isFlagged, bool isFrozen)
    : BankAccount(accountId, username, createdDate, balance, isFlagged, isFrozen) {}

void RegularAccount::displayInfo() {
    std::cout << "Regular Account - Account Id: " << accountId 
              << ", Created Date: " << createdDate
              << ", Balance: " << balance
              << ", Monthly Fee: " << monthlyFee
              << ", Transaction Fee: " << transactionFee
              << ", Is Flagged: " << (isFlagged ? "Yes" : "No")
              << ", Is Frozen: " << (isFrozen ? "Yes" : "No") << std::endl; 
}

std::string RegularAccount::getAccountType() {
    return "regular";
}

std::string RegularAccount::getData() {
    std::ostringstream oss;
    oss << accountId << "|"
        << username << "|"
        << "regular|"
        << createdDate << "|"
        << balance << "|"
        << (isFlagged ? "1" : "0") << "|"
        << (isFrozen ? "1" : "0") << std::endl;
    return oss.str();
}

bool RegularAccount::withdraw(double amount) {
    if (balance - amount - transactionFee < 0) {
        std::cout << "Insufficient balance to withdraw, considering transaction fee." << std::endl;
        return false;
    } else {
        balance -= (amount + transactionFee);
        std::cout << "Withdraw succeeded. Current balance: $" << balance << std::endl;
        return true;
    }
}

bool RegularAccount::transfer(double amount, BankAccount& bankAcc) {
    if (balance - amount - transactionFee < 0) {
        std::cout << "Insufficient balance to transfer, considering transaction fee." << std::endl;
        return false;
    } else {
        bankAcc.getTransfered(amount);
        balance -= (amount + transactionFee);
        std::cout << "Transfer succeeded. Current balance: $" << balance << std::endl;
        return true;
    }
}

void RegularAccount::monthlyUpdate() {
    if (balance >= monthlyFee) {
        balance -= monthlyFee;
    } else {
        if (isFlagged) isFrozen = true;
        isFlagged = true;
    }
}