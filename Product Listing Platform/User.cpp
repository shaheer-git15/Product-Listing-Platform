#include "User.h"
#include <iostream>
#include "FileHandler.h"
#include "Globals.h"
#include <algorithm>
#include <limits>

using namespace std;

bool User::operator==(const User &other) const
{
    return (userID == other.userID); // 2 products are same if their IDs are same
}

void User::signup(string &name, string &email, string &password)
{
    this->userID = generateUniqueUserID();
    this->name = name;
    this->email = email;
    this->password = password;
    this->status = "Active";
    this->prodIDs.clear();

    users.push_back(*this);
    FileHandler::appendUserData(*this);
}


void User::listProducts()
{   
    if (this->prodIDs.size() == 0)
    {
        cout << "You have not listed any products yet!" << endl;
    }

    bool show = true;
    int input;
    while (true) {
        if (show) {
            cout << endl << "Products listed by " << this->name << ":" << endl;
            cout << endl << "ID\tCategory\tName\tPrice\tRating\tStock\tSeller" << endl;
            cout << "___________________________________________________________________________________________" << endl;
            cout << "___________________________________________________________________________________________" << endl;
            for (int i = 0; i < products.size(); i++)
            {
                if (products[i].seller == this->name) {
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
        }

        if (!asAdmin)
        {            
            cout << endl << "Enter 1 to modify a product" << endl;
            cout << "Enter 2 to add a new product" << endl;
            cout << "Enter 3 to remove a product" << endl;
            cout << "Enter 0 to go back to Dashboard" << endl;

            input = getValidatedIntInput("Enter your Choice: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (input)
            {
                case 1:
                {
                    int id;
                    id = getValidatedIntInput("Enter ID of the product you want to modify: ");
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    int i = Product::getProductByID(id);
                    if (id == -1 || products[i].seller != this->name) {
                        cout << "None of your products has the specified ID" << endl;
                        show = false;
                    }
                    else {
                        modifyProduct(products[i]);
                        show = true;
                    }
                    break;
                }
                case 2:
                {
                    addProduct();
                    show = true;
                    break;
                }
                case 3:
                {
                    int id;
                    id = getValidatedIntInput("Enter ID of the product you want to remove: ");
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    int i = Product::getProductByID(id);
                    if (id == -1 || products[i].seller != this->name) {
                        cout << "None of your products has the specified ID" << endl;
                        show = false;
                    }
                    else {
                        removeProduct(products[i]);
                        show = true;
                    }
                    break;
                }
                case 0:
                {
                    cout << "Returning to your dashboard..." << endl;
                    return;
                }
                default:
                {
                    show = false;
                    cout << "Invalid choice. Please Try Again!" << endl;
                }
            }
            
        }

        else
        {
            cout << endl << "Enter 0 to return to All User Listing: " << endl;

            input = getValidatedIntInput("Enter here: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (input)
            {
                case 0:
                {
                    cout << "Returning to All User Listing..." << endl;
                    return;
                }
                default: {
                    show = false;
                    cout << "Invalid Input! Please Try Again." << endl;
                }
            }
        }
    }
}

void User::modifyProduct(Product &prod)
{
    cout << endl << "Enter the new Category of the product: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, prod.category);
    cout << "Enter the new Name of the product: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, prod.name);
    float price;
    do
    {
        price = getValidatedFloatInput("Enter the new Price of the product: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (price < 0)
            cout << "Price cannot be negative. Please enter a valid price!" << endl;
        else
            prod.price = price;
    } while (price < 0);
    cout << "Enter the new Description of the product: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, prod.description);
    int stock;
    do
    {
        stock = getValidatedFloatInput("Enter the new Stock of the product: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (stock < 0)
            cout << "Stock cannot be negative. Please enter a valid stock!" << endl;
        else
            prod.stock = stock;
    } while (stock < 0);

    cout << "Product modified successfully!" << endl;
    FileHandler::overwriteProductData(products);
}

void User::addProduct()
{
    Product newProd;
    cout << endl << "Enter the Category of the new product: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newProd.category);
    cout << "Enter the Name of the new product: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newProd.name);
    float price;
    do
    {
        price = getValidatedFloatInput("Enter the new Price of the product: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (price < 0)
            cout << "Price cannot be negative. Please enter a valid price!" << endl;
        else
            newProd.price = price;
    } while (price < 0);
    cout << "Enter the Description of the new product: ";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newProd.description);
    int stock;
    do
    {
        stock = getValidatedFloatInput("Enter the new Stock of the product: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (stock < 0)
            cout << "Stock cannot be negative. Please enter a valid stock!" << endl;
        else
            newProd.stock = stock;
    } while (stock < 0);
    newProd.productID = Product::generateUniqueProductID();
    newProd.rating = 0.0;
    newProd.reviews.clear();
    newProd.seller = this->name;

    cout << "Product added successfully!" << endl;
    products.push_back(newProd);
    FileHandler::appendProductData(newProd);

    this->prodIDs.push_back(newProd.productID);
    FileHandler::overwriteUserData(users);
}

void User::showCart()
{
    this->cart.show();

    if (this->cart.ids.size() == 0)
    {
        cout << "Your cart is empty!" << endl;
        return;
    }

    int input;
    while (true)
    {
        cout << endl << "Enter 1 to remove a product from cart" << endl;
        cout << "Enter 2 to cash out" << endl;
        cout << "Enter 0 to go back to your Dashboard" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input)
        {
        case 1:
        {
            int id = getValidatedIntInput("Enter ID of the Product you want to remove from cart: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            this->cart.removeFromCart(id);
            this->cart.show();
            break;
        }
        case 2:
        {
            Bank::checkForAccountNumber(this->userID);
            this->cart.show();
            break;
        }
        case 0:
        {
            cout << "Returning to your Dashboard..." << endl;
            return;
        }
        default:
            cout << "Invalid Choice. Please Try Again!" << endl;
        }
    }
}

void User::removeProduct(Product &prod)
{
    products.erase(
        remove(products.begin(), products.end(), prod), // remove iterates from begin to end and returns an iterator
                                                        // pointing to desired prod after pushing it to end of vector
        products.end()                                  // erase then iterates from that point to end and erases everything in its path
    );

    this->prodIDs.erase( // Removing that product id from current users listed products
        remove(this->prodIDs.begin(), this->prodIDs.end(), prod.productID),
        this->prodIDs.end());

    cout << "Product removed successfully!" << endl;
    FileHandler::overwriteUserData(users);
    FileHandler::overwriteProductData(products);
}

int User::generateUniqueUserID()
{
    int maxID = 0; 

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].userID > maxID)
        {
            maxID = users[i].userID; 
        }
    }

    return maxID + 1;    
}

int User::getUserByID(int id)
{
    for (int i = 0; i < products.size(); i++)
        if (products[i].productID == id)
            return i;
    return -1;
}
