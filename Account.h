#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account {
protected:
    string name, username, password;

public:
    Account(string name, string user, string pass) : name(name), username(user), password(pass) {}

    virtual ~Account() {}
    
    bool verifyPassword(const string& pass) const { return password == pass; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getName() const { return name; }
    void setPassword(const string& newPass) { password = newPass; }

    virtual void displayInfo() = 0;
    virtual string getData() = 0;
};

#endif // ACCOUNT_H