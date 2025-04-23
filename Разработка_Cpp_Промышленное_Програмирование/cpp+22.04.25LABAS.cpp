#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Transaction {
    static vector<Transaction> transactionHistory;
    static int totalTransactions;
    static double totalAmount, maxLimit;

public:
    string sender, receiver, timestamp;
    double amount;

    Transaction(string s, string r, double a, string t): sender(s), receiver(r),
        amount(a), timestamp(t)
    {

        totalTransactions++;
        totalAmount += amount;

        transactionHistory.push_back(*this);
    }

    void print() {
        cout << "Отправитель: " << sender << ", Получатель: " << receiver
            << ", Сумма: " << amount << ", Время: " << timestamp << endl;
    }

    static int getTotalTransactions() {
        return totalTransactions;
    }

    static double getTotalAmount() {
        return totalAmount;
    }

    static double getAverageAmount() {
        if (totalTransactions == 0) return 0;
        return totalAmount / totalTransactions;
    }

    static void cancelTransaction(Transaction transaction) {
        totalTransactions--;
        totalAmount -= transaction.amount;
    }

    static vector<Transaction> getTransactionsByUser(string user) {
        vector<Transaction> userTransactions;
        for (auto transaction : transactionHistory) {
            if (transaction.sender == user || transaction.receiver == user) {
                userTransactions.push_back(transaction);
            }
        }
        return userTransactions;
    }
};

int Transaction::totalTransactions = 0;
double Transaction::totalAmount = 0.0;
double Transaction::maxLimit = 10000.0;
vector<Transaction> Transaction::transactionHistory;

int main()
{
    setlocale(LC_ALL, "");
    Transaction t1("Alice", "Bob", 250.0, "2023.10.01");
    Transaction t2("Bob", "Charlie", 300.0, "2023.10.01");

    cout << "Общее количество транзакций: " << Transaction::getTotalTransactions() << endl;
    cout << "Общая сумма транзакций: " << Transaction::getTotalAmount() << endl;
    cout << "Средний размер транзакции: " << Transaction::getAverageAmount() << endl;

    cout << "Все транзакции:" << endl;
    auto transactions = Transaction::getTransactionsByUser("Bob");
    for (auto tx : transactions) {
        tx.print();
    }

    Transaction::cancelTransaction(t2);
    cout << endl << "Общее количество транзакций: " << Transaction::getTotalTransactions() << endl;
    cout << "Общая сумма транзакций: " << Transaction::getTotalAmount() << endl;
}