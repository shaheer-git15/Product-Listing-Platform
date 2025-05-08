#pragma once

#include <fstream>
#include "User.h"
#include "Product.h"
#include "Admin.h"
#include "Bank.h"
#include <vector>

class FileHandler
{
    static void userToCSV(std::fstream &stream, const User &user);
    static void productToCSV(std::fstream &stream, const Product &product);
    static void adminToCSV(std::fstream &stream, const Admin &admin);
    static void bankToCSV(std::fstream &stream, const Bank &account);

    public:
        static std::vector<User> readUserData();
        static std::vector<Product> readProductData();
        static std::vector<Admin> readAdminData();
        static std::vector<Bank> readBankData();

        static void appendUserData(User &newUser);
        static void appendProductData(Product &newProduct);
        static void appendAdminData(Admin &newAdmin);
        static void appendBankData(Bank &newAccount);

        static void overwriteUserData(std::vector<User> &users);
        static void overwriteProductData(std::vector<Product> &products);
        static void overwriteAdminData(std::vector<Admin> &admins);
        static void overwriteBankData(std::vector<Bank> &accounts);
};