#include "BankAccount.h"
#include "TimeUtils.h"

using namespace std;

int BankAccount::generateAccountId(SortedLinkedList<int>& usedAccountIds) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(10000000, 99999999);
    int generatedAccountId;
    
    do {
        generatedAccountId = dist(gen);
    } while (usedAccountIds.search(generatedAccountId));

    return generatedAccountId;
}

string BankAccount::getCurrentDate() {
    TimeUtils timeUtils;
    return timeUtils.getCurrentDate(false);
}