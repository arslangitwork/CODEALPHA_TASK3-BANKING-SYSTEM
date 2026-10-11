#include <iostream>
#include <string>
using namespace std;

class Transaction
{
private:
    int transactionID;
    string type;
    double amount;
    string details;

public:
    Transaction()
    {
        transactionID = 0;
        type = "";
        amount = 0;
        details = "";
    }

    Transaction(int id, string t, double a, string d)
    {
        transactionID = id;
        type = t;
        amount = a;
        details = d;
    }

    void displayTransaction()
    {
        cout << "Transaction ID: " << transactionID << endl;
        cout << "Type: " << type << endl;
        cout << "Amount: Rs. " << amount << endl;
        cout << "Details: " << details << endl;
        cout << "--------------------------------" << endl;
    }
};

class Customer
{
private:
    int customerID;
    string name;
    string phone;

public:
    Customer()
    {
        customerID = 0;
        name = "";
        phone = "";
    }

    Customer(int id, string n, string p)
    {
        customerID = id;
        name = n;
        phone = p;
    }

    int getCustomerID()
    {
        return customerID;
    }


string getName()
{
    return name;
}

string getPhone()
{
    return phone;
}

void displayCustomer()
{
    cout << "Customer ID: " << customerID << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phone << endl;
}
};

class Account
{
private:
    int accountNumber;
    int customerID;
    double balance;
    Transaction transactions[100];
    int transactionCount;

public:
    Account()
    {
        accountNumber = 0;
        customerID = 0;
        balance = 0;
        transactionCount = 0;
    }

    Account(int accNo, int custID)
    {
        accountNumber = accNo;
        customerID = custID;
        balance = 0;
        transactionCount = 0;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    int getCustomerID()
    {
        return customerID;
    }

    double getBalance()
    {
        return balance;
    }

    void addTransaction(string type, double amount, string details)
    {
        if (transactionCount < 100)
        {
            transactionCount++;
            transactions[transactionCount - 1] =
                Transaction(transactionCount, type, amount, details);
        }
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid deposit amount!" << endl;
            return;
        }

        balance = balance + amount;

        addTransaction(
            "Deposit",
            amount,
            "Money deposited into account."
        );

        cout << "Deposit successful!" << endl;
        cout << "New Balance: Rs. " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount!" << endl;
            return;
        }

        if (amount > balance)
        {
            cout << "Insufficient balance!" << endl;
            return;
        }

        balance = balance - amount;

        addTransaction(
            "Withdrawal",
            amount,
            "Money withdrawn from account."
        );

        cout << "Withdrawal successful!" << endl;
        cout << "New Balance: Rs. " << balance << endl;
    }

    bool transferMoney(Account& receiver, double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid transfer amount!" << endl;
            return false;
        }

        if (amount > balance)
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }

        balance = balance - amount;
        receiver.balance = receiver.balance + amount;

        addTransaction(
            "Transfer Sent",
            amount,
            "Money transferred to account " +
            to_string(receiver.accountNumber)
        );

        receiver.addTransaction(
            "Transfer Received",
            amount,
            "Money received from account " +
            to_string(accountNumber)
        );

        cout << "Transfer successful!" << endl;
        cout << "Your new balance: Rs. "
            << balance << endl;

        return true;
    }

    void displayAccount()
    {
        cout << endl;
        cout << "========== ACCOUNT INFORMATION ==========" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Customer ID: " << customerID << endl;
        cout << "Balance: Rs. " << balance << endl;
        cout << "=========================================" << endl;
    }

    void displayRecentTransactions()
    {
        cout << endl;
        cout << "========== TRANSACTION HISTORY ==========" << endl;

        if (transactionCount == 0)
        {
            cout << "No transactions found." << endl;
            return;
        }

        int start;

        if (transactionCount > 5)
        {
            start = transactionCount - 5;
        }
        else
        {
            start = 0;
        }

        for (int i = start; i < transactionCount; i++)
        {
            transactions[i].displayTransaction();
        }
    }
};

class BankingSystem
{
private:
    Customer customers[50];
    Account accounts[100];
    int customerCount;
    int accountCount;

public:
    BankingSystem()
    {
        customerCount = 0;
        accountCount = 0;
    }

    void createCustomer()
    {
        if (customerCount >= 50)
        {
            cout << "Customer limit reached!" << endl;
            return;
        }

        int id;
        string name;
        string phone;

        cout << "Enter Customer ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        customers[customerCount] =
            Customer(id, name, phone);

        customerCount++;

        cout << "Customer created successfully!" << endl;
    }

    void createAccount()
    {
        if (accountCount >= 100)
        {
            cout << "Account limit reached!" << endl;
            return;
        }

        int accountNumber;
        int customerID;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Customer ID: ";
        cin >> customerID;

        int index = findCustomer(customerID);

        if (index == -1)
        {
            cout << "Customer not found!" << endl;
            return;
        }

        accounts[accountCount] =
            Account(accountNumber, customerID);

        accountCount++;

        cout << "Account created successfully!" << endl;
    }

    int findCustomer(int id)
    {
        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].getCustomerID() == id)
            {
                return i;
            }
        }

        return -1;
    }

    int findAccount(int accountNumber)
    {
        for (int i = 0; i < accountCount; i++)
        {
            if (accounts[i].getAccountNumber()
                == accountNumber)
            {
                return i;
            }
        }

        return -1;
    }

    void depositMoney()
    {
        int accountNumber;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        int index = findAccount(accountNumber);

        if (index == -1)
        {
            cout << "Account not found!" << endl;
            return;
        }

        cout << "Enter amount to deposit: ";
        cin >> amount;

        accounts[index].deposit(amount);
    }

    void withdrawMoney()
    {
        int accountNumber;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        int index = findAccount(accountNumber);

        if (index == -1)
        {
            cout << "Account not found!" << endl;
            return;
        }

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        accounts[index].withdraw(amount);
    }

    void transferMoney()
    {
        int senderAccount;
        int receiverAccount;
        double amount;

        cout << "Enter Sender Account Number: ";
        cin >> senderAccount;

        cout << "Enter Receiver Account Number: ";
        cin >> receiverAccount;

        cout << "Enter amount to transfer: ";
        cin >> amount;

        int senderIndex = findAccount(senderAccount);
        int receiverIndex = findAccount(receiverAccount);

        if (senderIndex == -1)
        {
            cout << "Sender account not found!" << endl;
            return;
        }

        if (receiverIndex == -1)
        {
            cout << "Receiver account not found!" << endl;
            return;
        }

        if (senderIndex == receiverIndex)
        {
            cout << "Cannot transfer to the same account!"
                << endl;
            return;
        }

        accounts[senderIndex].transferMoney(
            accounts[receiverIndex],
            amount
        );
    }

    void displayAccountInformation()
    {
        int accountNumber;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        int index = findAccount(accountNumber);

        if (index == -1)
        {
            cout << "Account not found!" << endl;
            return;
        }

        accounts[index].displayAccount();
    }

    void displayCustomerInformation()
    {
        int customerID;

        cout << "Enter Customer ID: ";
        cin >> customerID;

        int index = findCustomer(customerID);

        if (index == -1)
        {
            cout << "Customer not found!" << endl;
            return;
        }

        cout << endl;
        cout << "========== CUSTOMER INFORMATION ==========" << endl;

        customers[index].displayCustomer();

        cout << "==========================================" << endl;
    }

    void displayTransactions()
    {
        int accountNumber;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        int index = findAccount(accountNumber);

        if (index == -1)
        {
            cout << "Account not found!" << endl;
            return;
        }

        accounts[index].displayRecentTransactions();
    }
};

int main()
{
    BankingSystem bank;
    int choice;

    do
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "        BANKING MANAGEMENT SYSTEM" << endl;
        cout << "========================================" << endl;

        cout << "1. Create Customer" << endl;
        cout << "2. Create Account" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Transfer Money" << endl;
        cout << "6. Display Customer Information" << endl;
        cout << "7. Display Account Information" << endl;
        cout << "8. View Recent Transactions" << endl;
        cout << "9. Exit" << endl;

        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cout << endl;

        switch (choice)
        {
        case 1:
            bank.createCustomer();
            break;

        case 2:
            bank.createAccount();
            break;

        case 3:
            bank.depositMoney();
            break;

        case 4:
            bank.withdrawMoney();
            break;

        case 5:
            bank.transferMoney();
            break;

        case 6:
            bank.displayCustomerInformation();
            break;

        case 7:
            bank.displayAccountInformation();
            break;

        case 8:
            bank.displayTransactions();
            break;

        case 9:
            cout << "Thank you for using the Banking System!"
                << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 9);

    return 0;
}
