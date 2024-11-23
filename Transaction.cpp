#include "Transaction.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Transaction::Transaction(uint64_t transId, const string &type, const string &username, int fromAcc, int toAcc, double amt, const string &date)
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
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << put_time(std::localtime(&in_time_t), "%Y%m%d%H%M%S");

    return std::stoull(oss.str());
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