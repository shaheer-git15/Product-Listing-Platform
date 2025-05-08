#pragma once
#include <vector>
#include <string>

struct Cart;

struct Product
{
    int productID;
    std::string category;
    std::string name;
    float price;
    float rating;
    std::vector<std::string> reviews;
    std::string description;
    int stock;
    std::string seller;

    bool operator==(const Product &other) const;
    void showDetails();
    void showReviews();
    void addToCart(Cart &cart);
    static int getProductByID(int id);
    static int generateUniqueProductID();
};