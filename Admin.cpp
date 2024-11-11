#include "Admin.h"

using namespace std;

void Admin::freezeBankAccount(BankAccNode* bankAccHead) {
    BankAccNode* temp = bankAccHead;
    long id;
    cout << "Enter bank account id: ";
    cin >> id;

    while (temp) {
        if (temp->account->getAccountId() == id) {
            temp->account->freeze();
            cout << "Account frozen.\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Account not found.\n";
};

void Admin::unFreezeBankAccount(BankAccNode* bankAccHead) {
    BankAccNode* temp = bankAccHead;
    long id;
    cout << "Enter bank account id: ";
    cin >> id;

    while (temp) {
        if (temp->account->getAccountId() == id) {
            temp->account->unFreeze();
            cout << "Account unfrozen.\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Account not found.\n";
}

void Admin::viewBankAccountInfo(BankAccNode* bankAccHead) const {
    BankAccNode* temp = bankAccHead;
    cout << "Enter the bank account ID:";
    int accountId;
    cin >> accountId;

    while (temp) {
        if (temp->account->getAccountId() == accountId) {
            temp->account->displayInfo(); 
            return;
        }
        temp = temp->next;
    }

    cout << "Account not found.\n";
}

void Admin::deleteBankAccount(BankAccNode*& bankAccHead) {
    int id;
    cout << "Enter the id of the bank account to delete: ";
    cin >> id;

    if (!bankAccHead) {
        cout << "Bank account not found.\n";
        return;
    }

    BankAccNode* temp = bankAccHead;
    BankAccNode* prev = nullptr;

    while (temp) {
        if (temp->account->getAccountId() == id) {
            if (!prev) {
                bankAccHead = temp->next;
            } else {
                prev->next = temp->next;
            }

            delete temp;
            cout << "Bank account deleted.\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Bank account not found.\n";
}

void Admin::viewUserInfo(Node* head) const {
    Node* temp = head;
    cout << "Enter username: ";
    string username;
    cin >> username;

    while (temp) {
        User* targetUser = dynamic_cast<User*>(temp->account);
        if (targetUser && targetUser->getUsername() == username) {
            targetUser->displayInfo(); 
            return;
        }
        temp = temp->next;
    }

    cout << "User not found.\n";
};

void Admin::viewUserTransactionHistory(Node* head) const {
    Node* temp = head;
    cout << "Enter username: ";
    string username;
    cin >> username;

    while (temp) {
        User* targetUser = dynamic_cast<User*>(temp->account);
        if (targetUser && targetUser->getUsername() == username) {
            targetUser->loadTransactionHistory();
            targetUser->showTransactionHistory(); 
            return;
        }
        temp = temp->next;
    }

    cout << "User not found.\n";
}

void Admin::deleteUser(Node*& head) {
    string username;
    cout << "Enter username: ";
    cin >> username;

    if (!head) {
        cout << "User not found.\n";
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    while (temp) {
        User* targetUser = dynamic_cast<User*>(temp->account);
        if (targetUser && targetUser->getUsername() == username) {
            if (!prev) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            delete temp;
            cout << "User deleted.\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "User not found.\n";
}

void Admin::displayActions(Node* head, BankAccNode* bankAccHead) {
    int adminChoice;
    
    do {
        cout << "\nAdmin Menu:\n"
             << "1. Freeze bank account\n"
             << "2. Unfreeze bank account\n"
             << "3. View bank account info\n"
             << "4. Delete bank account\n"
             << "5. View user info\n"
             << "6. View user transaction history\n"
             << "7. Delete user\n"
             << "8. Log out\n"
             << "Enter your choice: ";
        cin >> adminChoice;

        string username;
        int accountId;
        Node* temp = head;
        User* targetUser = nullptr;
        BankAccount* targetBankAccount = nullptr;

        switch (adminChoice) {
            case 1:
                freezeBankAccount(bankAccHead);
                break;
                
            case 2:
                unFreezeBankAccount(bankAccHead);
                break;

            case 3:
                viewBankAccountInfo(bankAccHead);
                break;

            case 4:
                deleteBankAccount(bankAccHead);
                break;

            case 5:
                viewUserInfo(head);
                break;

            case 6:
                viewUserTransactionHistory(head);
                break;

            case 7:
                deleteUser(head);
                break;

            case 8:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (adminChoice != 8);
}