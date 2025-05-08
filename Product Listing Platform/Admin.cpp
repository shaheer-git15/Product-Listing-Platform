#include "Admin.h"
#include "FileHandler.h"
#include "GLobals.h"
#include <algorithm>

using namespace std;

void Admin::signup(string &name, string &email, string &password) {
    this->adminID = generateUniqueAdminID();
    this->name = name;
    this->email = email;
    this->password = password;

    admins.push_back(*this);
    FileHandler::appendAdminData(*this);
}

void Admin::removeProduct(int &index) {
    int id = products[index].productID;
    string seller = products[index].seller;      
    products.erase(
        remove(products.begin(), products.end(), products[index]),
        products.end()
    );
    FileHandler::overwriteProductData(products);

    for (int i = 0; i < users.size(); i++) // Removing the ID of the removed product from user's listed products' IDs
        if (users[i].name == seller)
            for (int j = 0; j < users[i].prodIDs.size(); j++)
                if (users[i].prodIDs[j] == id)
                    users[i].prodIDs.erase(
                        remove(users[i].prodIDs.begin(), users[i].prodIDs.end(), id),
                        users[i].prodIDs.end()
                    );
    FileHandler::overwriteUserData(users);
}

void Admin::deactivateUser(int &index) {
    for (int j = 0; j < users[index].prodIDs.size(); j++) {    // Removing Products listed by user
        int prodIndex = Product::getProductByID(users[index].prodIDs[j]);
        removeProduct(prodIndex);
    }
    for (int j = 0; j < accounts.size(); j++) {       // Removing Bank Account of user
        if (users[index].userID == accounts[j].userID)
            accounts[j].removeAccount();
    }

    users.erase(
        remove(users.begin(), users.end(), users[index]),
        users.end()
    );


    FileHandler::overwriteProductData(products);
    FileHandler::overwriteUserData(users);
}

int Admin::generateUniqueAdminID() {
    int maxID = 0;

    for (int i = 0; i < admins.size(); i++)
    {
        if (admins[i].adminID > maxID)
        {
            maxID = admins[i].adminID;
        }
    }
    return maxID + 1;
}

int Admin::getAdminByID(int id) {
    for (int i = 0; i < admins.size(); i++)
        if (admins[i].adminID == id)
            return i;
    return -1;
}

    