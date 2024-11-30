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
#include "LinkedList.h"
#include "BankAccount.h"
#include "TimeUtils.h"

using namespace std;

LinkedList<Account> accs;
LinkedList<BankAccount> bankAccs;
SortedLinkedList<int> usedAccountIds;
SortedLinkedList<string> usedUsernames;
Account* loggedInAccount = nullptr;

void readDataFromFile() {
    ifstream inFileAccounts("accounts.txt");
    TimeUtils timeUtils;
    bool isNewMonth = timeUtils.isNewMonth();
    if (isNewMonth) cout << "A new month has passed. Updated bank accounts data->\n";

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
                accs.add(new User(name, username, password));
            } else if (accountType == "Admin") {
                accs.add(new Admin(name, username, password));
            }
            usedUsernames.add(username);
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

            if (accountType == "loan") {
                double currentLoan;
                getline(ss, temp, '|');
                currentLoan = stod(temp);
                bankAccs.add(new LoanAccount(accountId, username, createdDate, balance, isFlagged, isFrozen, currentLoan));
            } else if (accountType == "saving") {
                bankAccs.add(new SavingAccount(accountId, username, createdDate, balance, isFlagged, isFrozen));
            } else if (accountType == "regular") {
                bankAccs.add(new RegularAccount(accountId, username, createdDate, balance, isFlagged, isFrozen));
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

    LinkedList<Account>::Node* current = accs.head;

    while (current) {
        if (current->data->getUsername() == username) break;
        current = current->next;
    }

    if (!current) return nullptr;

    Account* currentAccount = current->data;
    if (currentAccount->verifyPassword(password)) {
        return currentAccount;
    } else return nullptr;
}

void signUp() {
    string name, username, password;

    cout << "Enter Name: ";
    cin >> name;

    while (true) {
        cout << "Enter Username: ";
        cin >> username;
        if (username.empty()) {
            cout << "Username cannot be empty.\n";
            continue;
        }
        if (username.length() < 6) {
            cout << "Username must be at least 6 characters long.\n";
            continue;
        }
        if (usedUsernames.search(username)) {
            cout << "Username is already taken. Please choose a different one.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter password: ";
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
        
    usedUsernames.add(name);
    accs.add(new User(name, username, password));
    cout << "Password updated successfully.\n";
}

void saveDataToFile() {
    ofstream outFileAccounts("accounts.txt");

    LinkedList<Account>::Node* temp1 = accs.head;
    if (outFileAccounts.is_open()) {
        while (temp1) {
            outFileAccounts << temp1->data->getData();
            temp1 = temp1->next;
        }
        outFileAccounts.close();
    } else {
        cerr << "Error opening accounts file" << endl;
    }

    ofstream outFileBankAccounts("bankAccounts.txt");

    LinkedList<BankAccount>::Node* temp2 = bankAccs.head;
    if (outFileBankAccounts.is_open()) {
        while (temp2) {
            outFileBankAccounts << temp2->data->getData();
            temp2 = temp2->next;
        }
        outFileBankAccounts.close();
    } else {
        cerr << "Error opening bank accounts file" << endl;
    }
}

void cleanupMemory() {
    accs.clear();
    bankAccs.clear();
}

int main() {
    readDataFromFile();
    int choice;

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        cout << "1. Sign Up\n"
             << "2. Log In\n"
             << "3. Exit\n"
             << "Enter your choice: ";
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
                        static_cast<Admin*>(account)->displayActions(accs, bankAccs);
                    } else {
                        static_cast<User*>(account)->displayActions(usedAccountIds, bankAccs);
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
        cout << "Press any key to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 3);

    cleanupMemory();
    return 0;
}