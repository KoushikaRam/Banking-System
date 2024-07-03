#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

struct Transaction {
    time_t timestamp;
    string type;
    double amount;

    Transaction(string type, double amount) : type(type), amount(amount) {
        timestamp = time(nullptr);
    }
};

class BankAccount {
private:
    string accountNumber;
    string ownerName;
    double balance;
    vector<Transaction> history;

public:
    BankAccount(string accountNumber, string ownerName, double balance = 0)
        : accountNumber(accountNumber), ownerName(ownerName), balance(balance) {}

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance. Withdrawal failed." << endl;
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdrawal", amount));
        return true;
    }

    double calculateAvailableBalance() const {
        double availableBalance = balance;
        for (const auto& transaction : history) {
            if (transaction.type == "Withdrawal") {
                availableBalance -= transaction.amount;
            }
        }
        return availableBalance;
    }

    void display() const {
        cout<<endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Owner Name: " << ownerName << endl;
        cout << "Available Balance: $" << balance << endl;
        cout << "\nTransaction History:" << endl;
        for (const auto& transaction : history) {
            cout << "- " << asctime(localtime(&transaction.timestamp))
                 << "Type: " << transaction.type << ", Amount: $" << transaction.amount << endl;
        }
        cout << endl;
    }
};

double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            break;
        } else {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        }
    }
    return value;
}

int main() {
    string accountNumber, ownerName;
    double initialBalance;

    cout << "Welcome to Your Bank Banking System!" << endl;
    cout << "Enter Account Number: ";
    cin >> accountNumber;
    cout << "Enter Owner Name: ";
    cin.ignore(); // Clear newline character from input buffer
    getline(cin, ownerName);
    initialBalance = getDoubleInput("Enter Initial Balance: $");

    BankAccount account(accountNumber, ownerName, initialBalance);

    while (true) {
        cout << "\nChoose an option:" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Account Details" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double amount = getDoubleInput("Enter amount to deposit: $");
                account.deposit(amount);
                cout << "Deposit successful." << endl;
                break;
            }
            case 2: {
                double amount = getDoubleInput("Enter amount to withdraw: $");
                if (account.withdraw(amount)) {
                    cout << "Withdrawal successful." << endl;
                }
                break;
            }
            case 3:
                account.display();
                break;
            case 4:
                cout << "\n hank you for using Our System" << endl<<"Have a Nice Day :)"<<endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
        }
    }

    return 0;
}
