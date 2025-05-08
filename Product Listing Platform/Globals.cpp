#include "Globals.h"
#include <iostream>
#include "Admin.h"
#include "User.h"
#include "Product.h"
#include "Bank.h"
#include <limits>

using namespace std;

vector<User> users;       // Global vector
vector<Product> products; // Global vector
vector<Admin> admins;     // Global Vector
vector<Bank> accounts;    // Global Vector
bool asAdmin;
optional<int> cAdminID; // Variable might have a value or might not
optional<int> cUserID;

float getValidatedFloatInput(const string &prompt)
{
    float input;

    while (true)
    {
        cout << prompt;
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input! Please enter a valid number" << endl;
        }

        else
            return input;
    }
}

int getValidatedIntInput(const string &prompt)
{
    int input;

    while (true)
    {
        cout << prompt;
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input! Please enter a valid number" << endl;
        }

        else
            return input;
    }
}
