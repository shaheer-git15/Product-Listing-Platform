#pragma once
#include <vector>

struct Cart
{
    std::vector<int> ids; 
    double totalPrice = 0;

    void show();
    void removeFromCart(int &prodID);
};