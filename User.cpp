#include "User.h"
#include "TimeUtils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

void User::deposit() {
    displayBankAccountsInfo();
    
    char choice = 'y';
    int choice2 = 1;
    
    while (choice != 'n') {
        BankAccNode* temp = bankAccountHead;
        int index = 1;
        
        while (temp) {
            cout << index << ". " << temp->account->getAccountId() << "    " << temp->account->getAccountType() << endl;
            temp = temp->next;
            index++;
        }
        
        cout << "Choose bank account to deposit into:\n";
        cin >> choice2;
        
        if (choice2 < 1 || choice2 >= index) {
            cout << "Invalid choice. Please select a valid account.\n";
            continue;
        }
        
        temp = bankAccountHead;
        for (int i = 1; i < choice2; i++) {
            temp = temp->next;
        }
        
        if (temp->account->getIsFrozen()) {
            cout << "Bank account is frozen and cannot receive deposits.\n";
            continue;
        }
        
        temp->account->displayInfo();
        
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Deposit amount must be greater than zero.\n";
            continue;;
        }

        temp->account->deposit(amount);
        recordTransaction("deposit", amount, 0, *temp->account);
        
        cout << "Do you want to make another deposit? (y/n): ";
        cin >> choice;
    }
}

void User::withdraw() {
    displayBankAccountsInfo();

    char choice = 'y';
    int choice2 = 1;

    while (choice != 'n') {
        BankAccNode* temp = bankAccountHead;
        int index = 1;
        
        while (temp) {
            cout << index << ". " << temp->account->getAccountId() << "    " << temp->account->getAccountType() << endl;
            temp = temp->next;
            index++;
        }
        
        cout << "Choose bank account to withdraw from:\n";
        cin >> choice2;

        if (choice2 < 1 || choice2 >= index) {
            cout << "Invalid choice. Please select a valid account.\n";
            continue;
        }

        temp = bankAccountHead;
        for (int i = 1; i < choice2; i++) {
            temp = temp->next;
        }

        if (temp->account->getIsFrozen()) {
            cout << "Bank account is frozen and cannot be accessed for withdrawal.\n";
            continue;
        }

        temp->account->displayInfo();
        
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Withdrawal amount must be greater than zero.\n";
            continue;
        }

        if (temp->account->withdraw(amount)) {
            recordTransaction("withdraw", amount, 0, *temp->account);
        } else {
            cout << "Insufficient balance or invalid amount.\n";
        }

        cout << "Do you want to make another withdrawal? (y/n): ";
        cin >> choice;
    }
}

void User::transfer(BankAccNode* bankAccHead) {
    displayBankAccountsInfo();

    char choice = 'y';
    int choice2 = 1;

    while (choice != 'n') {
        BankAccNode* temp = bankAccountHead;
        int index = 1;
        
        while (temp) {
            cout << index << ". " << temp->account->getAccountId() << "    " << temp->account->getAccountType() << endl;
            temp = temp->next;
            index++;
        }
        
        cout << "Choose bank account to be begin transfer:\n";
        cin >> choice2;

        if (choice2 < 1 || choice2 >= index) {
            cout << "Invalid choice. Please select a valid account.\n";
            continue;
        }

        temp = bankAccountHead;
        for (int i = 1; i < choice2; i++) {
            temp = temp->next;
        }

        if (temp->account->getIsFrozen()) {
            cout << "Bank account is frozen and cannot be accessed to transfer.\n";
            continue;
        }

        temp->account->displayInfo();
        
        int toAccountId;
        double amount;
        BankAccNode* temp2 = bankAccHead;

        cout << "Enter account id to transfer: ";
        cin >> toAccountId;

        while (temp2) {
            if (temp2->account->getAccountId() == toAccountId) {
                break;
            }
            temp2 = temp2->next;
        }

        if (!temp2) {
            cout << "Account not found.\n";
            continue;
        }

        if (amount <= 0) {
            cout << "Transfer amount must be greater than zero.\n";
            continue;
        }

        cout << "Enter amount to transfer: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Transfer amount must be greater than zero.\n";
            continue;
        }

        if (temp->account->transfer(amount, *temp2->account)) {
            recordTransaction("transfer", amount, temp2->account->getAccountId(), *temp->account);
        } else {
            cout << "Insufficient balance or invalid amount.\n";
        }

        cout << "Do you want to make another transfer? (y/n): ";
        cin >> choice;
    }
}

void User::changePassword() {
    string newPassword, confirmPassword;

    while (true) {
        cout << "Enter new password: ";
        cin >> newPassword;

        if (newPassword.empty()) {
            cout << "Password cannot be empty.\n";
            continue;
        }

        if (newPassword == password) {
            cout << "Password cannot be the same as the old one.\n";
            continue;
        }

        if (newPassword.length() < 6) {
            cout << "Password must be at least 6 characters long.\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "Confirm new password: ";
        cin >> confirmPassword;

        if (newPassword != confirmPassword) {
            cout << "Passwords do not match. Please try again.\n";
            continue;
        }

        break;
    }

    password = newPassword;
    cout << "Password updated successfully.\n";
}

void User::showTransactionHistory() {
    if (transactionHistoryHead == nullptr) {
        cout << "No previous transaction history found for " << name << endl;
        return;
    }

    cout << "Transaction History for " << name << ":\n";

    TransactionNode* current = transactionHistoryHead;
    while (current != nullptr) {
        current->transaction->displayInfo();
        current = current->next;
    }
}

void User::saveTransactionHistory() {
    ofstream outFile("transaction.txt", ios_base::app);
    if (outFile.is_open()) {
        TransactionNode* current = transactionHistoryHead;
        outFile << current->transaction->getData();
        outFile.close();
    } else {
        cout << "Error saving transaction history for " << name << endl;
    }
}

void User::loadTransactionHistory() {
    if (transactionHistoryHead != nullptr) return;

    ifstream inFile("transaction.txt");

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            uint64_t transactionId;
            long fromAccountId, toAccountId;
            double amount;
            string transactionType, date, username;

            ss >> transactionId;
            ss.ignore();
            getline(ss, transactionType, '|');
            getline(ss, username, '|');
            if (User::username == username) {
                ss >> fromAccountId;
                ss.ignore();
                ss >> toAccountId;
                ss.ignore();
                ss >> amount;
                ss.ignore();
                getline(ss, date);

                Transaction* newTransaction = new Transaction(transactionId, transactionType, username, fromAccountId, toAccountId, amount, date);
                TransactionNode* newNode = new TransactionNode(newTransaction, transactionHistoryHead);
                transactionHistoryHead = newNode;
            }
        }

        inFile.close();
    } else {
        cout << "Error opening transaction file." << endl;
    }
}

void User::recordTransaction(const string& transactionType, double amount, long toAccId, BankAccount& bankAccount) {
    TimeUtils timeUtils;

    Transaction* newTransaction = new Transaction(Transaction::generateUniqueTransactionId(), transactionType, username, bankAccount.getAccountId(), toAccId, amount, timeUtils.getCurrentDate(true));
    TransactionNode* newNode = new TransactionNode(newTransaction);

    newNode->next = transactionHistoryHead;
    transactionHistoryHead = newNode;

    saveTransactionHistory();
}

void User::createBankAccount(SortedLinkedList<int>& usedAccountIds, BankAccNode* bankAccHead, BankAccNode* bankAccTail) {
    int accountId;
    char choice;
    cout << "Choose account type (1: Savings, 2: Credit, 3: Regular): ";
    int accountTypeChoice;
    cin >> accountTypeChoice;

    BankAccount* newAccount;
    switch (accountTypeChoice) {
        case 1:
            newAccount = new SavingAccount();
            break;
        case 2:
            newAccount = new LoanAccount();
            break;
        case 3:
            newAccount = new RegularAccount();
            break;
        default:
            cout << "Invalid option. Exiting..." << endl;
            return;
    }

    cout << "Do you want to enter an account id manually? (y/n): ";
    cin >> choice;
    
    if (choice == 'y') {
        do {
            cout << "Enter an 8-digit account id: ";
            cin >> accountId;
            if (to_string(accountId).length() != 8 || usedAccountIds.search(accountId)) {
                cout << "Invalid or taken account id. Please enter a unique 8-digit id." << endl;
            }
        } while (to_string(accountId).length() != 8 || usedAccountIds.search(accountId));
    } else {
        accountId = BankAccount::generateAccountId(usedAccountIds);
        cout << "Generated account id: " << accountId << endl;
    }

    newAccount->setAccountId(accountId);
    newAccount->setUsername(User::username);
    usedAccountIds.add(accountId);

    BankAccNode* newBankAccountNode = new BankAccNode(newAccount, nullptr);

    if (bankAccHead == nullptr) {
        bankAccHead = newBankAccountNode;
        bankAccTail = newBankAccountNode;
    } else {
        bankAccTail->next = newBankAccountNode;
        bankAccTail = newBankAccountNode;
    }

    BankAccNode* newBankAccNode = new BankAccNode(newAccount);
    newBankAccNode->next = bankAccountHead;
    bankAccountHead = newBankAccNode;
    
    cout << "Account created successfully!" << endl;
}

void User::loadBankAccount(BankAccNode* bankAccHead) {
    if (bankAccountHead != nullptr) return;

    BankAccNode* temp = bankAccHead;

    while (temp) {
        if (temp->account->getUsername() == username) {
            BankAccNode* newBankAccNode = new BankAccNode(temp->account);
            
            newBankAccNode->next = bankAccountHead;
            bankAccountHead = newBankAccNode;
        }

        temp = temp->next;
    }
}

void User::showBankAccount() {
    if (bankAccountHead == nullptr) {
        cout << name  << "has no bank account." << endl;
        return;
    }

    cout << name << "'s bank accounts:\n";

    BankAccNode* temp = bankAccountHead;
    while (temp != nullptr) {
        temp->account->displayInfo();
        temp = temp->next;
    }
}

void User::displayBankAccountsInfo() {
    BankAccNode* temp = bankAccountHead;
    while (temp) {
        temp->account->displayInfo();
        temp = temp->next;
    }
}

void User::displayActions(SortedLinkedList<int>& usedAccountIds, BankAccNode* bankAccHead, BankAccNode* bankAccTail) {
    loadTransactionHistory();
    loadBankAccount(bankAccHead);
    int userChoice;

    do {
        cout << "\nUser Menu:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer\n";
        cout << "4. View transaction history\n";
        cout << "5. Change password\n";
        cout << "6. Create bank account\n";
        cout << "7. Show bank account\n";
        cout << "8. Log out\n";
        cout << "Enter your choice: ";

        cin >> userChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (userChoice) {
            case 1:
                deposit();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                transfer(bankAccHead);
                break;
            case 4:
                showTransactionHistory();
                break;
            case 5:
                changePassword();
                break;
            case 6:
                createBankAccount(usedAccountIds, bankAccHead, bankAccTail);
                break;
            case 7:
                showBankAccount();
                break;
            case 8:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (userChoice != 8);
}