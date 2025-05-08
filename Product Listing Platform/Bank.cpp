#include "Bank.h"
#include <iostream>
#include "FileHandler.h"
#include "Globals.h"
#include <algorithm>
#include <limits>


using namespace std;

bool Bank::operator==(const Bank &other) const
{
    return (userID == other.userID); // 2 Accounts are same if their user's IDs are same
}

void Bank::deposit()
{
    float amount = getValidatedFloatInput("Enter the amount that you want to deposit (Dollars): ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    this->balance += amount;
    FileHandler::overwriteBankData(accounts);
    cout << "The amount has been deposited successfully!" << endl
         << endl;
}

void Bank::checkForAccountNumber(int &IDforCheck)
{
    bool accountFound = false;
    int i;
    for (i = 0; i < accounts.size(); i++)
         if (accounts[i].userID == IDforCheck)
        {
            accountFound = true;
            break;
        }

    if (accountFound)
    { // If the provided calling user has a registered card number

        cout << endl << "You are already registered with us. Login to your bank account to continue" << endl;

        int input;
        while (true)
        {
            cout << endl << "Enter 1 to Login and 0 to go back to your cart" << endl;
            input = getValidatedIntInput("Enter your Choice: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (input)
            {
            case 1:
            {
                accounts[i].bankLogin();
                break;
            }
            case 0:
            {
                cout << "Returning to your Cart..." << endl;
                return;
            }
            default:
                cout << "Invalid Choice. Please try Again!" << endl
                        << endl;
            }
        }
    }
    else
    { // If he doesnt have a card number registered

        cout << "Sorry! You are not registered with us. Signup to your bank account to continue" << endl;

        int input;
        while (true)
        {
            cout << endl << "Enter 1 to Signup and 0 to go back to your cart" << endl;
            input = getValidatedIntInput("Enter your Choice: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (input)
            {
            case 1:
            {
                Bank newAccount;
                newAccount.bankSignup(IDforCheck);
                return;
            }
            case 0:
            {
                cout << "Returning to your Cart..." << endl;
                return;
            }
            default:
                cout << "Invalid Choice. Please try Again!" << endl
                        << endl;
            }
        }
    }
}

void Bank::bankSignup(int &userID)
{

    this->userID = userID;

    string enteredCardNum;
    do
    {
        cout << endl << "Enter your card number (16 digits without spaces and hyphens or '<' to go back to bank main menu): ";
        cin >> enteredCardNum;
        if (enteredCardNum == "<")
            return;
        if (enteredCardNum.size() < 16 || !(all_of(enteredCardNum.begin(), enteredCardNum.end(), ::isdigit)))
            cout << "Invalid Input! Please enter 16 digits only" << endl;
        else
        {
            cout << "Card Number Valid!" << endl;
            this->cardNumber = enteredCardNum;
        }

    } while (enteredCardNum.size() < 16 ||
             !(all_of(enteredCardNum.begin(), enteredCardNum.end(), ::isdigit)) ||
             enteredCardNum != this->cardNumber);

    cout << "Signup successful!" << endl;
    cout << "Note: Your balance will be initialized to 0.0$. Login to deposit Money" << endl;
    this->balance = 0.0;

    accounts.push_back(*this);
    for (int i = 0; i < accounts.size(); i++)
        cout << accounts[i].userID << endl;
    FileHandler::appendBankData(*this);
}

void Bank::bankLogin()
{

    string enteredCardNum;
    do
    {
        cout << endl << "Enter your card number (16 digits without spaces and hyphens or '<' to go back to bank main menu): ";
        cin >> enteredCardNum;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (enteredCardNum == "<")
            return;
        if (enteredCardNum.size() < 16 || !(all_of(enteredCardNum.begin(), enteredCardNum.end(), ::isdigit)))
            cout << "Invalid Input! Please enter 16 digits only" << endl;
        else if (enteredCardNum != this->cardNumber)
            cout << "The entered card number is Wrong. Please try Again!" << endl;
        else
        {

            int input;
            while (true)
            {
                cout << endl << "Enter 1 to proceed with your transaction" << endl;
                cout << "Enter 2 to deposit money" << endl;
                cout << "Enter 3 to remove your account from bank database" << endl;
                cout << "Enter 0 to go back to main menu" << endl;

                input = getValidatedIntInput("Enter your Choice: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (input)
                {
                case 1:
                {
                    cout << "Your transaction is being confirmed..." << endl;
                    this->confirmPurchase();
                    return;
                }
                case 2:
                {
                    this->deposit();
                    break;
                }
                case 3:
                {
                    this->removeAccount();
                    return;
                }
                case 0:
                {
                    cout << "Returning to bank main menu..." << endl;
                    return;
                }
                default:
                    cout << "Invalid Choice. Please try Again!" << endl
                         << endl;
                }
            }
        }

    } while (enteredCardNum.size() < 16 ||
             !(all_of(enteredCardNum.begin(), enteredCardNum.end(), ::isdigit)) ||
             enteredCardNum != this->cardNumber);
}

void Bank::confirmPurchase()
{
    if (users[User::getUserByID(this->userID)].cart.totalPrice > this->balance)
    {
        cout << "Error: You do not have enough balance to make this purchase" << endl;

        int input;
        while (true)
        {
            cout << endl << "Enter 1 to deposit money to your account and 0 to go back to bank main menu" << endl;

            input = getValidatedIntInput("Enter your Choice: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (input)
            {
            case 1:
            {
                this->deposit();
                break;
            }
            case 0:
            {
                cout << "Returning to bank main menu..." << endl;
                return;
            }
            }
        }
    }

    else
    {
        this->balance -= users[User::getUserByID(this->userID)].cart.totalPrice;
        FileHandler::overwriteBankData(accounts);
        users[User::getUserByID(this->userID)].cart.totalPrice = 0.0;
        users[User::getUserByID(this->userID)].cart.ids.clear();
        cout << "Purchase Successful. Order Dispatched!" << endl;
    }
}

void Bank::removeAccount()
{
    accounts.erase(
        remove(accounts.begin(), accounts.end(), *this),
        accounts.end());
    FileHandler::overwriteBankData(accounts);
    cout << "Your account has been removed from the bank" << endl;
}