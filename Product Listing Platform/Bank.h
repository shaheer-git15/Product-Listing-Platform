#pragma once

#include <string>

struct Bank
{
    int userID;
    std::string cardNumber;
    double balance;

    bool operator==(const Bank &other) const; 
    void deposit();
    static void checkForAccountNumber(int &IDforCheck);
    void bankSignup(int &userID);
    void bankLogin();
    void confirmPurchase();
    void removeAccount();
};