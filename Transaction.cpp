#include "Transaction.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Transaction::Transaction(int transId, const string &type, const string &username, int fromAcc, int toAcc, double amt, const string &date)
    : transactionId(transId), transactionType(type), username(username), fromAccountId(fromAcc), toAccountId(toAcc), amount(amt), transactionDate(date){}

void Transaction::displayInfo() const {
    cout << "  Transaction ID: " << transactionId << endl;
    cout << "Transaction Date: " << transactionDate << endl;
    cout << "Transaction Type: " << transactionType << endl;
    cout << " From Account ID: " << fromAccountId << endl;
    cout << "   To Account ID: " << toAccountId << endl;
    cout << "          Amount: $" << amount << endl;
}

uint64_t Transaction::generateUniqueTransactionId() {
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(now).count());
}

std::string Transaction::getData() const {
    std::ostringstream oss;
    oss << transactionId << "|"
        << transactionType << "|"
        << username << "|"
        << fromAccountId << "|"
        << toAccountId << "|"
        << amount << "|"
        << transactionDate << endl;
    return oss.str();
}