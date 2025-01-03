#include "SavingAccount.h"

SavingAccount::SavingAccount(int accountId, std::string username, std::string createdDate, double balance, bool isFlagged, bool isFrozen)
    : BankAccount(accountId, username, createdDate, balance, isFlagged, isFrozen) {}

void SavingAccount::displayInfo() {
    std::cout << "Saving Account - Account Id: " << accountId 
              << ", Created Date: " << createdDate
              << ", Balance: " << balance
              << ", Minimum Balance: " << minimumBalance
              << ", Interest Rate: " << interestRate * 100 << "%"
              << ", Is Flagged: " << (isFlagged ? "Yes" : "No")
              << ", Is Frozen: " << (isFrozen ? "Yes" : "No") << std::endl;
}

std::string SavingAccount::getAccountType() {
    return "saving";
}

std::string SavingAccount::getData() {
    std::ostringstream oss;
    oss << accountId << "|"
        << username << "|"
        << "saving|"
        << createdDate << "|"
        << balance << "|"
        << (isFlagged ? "1" : "0") << "|"
        << (isFrozen ? "1" : "0") << std::endl;
    return oss.str();
}

void SavingAccount::monthlyUpdate() {
    if (balance >= minimumBalance) {
        balance += balance * interestRate;
    }
}

bool SavingAccount::withdraw(double amount) {
  	if (balance - amount < minimumBalance) {
    	cout << "Insufficient balance to withdraw, considering mininmum balance.\n";
    	return false;
  	} else {
    	if (amount/balance > 0.8) {
    	  	if (isFlagged) isFrozen = true;
    	  	isFlagged = true;
    	}
    	balance -= amount;
    	std::cout << "Withdraw succeeded. Current balance: $" << balance << std::endl;
    	return true;
  	}
}

bool SavingAccount::transfer(double amount, BankAccount& bankAcc) {
  	if (balance - amount < minimumBalance) {
    	cout << "Insufficient balance to transfer, considering mininmum balance.\n";
    	return false;
  	} else {
    	if (amount/balance > 0.8) {
    	  	if (isFlagged) isFrozen = true;
    	  	isFlagged = true;
    	}
        bankAcc.getTransfered(amount);
    	balance -= amount;
    	std::cout << "Transfer succeeded. Current balance: $" << balance << std::endl;
    	return true;
  	}
}