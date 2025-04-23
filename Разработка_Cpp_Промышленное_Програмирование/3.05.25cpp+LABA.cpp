#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    double balance;
    string accountNumber;

    class Transaction {
    private:
        double amount;
        string type;
        int timestamp;

    public:
        Transaction(double amt, string t)
            : amount(amt), type(t) {}
    };

    class Owner {
    private:
        string name, address, phone;

    public:
        Owner(string n, string a, string p)
            : name(n), address(a), phone(p) {}

        void displayInfo() {
            cout << "имя: " << name << endl;
            cout << "адрес: " << address << endl;
            cout << "телефон: " << phone << endl;
        }
    };
    vector<Transaction> transactions;
    Owner owner;

public:
    BankAccount(string an, string on, string oa, string op)
        : accountNumber(an), balance(0.0), owner(on, oa, op) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back(Transaction(amount, "Депозит"));
            cout << "Депозит: " << amount << ", Баланс теперь: " << balance << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction(amount, "забрали"));
            cout << "забрали: " << amount << ", Баланс теперь: " << balance << endl;
        }
    }

    double getBalance() {
        return balance;
    }

    void info() {
        owner.displayInfo();
    }

};

int main() {
    setlocale(LC_ALL, "");
    BankAccount account("13233132", "Kasey", "ГАЗОВАЯ", "312123132");
    cout << "Баланс изначально: " << account.getBalance() << endl;
    account.deposit(1000);
    account.withdraw(200);
    account.info();
}