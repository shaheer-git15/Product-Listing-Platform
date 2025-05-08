/* 
    Add braces on cases
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <optional>
#include <limits>
#include "Product.h"
#include "Admin.h"
#include "User.h"
#include "Bank.h"
#include "FileHandler.h"
#include "Globals.h"


using namespace std;

void adminSignupInterface();
void adminLoginInterface();
void adminDashboard();
void listAllUsers();
void userSignupInterface();
void userLoginInterface();
void userDashboard();
void listAllProducts();
void sortInterface();
void sortProducts(int &by, int &ascending);
void filterInterface();
vector<Product> applyFilter(int type, int by, float value);
vector<Product> applyFilter(int type, int by, string value);
void listFilteredProducts(const vector<Product> &filteredProducts);
void searchInterface();
vector<Product> searchFor(string &term);
void listSearchedProducts(const vector<Product> &searchedProducts);
string transformToLower(string &s);

int main()
{
    users = FileHandler::readUserData();
    cout << "***User CSV Data read from main***" << endl;
    products = FileHandler::readProductData();
    cout << "***Products CSV Data read from main***" << endl;
    admins = FileHandler::readAdminData();
    cout << "***Admins CSV Data read from main***" << endl;
    accounts = FileHandler::readBankData();
    cout << "***Banks CSV Data read from main***" << endl;

    int input;    
    while (true) {
        cout << endl << "WELCOME TO PRODUCTORIES!" << endl;
        cout << "Enter 1 for signup as admin" << endl;
        cout << "Enter 2 for login as admin" << endl;
        cout << "Enter 3 for signup as user" << endl;
        cout << "Enter 4 for login as user" << endl;
        cout << "Enter 0 To terminate program" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input) {
            case 1: {
                adminSignupInterface();
                break;
            }
            case 2: {
                adminLoginInterface();
                break;
            }
            case 3: {
                userSignupInterface();
                break;
            }
            case 4: {
                userLoginInterface();
                break;
            }
            case 0: {
                cout << "Thank you for using our Platform! Goodbye!"<<endl;
                return 0;
            }
            default: 
                cout <<"Invalid choice. Please try Again!"<<endl;
        }
    }
        
}

void adminSignupInterface() {
    Admin newAdmin;
    string name, email, password;

    string in;

    do 
    {
        cout << endl << "Provide secret platform code to signup as an Admin (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<") return;
        if (in != "Winter is Coming!")
            cout << "The secret code is incorrect! Please Try Again!" << endl;
    } while (in != "Winter is Coming!");

    cout << "Enter your Full Name (Or '<' to go back to main menu): ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, in);
    if (in == "<") return;
    name = in;
    do
    {
        cout << "Enter your Email [Example: *@gmail.com] (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<") return;
        if (in.find("@gmail.com") == string::npos)
            cout << "Please Enter a valid Email (Example '*@gmail.com')" << endl;
    } while (in.find("@gmail.com") == string::npos);
    email = in;

    do
    {
        cout << "Enter your Password [Must contain at least 4 characters] (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<") return;
        if (in.size() < 4)
            cout << "Error: Password must contain at least 4 characters" << endl;
    } while (in.size() < 4);
    password = in;

    newAdmin.signup(name, email, password);
}

void adminLoginInterface() {

    string name, email, password;

    string in;
    int i;
    do
    {
        cout << endl <<  "Enter your email (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<") return;
        for (i = 0; i < admins.size(); i++)
            if (admins[i].email == in) {
                cout << "Username found!" << endl;
                break;
            }
        if (i == admins.size())
            cout << "No such username was found! Please try again." << endl;
    } while (i == admins.size());
    email = in;

    do
    {
        cout << "Enter your password (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<") return;
        if (in != admins[i].password)
            cout << "Your Password is incorrect! Please try again." << endl;

    } while (in != admins[i].password);
    password = in;

    cout << "You are successfully logged in as: " << admins[i].name << endl << endl;
    asAdmin = true;
    cAdminID = admins[i].adminID;
    cUserID.reset();

    adminDashboard();
    return;
}

void adminDashboard() {
    
    int input;
    while (true)
    {
        cout << endl
             << "WELCOME TO YOUR ADMIN DASHBOARD " << admins[Admin::getAdminByID(cAdminID.value())].name << "!" << endl;
        cout << "How can we help you today?" << endl << endl;
        cout << "Enter 1 to list all products" << endl;
        cout << "Enter 2 to list all users" << endl;
        cout << "Enter 0 to Log Out" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input)
        {
        case 1: {
            listAllProducts();
            break;
        }
        case 2: {
            listAllUsers();
            break;
        }
        case 0: {
            cout << "Returning to main menu..." << endl;
            return;
        }
        default:
            cout << "Invalid choice. Please try Again!" << endl;
        }
    }
}

void listAllUsers() {

    bool show = true;
    int input;
    while (true)
    {
        if (show) {
            cout << endl
                 << "ID\tName\tEmail\tListed Product IDs" << endl;
            cout << "___________________________________________________________________________________________" << endl;
            cout << "___________________________________________________________________________________________" << endl;

            for (int i = 0; i < users.size(); i++)
            {
                cout << users[i].userID << "\t"
                     << users[i].name << "\t"
                     << users[i].email << "\t" << "[";
                if (users[i].prodIDs.empty())
                    cout << "No Products Listed" << endl;
                else {
                    for (int j = 0; j < users[i].prodIDs.size() - 1; j++)
                        cout << users[i].prodIDs[j] << ",";
                    cout << users[i].prodIDs.back() << "]" << endl;
                }

                cout << "________________________________________________________________________________________" << endl;
            }
        }
            
        cout << endl << "Enter 1 to show Products listed by a user" << endl;
        cout << "Enter 2 to Deactivate a User" << endl;
        cout << "Enter 0 to return to your dashboard" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input)
            {
            case 1: {
                int id;
                id = getValidatedIntInput("Enter User ID: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int index = User::getUserByID(id);
                if (index == -1) {
                    cout << "No user found with the specified ID" << endl;
                    show = false;
                }
                else {
                    users[index].listProducts();
                    show = true;
                }
                break;
            }
            case 2: {
                int id = getValidatedIntInput("Enter the ID of the user to be deactivated: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int index = User::getUserByID(id);
                if (index == -1) {
                    cout << "No user has the specified ID" << endl;
                    show = false;
                }
                else {
                    admins[Admin::getAdminByID(cAdminID.value())].deactivateUser(index);
                    show = true;
                }
                break;
            }
            case 0: {
                cout << "Returning to your dashboard..." << endl;
                return;
            }
            default: {
                cout << "Invalid choice. Please try Again!" << endl;
                show = false;
            }
        }
    }
}

void userSignupInterface() {
    User newUser;
    string name, email, password;
    string in;

    cout << endl <<"Enter your Full Name (Or '<' to go back to main menu): ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, in);
    if (in == "<") return;
    name = in;
    do
    {
        cout << "Enter your Email [Example: *@gmail.com] (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<") return;
        if (in.find("@gmail.com") == string::npos)
            cout << "Please Enter a valid Email (Example '*@gmail.com')" << endl;
    } while (in.find("@gmail.com") == string::npos);
    email = in;

    do
    {
        cout << "Enter your Password [Must contain at least 4 characters] (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<") return;
        if (in.size() < 4)
            cout << "Error: Password must contain at least 4 characters" << endl;
    } while (in.size() < 4);
    password = in;

    cout << "You are successfully signed up as: " << name << endl;
    newUser.signup(name, email, password);
}

void userLoginInterface()
{

    string email, password;

    string in;
    int i;
    do
    {
        cout << endl << "Enter your email (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<")
            return;
        for (i = 0; i < users.size(); i++)
            if (users[i].email == in)
            {
                cout << "Username found!" << endl;
                break;
            }
        if (i == users.size())
            cout << "No such username was found! Please try again." << endl;
    } while (i == users.size());
    email = in;

    do
    {
        cout << "Enter your password (Or '<' to go back to main menu): ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, in);
        if (in == "<")
            return;
        if (in != users[i].password)
            cout << "Your Password is incorrect! Please try again." << endl;
    } while (in != users[i].password);
    password = in;

    cout << "You are successfully logged in as: " << users[i].name << endl
         << endl;
    asAdmin = false;
    cUserID = users[i].userID;
    cAdminID.reset(); // Removes all values from cAdmin

    userDashboard();
    return;
}

void userDashboard() {
    
    int input;
    while (true)
    {
        cout << endl
             << "WELCOME TO YOUR DASHBOARD " << users[User::getUserByID(cUserID.value())].name << "!" << endl;
        cout << "How can we help you today?" << endl << endl;
        cout << "Enter 1 to list all products" << endl;
        cout << "Enter 2 to show (or modify) your listings" << endl;
        cout << "Enter 3 to show Cart" << endl;
        cout << "Enter 0 to Log Out" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input)
        {
        case 1: {
            listAllProducts();
            break;
        }
        case 2: {
            users[User::getUserByID(cUserID.value())].listProducts();
            break;
        }
        case 3: {
            users[User::getUserByID(cUserID.value())].showCart();
            break;
        }
        case 0: {
            cout << "Returning to main menu..." << endl;
            return;
        }
        default:
            cout << "Invalid choice. Please try Again!" << endl;
        }
    }
}

void listAllProducts()
{
    bool show = true;
    int input;
    while (true)
    {
        if (show) {
            cout << endl
                 << "ID\tCategory\tName\tPrice\tRating\tStock\tSeller" << endl;
            cout << "___________________________________________________________________________________________" << endl;
            cout << "___________________________________________________________________________________________" << endl;

            for (int i = 0; i < products.size(); i++)
            {
                cout << products[i].productID << "\t"
                     << products[i].category << "\t"
                     << products[i].name << "\t"
                     << products[i].price << "\t"
                     << products[i].rating << "\t"
                     << products[i].stock << "\t"
                     << products[i].seller << "\t" << endl;
                cout << "________________________________________________________________________________________" << endl;
            }
        }

        cout << endl << "Enter 1 to show details of a product" << endl;
        cout << "Enter 2 to search for a product" << endl;
        cout << "Enter 3 to sort the list" << endl;
        cout << "Enter 4 to apply a filter" << endl;
        if (asAdmin)
            cout << "Enter 5 to Remove a Product" << endl;
        cout << "Enter 0 to return to your dashboard" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input) {
            case 1: {
                int id;
                id = getValidatedIntInput("Enter Product ID: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int index = Product::getProductByID(id);
                if (index == -1) {
                    cout << "No Product has the specified ID" << endl;
                    show = false;
                }
                else {
                    products[index].showDetails();
                    show = true;
                }
                break;
            }
            case 2: {
                searchInterface();
                show = true;
                break;
            }
            case 3: {
                sortInterface();
                show = true;
                break;
            }
            case 4: {
                filterInterface();
                show = true;
                break;
            }
            case 5: {
                if (asAdmin) {
                    int id = getValidatedIntInput("Enter the ID of the product you want to remove: ");
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    int index = Product::getProductByID(id);
                    if (index == -1) {
                        cout << "No Product has the specified ID" << endl;
                        show = false;
                    }
                    else {
                        admins[Admin::getAdminByID(cAdminID.value())].removeProduct(index); // .value accesses the Admin obj in the optional wrapper
                        show = true;
                    }
                }
                else {
                    cout << "Invalid choice. Please try Again!" << endl;
                    show = false;
                }
                break;
            }
            case 0: {
                cout << "Returning to your dashboard..." << endl;
                return;
            }
            default: {
                cout << "Invalid choice. Please try Again!" << endl;
                show = false;
            }
        }
    }
}

void sortInterface() {

    auto ascendingFunc = []() -> int
    {
        int ascending;
        ascending = getValidatedIntInput("Enter 1 for ascending order and 0 for descending order: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ascending == 0 || ascending == 1)
            return ascending;
        cout << "Invalid Input!" << endl;
        return -1;
    };

    int by;

    while (true)
    {
        cout << endl << "Enter 1 to sort by ID" << endl;
        cout << "Enter 2 to sort by Category" << endl;
        cout << "Enter 3 to sort by Name" << endl;
        cout << "Enter 4 to sort by Price" << endl;
        cout << "Enter 5 to sort by Rating" << endl;
        cout << "Enter 6 to sort by Stock" << endl;
        cout << "Enter 7 to sort by Seller" << endl;
        cout << "Enter 0 to return to All Products Listing" << endl << endl;

        by = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (by >= 1 && by <= 7) {
            int ascending = ascendingFunc();
            if (ascending != -1) {
                sortProducts(by, ascending);
                return;
            }

        }
        else if (by == 0) {
            cout << "Returning to All Products Listing..." << endl;
            return;
        }
        else
            cout << "Invalid Choice. Please try again!" << endl;
    }
}

void sortProducts(int &by, int &ascending) {
    sort(products.begin(), products.end(), [&](const Product &a, const Product &b) {
        switch (by) {
            case 1:
                return ascending ? (a.productID < b.productID) : (a.productID > b.productID);
            case 2:
                return ascending ? (a.category < b.category) : (a.category > b.category);
            case 3:
                return ascending ? (a.name < b.name) : (a.name > b.name);
            case 4:
                return ascending ? (a.price < b.price) : (a.price > b.price);
            case 5:
                return ascending ? (a.rating < b.rating) : (a.rating > b.rating);
            case 6:
                return ascending ? (a.stock < b.stock) : (a.stock > b.stock);
            case 7:
                return ascending ? (a.seller < b.seller) : (a.seller > b.seller);
            default:
                return false;
        }
    });

}

void filterInterface() {
    auto getTypeFunc = []() -> int
    {
        int type;
        do {
            cout << endl << "Enter 1 for filtering by less than (or equal to) a value" << endl;
            cout << "Enter 2 for filtering by greater than (or equal to) a value" << endl;
            cout << "Enter 3 for filtering by equal to a value" << endl;
            type = getValidatedIntInput("Enter your Choice: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (type >= 1 && type <= 3)
                return type;
            cout << "Invalid Input! Try Again" << endl;
        } while (!(type >= 1 && type <= 3));
    };

    auto getFilterValue = [](int &by) -> string
    {   
        cout << "Enter a value to apply filter upon: ";
        if (by == 1 || by == 5)
        {
            string value;
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, value);
            return value;
        }
        else {
            float value = getValidatedFloatInput("Enter a Value to apply filter upon: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return to_string(value);
        }
    };

    int by;
    while (true) {
        cout << endl << "Enter 1 to filter by category" << endl;
        cout << "Enter 2 to filter by price" << endl;
        cout << "Enter 3 to filter by rating" << endl;
        cout << "Enter 4 to filter by stock" << endl;
        cout << "Enter 5 to filter by seller" << endl;
        cout << "Enter 0 to return to All Products Listing" << endl;

        by = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(by) {
            case 1: {
                int type = getTypeFunc();
                string value = getFilterValue(by);
                listFilteredProducts(applyFilter(type, by, value));
                break;
            }
            case 2: {
                int type = getTypeFunc();
                float value = stof(getFilterValue(by));
                listFilteredProducts(applyFilter(type, by, value));
                break;
            }
            case 3: {
                int type = getTypeFunc();
                float value = stof(getFilterValue(by));
                listFilteredProducts(applyFilter(type, by, value));
                break;
            }
            case 4: {
                int type = getTypeFunc();
                float value = stof(getFilterValue(by));
                listFilteredProducts(applyFilter(type, by, value));
                break;
            }
            case 5: {
                int type = getTypeFunc();
                string value = getFilterValue(by);
                listFilteredProducts(applyFilter(type, by, value));
                break;
            }
            case 0: {
                cout << "Returning to All Products Listng..." << endl;
                return;
            }
            default:
                cout << "Invalid Choice. Please try again!" << endl;
        }        
    }
}

vector<Product> applyFilter(int type, int by, float value) {
    vector<Product> filteredProducts;
    if (by == 2) {
        switch(type){
            case 1: {
                for (int i = 0; i < products.size(); i++) 
                    if (products[i].price <= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 2: {
                for (int i = 0; i < products.size(); i++) 
                    if (products[i].price >= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 3: {
                for (int i = 0; i < products.size(); i++) 
                    if (products[i].price == value)
                        filteredProducts.push_back(products[i]);
                break;
            }
        }
    }

    else if (by == 3) {
        switch (type) {
            case 1: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].rating <= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 2: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].rating >= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 3: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].rating == value)
                        filteredProducts.push_back(products[i]);
                break;
            }
        }
    }

    else if (by == 4) {
        switch (type) {
            case 1: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].stock <= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 2: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].stock >= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 3: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].stock == value)
                        filteredProducts.push_back(products[i]);
                break;
            }
        }
    }
    return filteredProducts;
}

vector<Product> applyFilter(int type, int by, string value) {
    vector<Product> filteredProducts;
    if (by == 1) {
        switch (type) {
            case 1: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].category <= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 2: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].category >= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 3: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].category == value)
                        filteredProducts.push_back(products[i]);
                break;
            }
        }
    }

    else {
        switch (type) {
            case 1: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].seller <= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 2: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].seller >= value)
                        filteredProducts.push_back(products[i]);
                break;
            }
            case 3: {
                for (int i = 0; i < products.size(); i++)
                    if (products[i].seller == value)
                        filteredProducts.push_back(products[i]);
                break;
            }
        }
    }
    return filteredProducts;
}

void listFilteredProducts(const vector<Product> &filteredProducts) {
    bool show = true;
    int input;
    while (true)
    {
        if (show) {
            cout << endl
                 << "ID\tCategory\tName\tPrice\tRating\tStock\tSeller" << endl;
            cout << "___________________________________________________________________________________________" << endl;
            cout << "___________________________________________________________________________________________" << endl;

            for (int i = 0; i < filteredProducts.size(); i++)
            {
                cout << filteredProducts[i].productID << "\t"
                     << filteredProducts[i].category << "\t"
                     << filteredProducts[i].name << "\t"
                     << filteredProducts[i].price << "\t"
                     << filteredProducts[i].rating << "\t"
                     << filteredProducts[i].stock << "\t"
                     << filteredProducts[i].seller << "\t" << endl;
                cout << "________________________________________________________________________________________" << endl;
            }
        }

        cout << endl << "Enter 1 to show details of a product" << endl;
        if (asAdmin)
            cout << "Enter 2 to Remove a Product" << endl;
        cout << "Enter 0 to return to Product Filtering Interface" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input)
        {
            case 1: {
                int id;
                id = getValidatedIntInput("Enter Product ID: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int index = Product::getProductByID(id);
                if (index == -1) {
                    cout << "No Product has the specified ID" << endl;
                    show = false;
                }
                else {
                    products[index].showDetails();
                    show = true;
                }
                break;
            }
            case 2: {
                if (asAdmin)
                {
                    int id = getValidatedIntInput("Enter the ID of the product you want to remove: ");
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    int index = Product::getProductByID(id);
                    if (index == -1) {
                        cout << "No Product has the specified ID" << endl;
                        show = false;
                    }
                    else {
                        admins[Admin::getAdminByID(cAdminID.value())].removeProduct(index); // .value accesses the Admin obj in the optional wrapper
                        show = true;
                    }
                }
                else {
                    cout << "Invalid choice. Please try Again!" << endl;
                    show = false;
                }
                break;
            }
            case 0: {
                cout << "Returning to Product Filtering Interface..." << endl;
                return;
            }
            default: {
                cout << "Invalid choice. Please try Again!" << endl;
                show = false;
            }
        }
    }
}

void searchInterface() {
    string term;
    cout << endl << "Enter the term you want to search for: " << endl;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, term);
    listSearchedProducts(searchFor(term));
    return;
}

vector<Product> searchFor (string &term) {
    vector<Product> searchedProducts;
    term = transformToLower(term); // from beginning to end of term apply tolower and
                                   // start storing result from beginning of the term
    for (int i = 0; i < products.size(); i++) {
        string lowerCategory = transformToLower(products[i].category);
        string lowerName = transformToLower(products[i].name);
        string lowerDescription = transformToLower(products[i].description);
        string lowerSeller = transformToLower(products[i].seller);

        if (
            lowerCategory.find(term) != string::npos ||
            lowerName.find(term) != string::npos ||
            lowerDescription.find(term) != string::npos ||
            lowerSeller.find(term) != string::npos ||
            to_string(products[i].productID).find(term) != string::npos ||
            to_string(products[i].price).find(term) != string::npos ||
            to_string(products[i].rating).find(term) != string::npos ||
            to_string(products[i].stock).find(term) != string::npos
        )
            searchedProducts.push_back(products[i]); 
    }
    return searchedProducts;
}

void listSearchedProducts(const vector<Product> &searchedProducts) {
    bool show = true;
    int input;
    while (true)
    {
        if (show) {
            cout << endl
                 << "ID\tCategory\tName\tPrice\tRating\tStock\tSeller" << endl;
            cout << "___________________________________________________________________________________________" << endl;
            cout << "___________________________________________________________________________________________" << endl;

            for (int i = 0; i < searchedProducts.size(); i++)
            {
                cout << searchedProducts[i].productID << "\t"
                     << searchedProducts[i].category << "\t"
                     << searchedProducts[i].name << "\t"
                     << searchedProducts[i].price << "\t"
                     << searchedProducts[i].rating << "\t"
                     << searchedProducts[i].stock << "\t"
                     << searchedProducts[i].seller << "\t" << endl;
                cout << "________________________________________________________________________________________" << endl;
            }
        }

        cout << endl << "Enter 1 to show details of a product" << endl;
        if (asAdmin)
            cout << "Enter 2 to Remove a Product" << endl;
        cout << "Enter 0 to return to All Products Listing" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input)
        {
            case 1: {
                int id;
                id = getValidatedIntInput("Enter Product ID: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int index = Product::getProductByID(id);
                if (index == -1) {
                    cout << "No product has the specified ID" << endl;
                    show = false;
                }
                else {
                    products[index].showDetails();
                    show = true;
                }
                break;
            }
            case 2: {
                if (asAdmin)
                {
                    int id = getValidatedIntInput("Enter the ID of the product you want to remove: ");
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    int index = Product::getProductByID(id);
                    if (index == -1) {
                        cout << "No Product has the specified ID" << endl;
                        show = false;
                    }
                    else {
                        admins[Admin::getAdminByID(cAdminID.value())].removeProduct(index); // .value accesses the Admin obj in the optional wrapper
                        show = true;
                    }
                }
                else {
                    cout << "Invalid choice. Please try Again!" << endl;
                    show = false;
                }
                break;
            }
            case 0: {
                cout << "Returning to All Products Listing..." << endl;
                return;
            }
            default: {
                cout << "Invalid choice. Please try Again!" << endl;
                show = false;
            }
        }
    }
}

string transformToLower(string &s) {
    string target = s;
    transform(target.begin(), target.end(), target.begin(), ::tolower);
    return target;
}
