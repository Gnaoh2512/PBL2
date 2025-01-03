#include "User.h"

void User::deposit() {
    if (userBankAccounts.isEmpty()) {
        cout << name  << " has no bank account.\n";
        return;
    }
    
    char choice = 'y';
    int choice2 = 1;
    
    while (choice != 'n') {
        LinkedList<BankAccount>::Node* current = userBankAccounts.head;
        int index = 1;
        
        while (current) {
            cout << index << ". " << current->data->getAccountId() << " | " << current->data->getAccountType() << endl;
            current = current->next;
            index++;
        }
        
        cout << "Choose bank account to deposit into: ";
        cin >> choice2;
        
        if (choice2 < 1 || choice2 >= index) {
            cout << "Invalid choice. Please select a valid account.\n";
            continue;
        }
        
        current = userBankAccounts.head;
        for (int i = 1; i < choice2; i++) {
            current = current->next;
        }
        
        if (current->data->getIsFrozen()) {
            cout << "Bank account is frozen and cannot receive deposits.\n";
            continue;
        }
        
        current->data->displayInfo();
        
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Deposit amount must be greater than zero.\n";
            continue;
        }

        current->data->deposit(amount);
        recordTransaction("deposit", amount, 0, *current->data);
        
        cout << "Do you want to make another deposit? (y/n): ";
        cin >> choice;
    }
}

void User::withdraw() {
    if (userBankAccounts.isEmpty()) {
        cout << name  << " has no bank account.\n";
        return;
    }

    char choice = 'y';
    int choice2 = 1;

    while (choice != 'n') {
        LinkedList<BankAccount>::Node* current = userBankAccounts.head;
        int index = 1;
        
        while (current) {
            cout << index << ". " << current->data->getAccountId() << " | " << current->data->getAccountType() << endl;
            current = current->next;
            index++;
        }
        
        cout << "Choose bank account to withdraw from: ";
        cin >> choice2;

        if (choice2 < 1 || choice2 >= index) {
            cout << "Invalid choice. Please select a valid account.\n";
            continue;
        }

        current = userBankAccounts.head;
        for (int i = 1; i < choice2; i++) {
            current = current->next;
        }

        if (current->data->getIsFrozen()) {
            cout << "Bank account is frozen and cannot be accessed to withdraw.\n";
            continue;
        }

        current->data->displayInfo();
        
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Withdrawal amount must be greater than zero.\n";
            continue;
        }

        if (current->data->withdraw(amount)) {
            recordTransaction("withdraw", amount, 0, *current->data);
        } else {
            cout << "Insufficient balance or invalid amount.\n";
        }

        cout << "Do you want to make another withdrawal? (y/n): ";
        cin >> choice;
    }
}

void User::transfer(LinkedList<BankAccount> &bankAccs) {
    if (userBankAccounts.isEmpty()) {
        cout << name  << " has no bank account.\n";
        return;
    }

    char choice = 'y';
    int choice2 = 1;

    while (choice != 'n') {
        LinkedList<BankAccount>::Node* temp1 = userBankAccounts.head;
        int index = 1;
        
        while (temp1) {
            cout << index << ". " << temp1->data->getAccountId() << " | " << temp1->data->getAccountType() << endl;
            temp1 = temp1->next;
            index++;
        }
        
        cout << "Choose bank account to be begin transfer: ";
        cin >> choice2;

        if (choice2 < 1 || choice2 >= index) {
            cout << "Invalid choice. Please select a valid account.\n";
            continue;
        }

        temp1 = userBankAccounts.head;

        for (int i = 1; i < choice2; i++) {
            temp1 = temp1->next;
        }

        if (temp1->data->getIsFrozen()) {
            cout << "Bank account is frozen and cannot be accessed to begin transfer.\n";
            continue;
        }

        temp1->data->displayInfo();
        
        int toAccountId;
        double amount;
        LinkedList<BankAccount>::Node* temp2 = bankAccs.head;

        cout << "Enter account id to transfer: ";
        cin >> toAccountId;

        while (temp2) {
            if (temp2->data->getAccountId() == toAccountId) {
                break;
            }
            temp2 = temp2->next;
        }

        if (!temp2) {
            cout << "Account not found.\n";
            continue;
        }

        cout << "Enter amount to transfer: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Transfer amount must be greater than zero.\n";
            continue;
        }

        if (temp1->data->transfer(amount, *temp2->data)) {
            recordTransaction("transfer", amount, temp1->data->getAccountId(), *temp2->data);
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
    if (transactionHistory.isEmpty()) {
        cout << "No previous transaction history found for " << name << endl;
        return;
    }

    cout << "Transaction History for " << name << ":\n";
    LinkedList<Transaction>::Node* current = transactionHistory.head;
    while (current != nullptr) {
        current->data->displayInfo();
        current = current->next;
    }
}

void User::saveTransactionHistory() {
    ofstream outFile("transaction.txt", ios_base::app);
    if (outFile.is_open()) {
        LinkedList<Transaction>::Node* current = transactionHistory.tail;
        outFile << current->data->getData();
        outFile.close();
    } else {
        cout << "Error saving transaction history for " << name << endl;
    }
}

void User::loadTransactionHistory() {
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

                transactionHistory.add(new Transaction(transactionId, transactionType, username, fromAccountId, toAccountId, amount, date));
            }
        }

        inFile.close();
    } else {
        cout << "Error opening transaction file.\n";
    }
}

void User::recordTransaction(const string& transactionType, double amount, long toAccId, BankAccount& bankAccount) {
    TimeUtils timeUtils;
    transactionHistory.add(new Transaction(Transaction::generateUniqueTransactionId(), transactionType, username, bankAccount.getAccountId(), toAccId, amount, timeUtils.getCurrentDate(true)));

    saveTransactionHistory();
}

void User::createBankAccount(SortedLinkedList<int>& usedAccountIds, LinkedList<BankAccount> &bankAccs) {
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
            cout << "Invalid option. Exiting...\n";
            return;
    }

    cout << "Do you want to enter an account id manually? (y/n): ";
    cin >> choice;
    
    if (choice == 'y') {
        do {
            cout << "Enter an 8-digit account id: ";
            cin >> accountId;
            if (to_string(accountId).length() != 8 || usedAccountIds.search(accountId)) {
                cout << "Invalid or taken account id. Please enter a unique 8-digit id.\n";
            }
        } while (to_string(accountId).length() != 8 || usedAccountIds.search(accountId));
    } else {
        accountId = BankAccount::generateAccountId(usedAccountIds);
        cout << "Generated account id: " << accountId << endl;
    }

    newAccount->setAccountId(accountId);
    newAccount->setUsername(User::username);
    usedAccountIds.add(accountId);

    userBankAccounts.add(newAccount);
    bankAccs.add(newAccount);
    
    cout << "Account created successfully!\n";
}

void User::loadBankAccount(LinkedList<BankAccount> &bankAccs) {
    LinkedList<BankAccount>::Node* current = bankAccs.head;

    while (current) {
        if (current->data->getUsername() == username) {
            userBankAccounts.add(current->data);
        }
        current = current->next;
    }
}

void User::showBankAccount() {
    if (userBankAccounts.isEmpty()) {
        cout << name  << " has no bank account.\n";
        return;
    }
    cout << name << "'s bank accounts:\n";
    displayBankAccountsInfo();
}

void User::displayBankAccountsInfo() {
    LinkedList<BankAccount>::Node* current = userBankAccounts.head;
    while (current) {
        current->data->displayInfo();
        current = current->next;
    }
}

void User::displayActions(SortedLinkedList<int>& usedAccountIds, LinkedList<BankAccount> &bankAccs) {
    loadTransactionHistory();
    loadBankAccount(bankAccs);
    int userChoice;

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        cout << "User Menu:\n"
             << "1. Deposit\n"
             << "2. Withdraw\n"
             << "3. Transfer\n"
             << "4. View transaction history\n"
             << "5. Change password\n"
             << "6. Create bank account\n"
             << "7. Show bank account\n"
             << "8. Log out\n"
             << "Enter your choice: ";

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
                transfer(bankAccs);
                break;
            case 4:
                showTransactionHistory();
                break;
            case 5:
                changePassword();
                break;
            case 6:
                createBankAccount(usedAccountIds, bankAccs);
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
        if (userChoice != 8) {
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
        }
    } while (userChoice != 8);
    userBankAccounts.clear();
    transactionHistory.clear();
}