#pragma once
#include <string>
#include "Product.h"
#include "Cart.h"
#include <vector>

struct User
{
    int userID;
    std::string name;
    std::string email;
    std::string password;
    std::string status;
    std::vector<int> prodIDs;
    Cart cart;

    bool operator==(const User &other) const;
    void signup(std::string &name, std::string &email, std::string &password);
    void listProducts();
    void modifyProduct(Product &prod);
    void addProduct();
    void showCart();
    void removeProduct(Product &prod);
    static int generateUniqueUserID();
    static int getUserByID(int id);

};