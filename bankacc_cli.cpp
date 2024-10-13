#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chorno>
using namespace std;

class Account {
public:
    string acc_holder;
    string acc_number;
    double balance;

    // Constructor to initialize account details
    Account(string name, string number, double initialDeposit) {
        acc_holder = name;        
        acc_number = number;
        balance = initialDeposit;
    }

    // Deposit function
    void Deposit(double amount) {
        balance += amount;
        cout << "Amount successfully deposited. New balance: $" << balance << endl;
        this_thread::sleep_for(chrono::seconds(5))
    }

    // Withdraw function
    void withdraw(double amount) {
        
        if (balance >= amount) {
            balance -= amount;
            cout << "Amount successfully withdrawn. New Balance: $" << balance << endl;
            this_thread::sleep_for(chrono::seconds(5))
        } else {
            do {cout << "Balance Insufficient." << endl;
            withdraw(amount)
            } while (balance<amount);
        }
    }

    // Show balance function
    void showbalance() {
        cout << "Balance: $" << balance << endl;
        this_thread::sleep_for(chrono::seconds(5))
    }

    // Generate a 12-digit account number
    string createacc_number() {
        string acc_number_str = "";  // Start with an empty string
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 9);

        for (int i = 0; i < 12; ++i) {  // Generate 12 digits
            int digit = dist(gen);  // Generate a random digit
            acc_number_str += to_string(digit);  // Append digit to string
        }

        return acc_number_str;  // Return the generated account number as a string
        this_thread::sleep_for(chrono::seconds(5))
    }
};

int main() {
    vector<Account> accounts;  // List of accounts
    int choice;

    do {
        cout << "\n Welcome To The Maze Bank App! \n";
        cout << "\n Select Your Option: \n 1. Create Account \n 2. Deposit \n 3. Withdraw \n 4. Show Balance \n 5. Quit \n";
        cout << "\n Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            string acc_number;
            double deposit_amount = 0;
            cout << "Enter Your Name: ";
            cin >> name;

            // Create an object to generate a random account number
            Account newaccount("John Doe", "0", 0.0);
            acc_number = newaccount.createacc_number();

            cout << "Your Account Number Will be revealed after the first deposit.\n";
            do {
                cout << "First Deposit To Complete The Registration Process. Deposit Must Be Greater Than Or Equal To $1000: ";
                cin >> deposit_amount;
            } while (deposit_amount < 1000);

            accounts.push_back(Account(name, acc_number, deposit_amount));  // Add the new account

            cout << "Account Created Successfully! Your Account Number is: " << acc_number << endl;
        }
        else if (choice == 2 || choice == 3 || choice == 4) {
            string acc_num;
            cout << "Enter your 12-digit account number: ";
            cin >> acc_num;

            bool account_found = false;

            for (Account &acc : accounts) {  // Search for the account by account number
                if (acc.acc_number == acc_num) {
                    account_found = true;

                    if (choice == 2) {
                        double amount;
                        cout << "Enter the amount to deposit: ";
                        cin >> amount;
                        acc.Deposit(amount);
                    } 
                    else if (choice == 3) {
                        double amount;
                        cout << "Enter the amount to withdraw: ";
                        cin >> amount;
                        acc.withdraw(amount);
                    } 
                    else if (choice == 4) {
                        acc.showbalance();
                    }

                    break;
                }
            }

            if (!account_found) {
                cout << "Account number not found!" << endl;
            }
        }
    } while (choice != 5);

    cout << "Exiting system." << endl;
    return 0;
}
