#include "Admin.h"

using namespace std;

void Admin::freezeBankAccount(LinkedList<BankAccount>& bankAccs) {
    LinkedList<BankAccount>::Node* current = bankAccs.head;
    long id;

    cout << "Enter bank account id: ";
    cin >> id;

    while (current) {
        if (current->data->getAccountId() == id) {
            current->data->freeze();
            cout << "Account frozen.\n";
            return;
        }
        current = current->next;
    }

    cout << "Account not found.\n";
};

void Admin::unFreezeBankAccount(LinkedList<BankAccount>& bankAccs) {
    LinkedList<BankAccount>::Node* current = bankAccs.head;
    long id;
    
    cout << "Enter bank account id: ";
    cin >> id;

    while (current) {
        if (current->data->getAccountId() == id) {
            current->data->unFreeze();
            cout << "Account unFrozen.\n";
            return;
        }
        current = current->next;
    }

    cout << "Account not found.\n";
}

void Admin::viewBankAccountInfo(LinkedList<BankAccount>& bankAccs) const {
    LinkedList<BankAccount>::Node* current = bankAccs.head;
    cout << "Enter the bank account ID:";
    int accountId;
    cin >> accountId;

    while (current) {
        if (current->data->getAccountId() == accountId) {
            current->data->displayInfo(); 
            return;
        }
        current = current->next;
    }

    cout << "Account not found.\n";
}

void Admin::deleteBankAccount(LinkedList<BankAccount>& bankAccs) {
    int id;
    cout << "Enter the id of the bank account to delete: ";
    cin >> id;

    if (bankAccs.isEmpty()) {
        cout << "Bank account not found.\n";
        return;
    }

    LinkedList<BankAccount>::Node* current = bankAccs.head;
    while (current) {
        if (current->data->getAccountId() == id) break;
        current = current->next;
    }

    if (!current) {
        cout << "Bank account not found.\n";
        return;
    }

    bankAccs.remove(current->data);
}

void Admin::viewUserInfo(LinkedList<Account>& accs) const {
    LinkedList<Account>::Node* current = accs.head;
    string username;
    cout << "Enter username: ";
    cin >> username;

    while (current) {
        User* targetUser = dynamic_cast<User*>(current->data);
        if (targetUser && targetUser->getUsername() == username) {
            targetUser->displayInfo(); 
            return;
        }
        current = current->next;
    }
    cout << "User not found.\n";
};

void Admin::viewUserTransactionHistory(LinkedList<Account>& accs) const {
    LinkedList<Account>::Node* current = accs.head;
    string username;
    cout << "Enter username: ";
    cin >> username;

    while (current) {
        User* targetUser = dynamic_cast<User*>(current->data);
        if (targetUser && targetUser->getUsername() == username) {
            targetUser->loadTransactionHistory();
            targetUser->showTransactionHistory();
            return;
        }
        current = current->next;
    }
    cout << "User not found.\n";
}

void Admin::deleteUser(LinkedList<Account>& accs) {
    string username;
    cout << "Enter username: ";
    cin >> username;

    if (accs.isEmpty()) {
        cout << "User not found.\n";
        return;
    }

    LinkedList<Account>::Node* current = accs.head;
    while (current) {
        if (current->data->getUsername() == username) break;
        current = current->next;
    }

    if (!current) {
        cout << "Bank account not found.\n";
        return;
    }

    accs.remove(current->data);
}

void Admin::displayActions(LinkedList<Account>& accs, LinkedList<BankAccount>& bankAccs) {
    int choice;
    
    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        cout << "Admin Menu:\n"
             << "1. Freeze bank account\n"
             << "2. Unfreeze bank account\n"
             << "3. View bank account info\n"
             << "4. Delete bank account\n"
             << "5. View user info\n"
             << "6. View user transaction history\n"
             << "7. Delete user\n"
             << "8. Log out\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                freezeBankAccount(bankAccs);
                break;
                
            case 2:
                unFreezeBankAccount(bankAccs);
                break;

            case 3:
                viewBankAccountInfo(bankAccs);
                break;

            case 4:
                deleteBankAccount(bankAccs);
                break;

            case 5:
                viewUserInfo(accs);
                break;

            case 6:
                viewUserTransactionHistory(accs);
                break;

            case 7:
                deleteUser(accs);
                break;

            case 8:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
        if (choice != 8) {
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 8);
}