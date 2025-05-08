# pragma once

#include <string>

struct Admin
{
    int adminID;
    std::string name;
    std::string email;
    std::string password;

    void signup(std::string &name, std::string &email, std::string &password);
    void removeProduct(int &index);
    void deactivateUser(int &index);
    static int generateUniqueAdminID();
    static int getAdminByID(int id);
};