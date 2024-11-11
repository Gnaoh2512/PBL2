#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "Account.h"
#include "User.h"
#include "Admin.h"
#include "Transaction.h"
#include "SortedLinkedList.h"
#include "BankAccount.h"
#include "TimeUtils.h"

using namespace std;

Node* accHead = nullptr;
Node* accTail = nullptr;
BankAccNode* bankAccHead = nullptr;
BankAccNode* bankAccTail = nullptr;
SortedLinkedList<int> usedAccountIds;
SortedLinkedList<string> usedUsernames;
Account* loggedInAccount = nullptr;

void addAccountToList(Account* account) {
    Node* newNode = new Node(account, nullptr);
    
    if (accHead == nullptr) {
        accHead = newNode;
        accTail = newNode;
    } else {
        accTail->next = newNode;
        accTail = newNode;
    }
}

void addBankAccountToList(BankAccount* bankAccount) {
    BankAccNode* newNode = new BankAccNode(bankAccount, nullptr);

    if (bankAccHead == nullptr) {
        bankAccHead = newNode;
        bankAccTail = newNode;
    } else {
        bankAccTail->next = newNode;
        bankAccTail = newNode;
    }
};

void readDataFromFile() {
    ifstream inFileAccounts("accounts.txt");
    TimeUtils timeUtils;
    bool isNewMonth = timeUtils.isNewMonth();
    if (isNewMonth) cout << "A new month has passed. Updated bank accounts data.\n";

    if (inFileAccounts.is_open()) {
        string line;
        while (getline(inFileAccounts, line)) {
            istringstream ss(line);
            string accountType, name, username, password;
            int flagged;

            getline(ss, accountType, '|');
            getline(ss, name, '|');
            getline(ss, username, '|');
            getline(ss, password, '|');

            if (accountType == "User") {
                ss >> flagged;
                usedUsernames.add(username);
                User* newUser = new User(name, username, password);
                addAccountToList(newUser);
            } else if (accountType == "Admin") {
                Admin* newAdmin = new Admin(name, username, password);
                addAccountToList(newAdmin);
            }
        }
        inFileAccounts.close();
    } else {
        cerr << "Error opening accounts file" << endl;
    }

    ifstream inFileBankAccounts("bankAccounts.txt");
    if (inFileBankAccounts.is_open()) {
        string line;
        while (getline(inFileBankAccounts, line)) {
            istringstream ss(line);
            int accountId;
            string username, accountType, createdDate;
            double balance;
            int isFlagged, isFrozen;

            ss >> accountId;
            usedAccountIds.add(accountId);
            ss.ignore();
            getline(ss, username, '|');
            getline(ss, accountType, '|');
            getline(ss, createdDate, '|');
            
            std::string temp;
            getline(ss, temp, '|');
            balance = stod(temp);

            getline(ss, temp, '|');
            isFlagged = stoi(temp);

            getline(ss, temp, '|');
            isFrozen = stoi(temp);

            BankAccount* bankAccount = nullptr;
            if (accountType == "loan") {
                double currentLoan;
                getline(ss, temp, '|');
                currentLoan = stod(temp);
                bankAccount = new LoanAccount(accountId, username, createdDate, balance, isFlagged, isFrozen, currentLoan);
            } else if (accountType == "saving") {
                bankAccount = new SavingAccount(accountId, username, createdDate, balance, isFlagged, isFrozen);
            } else if (accountType == "regular") {
                bankAccount = new RegularAccount(accountId, username, createdDate, balance, isFlagged, isFrozen);
            }

            if (bankAccount) {
                if (isNewMonth) bankAccount->monthlyUpdate();
                addBankAccountToList(bankAccount);
            }
        }
        inFileBankAccounts.close();
    } else {
        cerr << "Error opening bank accounts file" << endl;
    }
}

Account* login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Node* temp = accHead;
    while (temp) {
        if (temp->account->getUsername() == username && temp->account->verifyPassword(password)) {
            return temp->account;
        }
        temp = temp->next;
    }
    return nullptr;
}

void signUp() {
    string name, username, password, confirmPassword;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    do {
        cout << "Enter username: ";
        cin >> username;
        if (usedUsernames.search(username)) {
            cout << "Username is already taken. Please choose a different one.\n";
        }
    } while (usedUsernames.search(username));

    while (true) {
        cout << "Enter new password: ";
        cin >> password;

        if (password.empty()) {
            cout << "Password cannot be empty.\n";
            continue;
        }

        if (password.length() < 6) {
            cout << "Password must be at least 6 characters long.\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "Confirm new password: ";
        cin >> confirmPassword;

        if (password != confirmPassword) {
            cout << "Passwords do not match. Please try again.\n";
            continue;
        }

        break;
    }

    User* newUser = new User(name, username, password);
    addAccountToList(newUser);
    cout << "Password updated successfully.\n";
}

void saveDataToFile() {
    ofstream outFileAccounts("accounts.txt");
    Node* temp = accHead;

    if (outFileAccounts.is_open()) {
        while (temp) {
            outFileAccounts << temp->account->getData();
            temp = temp->next;
        }
        outFileAccounts.close();
    } else {
        cerr << "Error opening accounts file" << endl;
    }

    ofstream outFileBankAccounts("bankAccounts.txt");
    BankAccNode* bankTemp = bankAccHead;

    if (outFileBankAccounts.is_open()) {
        while (bankTemp) {
            outFileBankAccounts << bankTemp->account->getData();
            bankTemp = bankTemp->next;
        }
        outFileBankAccounts.close();
    } else {
        cerr << "Error opening bank accounts file" << endl;
    }
}

void cleanupMemory() {
    Node* temp1;
    while (accHead) {
        temp1 = accHead;
        accHead = accHead->next;
        delete temp1->account;
        delete temp1;
    }

    BankAccNode* temp2;
    while (bankAccHead) {
        temp2 = bankAccHead;
        bankAccHead = bankAccHead->next;
        delete temp2->account;
        delete temp2;
    }
}

int main() {
    readDataFromFile();
    int choice;

    do {
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2: {
                Account* account = login();
                if (account) {
                    loggedInAccount = account;
                    if (dynamic_cast<Admin*>(account)) {
                        static_cast<Admin*>(account)->displayActions(accHead, bankAccHead);
                    } else {
                        static_cast<User*>(account)->displayActions(usedAccountIds, bankAccHead, bankAccTail);
                    }
                } else {
                    cout << "Login failed. Please check your credentials.\n";
                }
                break;
            }
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
        saveDataToFile();
    } while (choice != 3);

    cleanupMemory();
    return 0;
}