#include "FileHandler.h"
#include <iostream>
#include <sstream>


using namespace std;

void FileHandler::userToCSV(fstream &stream, const User &user)
{
    stream << user.userID << ","
            << user.name << ","
            << user.email << ","
            << user.password << ","
            << user.status << ",[";

    if (!user.prodIDs.empty())
    {
        for (int i = 0; i < user.prodIDs.size() - 1; i++)
            stream << user.prodIDs[i] << ",";
        stream << user.prodIDs.back();
    }
    stream << "]\n";
}

void FileHandler::productToCSV(fstream &stream, const Product &product)
{
    stream << product.productID << ","
            << product.category << ","
            << product.name << ","
            << product.price << ","
            << product.rating << ",[";

    if (!product.reviews.empty())
    {
        for (int i = 0; i < product.reviews.size() - 1; i++)
            stream << product.reviews[i] << "*";
        stream << product.reviews.back();
    }
    stream << "],";

    stream << product.description << "|,"
            << product.stock << ","
            << product.seller << "\n";
}

void FileHandler::adminToCSV(fstream &stream, const Admin &admin)
{
    stream << admin.adminID << ","
            << admin.name << ","
            << admin.email << ","
            << admin.password << "\n";
}

void FileHandler::bankToCSV(fstream &stream, const Bank &account)
{
    stream << account.userID << ","
            << account.cardNumber << ","
            << account.balance << "\n";
}

vector<User> FileHandler::readUserData()
{

    vector<User> users;

    fstream user_f("user_dataset.csv", ios::in);
    if (!user_f.is_open())
    {
        cerr << "Failed to open User Datset." << endl;
        throw runtime_error("An Unexpected Backend Error Occured. (Could not open User Dataset!)");
    }
    else
    {
        string row;
        getline(user_f, row);        // Skipping header row
        while (getline(user_f, row)) // Reading each row one by one
        {
            User user;
            stringstream ss(row); // Converting each row to a stream
            string attrs;         // Declaring a temporary string to store each attribute using getline
            getline(ss, attrs, ',');
            user.userID = stoi(attrs);
            getline(ss, attrs, ',');
            user.name = attrs;
            getline(ss, attrs, ',');
            user.email = attrs;
            getline(ss, attrs, ',');
            user.password = attrs;
            getline(ss, attrs, ',');
            user.status = attrs;
            getline(ss, attrs, '[');
            getline(ss, attrs, ']'); // Now attrs is storing the string between []

            string tempProdID;
            stringstream ss_prodID(attrs);                // Converting the string in [] to stream
            while (getline(ss_prodID, tempProdID, ','))   // splitting the product IDs by ','
                user.prodIDs.push_back(stoi(tempProdID)); // and storing them in the productID vector

            users.push_back(user);
        }
        user_f.close();
    }
    return users;
}

vector<Product> FileHandler::readProductData()
{

    vector<Product> products;

    fstream product_f("unique_product_listing_dataset (1).csv", ios::in);
    if (!product_f.is_open())
    {
        cerr << "Failed to Open Product Listing Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Product Listing Dataset!)");
    }
    else
    {
        string row;
        getline(product_f, row);        // Skipping header row
        while (getline(product_f, row)) // Reading each row one by one
        {
            Product product;
            stringstream ss(row); // Converting each row to a stream
            string attrs;         // Declaring a temporary string to store each attribute using getline
            getline(ss, attrs, ',');
            product.productID = stoi(attrs);
            getline(ss, attrs, ',');
            product.category = attrs;
            getline(ss, attrs, ',');
            product.name = attrs;
            getline(ss, attrs, ',');
            product.price = stof(attrs);
            getline(ss, attrs, ',');
            product.rating = stof(attrs);
            getline(ss, attrs, '[');
            getline(ss, attrs, ']'); // Now attrs is storing the string between []

            string tempReviews;
            stringstream ss_reviews(attrs);               // Converting the string in [] to stream
            while (getline(ss_reviews, tempReviews, '*')) // splitting the Reviews by ','
                product.reviews.push_back(tempReviews);   // and storing them in the Reviews vector

            getline(ss, attrs, ',');
            getline(ss, attrs, '|');
            product.description = attrs;
            getline(ss, attrs, ','); // Don't want to store the value (null) b/w "$" and next ","
            getline(ss, attrs, ',');
            product.stock = stoi(attrs);
            getline(ss, attrs);
            product.seller = attrs;

            products.push_back(product);
        }
        product_f.close();
    }
    return products;
}

vector<Admin> FileHandler::readAdminData()
{

    vector<Admin> admins;

    fstream admin_f("admins_test_dataset.csv", ios::in);
    if (!admin_f.is_open())
    {
        cerr << "Failed to Open Admin Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Admin Dataset!)");
    }
    else
    {
        string row;
        getline(admin_f, row);
        while (getline(admin_f, row))
        {
            Admin admin;
            string attrs;
            stringstream ss(row);

            getline(ss, attrs, ',');
            admin.adminID = stoi(attrs);
            getline(ss, attrs, ',');
            admin.name = attrs;
            getline(ss, attrs, ',');
            admin.email = attrs;
            getline(ss, attrs);
            admin.password = attrs;

            admins.push_back(admin);
        }
        admin_f.close();
    }
    return admins;
}

vector<Bank> FileHandler::readBankData()
{

    vector<Bank> accounts;

    fstream bank_f("bank_test_dataset.csv", ios::in);
    if (!bank_f.is_open())
    {
        cerr << "Failed to Open Bank Accounts Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Bank Accounts Dataset!)");
    }
    else
    {
        string row;
        getline(bank_f, row);
        while (getline(bank_f, row))
        {
            Bank account;
            string attrs;
            stringstream ss(row);

            getline(ss, attrs, ',');
            account.userID = stoi(attrs);
            getline(ss, attrs, ',');
            account.cardNumber = attrs;
            getline(ss, attrs);
            account.balance = stod(attrs);

            accounts.push_back(account);
        }
        bank_f.close();
    }
    return accounts;
}

void FileHandler::appendUserData(User &newUser)
{
    fstream user_f("user_dataset.csv", ios::app);
    if (!user_f.is_open())
    {
        cerr << "Failed to open User Datset." << endl;
        throw runtime_error("An Unexpected Backend Error Occured. (Could not open User Dataset!)");
    }
    else
    {
        userToCSV(user_f, newUser);
        user_f.close();
    }
}

void FileHandler::appendProductData(Product &newProduct)
{
    fstream product_f("unique_product_listing_dataset (1).csv", ios::app);
    if (!product_f.is_open())
    {
        cerr << "Failed to Open Product Listing Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Product Listing Dataset!)");
    }
    else
    {
        productToCSV(product_f, newProduct);
        product_f.close();
    }
}

void FileHandler::appendAdminData(Admin &newAdmin)
{
    fstream admin_f("admins_test_dataset.csv", ios::app);
    if (!admin_f.is_open())
    {
        cerr << "Failed to Open Admin Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Admin Dataset!)");
    }
    else
    {
        adminToCSV(admin_f, newAdmin);
        admin_f.close();
    }
}

void FileHandler::appendBankData(Bank &newAccount)
{
    fstream bank_f("bank_test_dataset.csv", ios::app);
    if (!bank_f.is_open())
    {
        cerr << "Failed to Open Bank Accounts Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Bank Accounts Dataset!)");
    }
    else
    {
        bankToCSV(bank_f, newAccount);
        bank_f.close();
    }
}

void FileHandler::overwriteUserData(vector<User> &users)
{
    fstream user_f("user_dataset.csv", ios::out | ios::trunc);
    if (!user_f.is_open())
    {
        cerr << "Failed to open User Datset." << endl;
        throw runtime_error("An Unexpected Backend Error Occured. (Could not open User Dataset!)");
    }
    else
    {
        user_f << "UserID,UserName,UserEmail,UserPassword,UserStatus,UserProductsID\n"; // Rewriting the Header Row
        for (int i = 0; i < users.size(); i++)
            userToCSV(user_f, users[i]);
        user_f.close();
    }
}

void FileHandler::overwriteProductData(vector<Product> &products)
{
    fstream product_f("unique_product_listing_dataset (1).csv", ios::out | ios::trunc);
    if (!product_f.is_open())
    {
        cerr << "Failed to Open Product Listing Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Product Listing Dataset!)");
    }
    else
    {
        product_f << "ProductID,Category,ProductName,Price,Rating,Reviews,Description,InStock,ListedBy\n"; // Rewriting Headers
        for (int i = 0; i < products.size(); i++)
            productToCSV(product_f, products[i]);
        product_f.close();
    }
}

void FileHandler::overwriteAdminData(vector<Admin> &admins)
{
    fstream admin_f("admins_test_dataset.csv", ios::out | ios::trunc);
    if (!admin_f.is_open())
    {
        cerr << "Failed to Open Admin Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Admin Dataset!)");
    }
    else
    {
        admin_f << "AdminID,AdminName,AdminEmail,AdminPassword\n";
        for (int i = 0; i < admins.size(); i++)
            adminToCSV(admin_f, admins[i]);
        admin_f.close();
    }
}

void FileHandler::overwriteBankData(vector<Bank> &accounts)
{
    fstream bank_f("bank_test_dataset.csv", ios::out | ios::trunc);
    if (!bank_f.is_open())
    {
        cerr << "Failed to Open Bank Accounts Dataset" << endl;
        throw runtime_error("An Unexpected Backend Error Occurred. (Could not open Bank Accounts Dataset!)");
    }
    else
    {
        bank_f << "UserID,CardNumber,Balance\n";
        for (int i = 0; i < accounts.size(); i++)
            bankToCSV(bank_f, accounts[i]);
        bank_f.close();
    }
}

