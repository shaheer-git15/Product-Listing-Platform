#include "Product.h"
#include "FileHandler.h"
#include "Globals.h"
#include "Cart.h"
#include <iostream>
#include <limits>

using namespace std;

bool Product::operator==(const Product &other) const
{
    return (productID == other.productID); // 2 products are same if their IDs are same
}

void Product::showDetails()
{
    cout << endl << "Product ID: " << this->productID << endl;
    cout << "Category: " << this->category << endl;
    cout << "Name: " << this->name << endl;
    cout << "Price: " << this->price << endl;
    cout << "Average Rating: " << this->rating << endl;
    cout << "Stock: " << this->stock << endl;
    cout << "Seller Name: " << this->seller << endl;
    cout << endl << "Description: " << endl << this->description << endl;
    cout << endl << "Reviews: " << endl;
    showReviews();
    cout << endl;

    int input;
    while (true)
    {
        cout << endl << "Enter 1 to rate this product" << endl;
        cout << "Enter 2 to submit a Review" << endl;
        if (asAdmin)
            cout << "Enter 3 to Remove this Product" << endl;
        if (!asAdmin)
            cout << "Enter 4 to add product to cart" << endl;
        cout << "Enter 0 to go back to previous choice" << endl << endl;

        input = getValidatedIntInput("Enter your Choice: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input)
        {
        case 1:
        {
            float rated;
            rated = getValidatedFloatInput("How much would you rate this product (0.0 to 5.0): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (rated >= 0.0 && rated <= 5.0)
            {
                this->rating = (this->rating + rated) / 2;
                FileHandler::overwriteProductData(products);
            }
            else
                cout << "Error: Invalid Rating entered! Rating must be between 0.0 and 5.0" << endl;
            break;
        }
        case 2:
        {
            string review;
            cout << "Please write a review for this product: ";
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, review);
            this->reviews.push_back(review);
            FileHandler::overwriteProductData(products);
            break;
        }
        case 3:
        {
            if (asAdmin)
            {
                int id = getValidatedIntInput("Enter ID of product you want to remove: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int index = Product::getProductByID(id);
                if (index == -1)
                    cout << "No Product has the specified ID" << endl;
                else
                    admins[Admin::getAdminByID(cAdminID.value())].removeProduct(index); // .value accesses the Admin obj in the optional wrapper
            }
            else
                cout << "Invalid choice. Please try Again!" << endl;
            break;
        }
        case 4:
        {
            if (!asAdmin)
            {
                addToCart(users[User::getUserByID(cUserID.value())].cart);
            }
            break;
        }
        case 0:
        {
            cout << "Returning to previous choice..." << endl;
            return;
        }
        default:
            cout << "Invalid Choice. Please try again!" << endl;
        }
    }
}

void Product::showReviews()
{
    for (int i = 0; i < this->reviews.size(); i++)
        cout << "Review " << i + 1 << ":\t" << this->reviews[i] << endl;
}

void Product::addToCart(Cart &cart) {
    if (this->stock > 0) {
        cart.ids.push_back(this->productID);
        cart.totalPrice += this->price;
        this->stock--;
        cout << "Product added to cart successfully!" << endl;
    }
    else
        cout << "Sorry! This product is currently out of stock!" << endl;
}

int Product::getProductByID(int id)
{
    for (int i = 0; i < products.size(); i++)
        if (products[i].productID == id)
            return i;
    return -1;
}

int Product::generateUniqueProductID()
{
    int maxID = 0;

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].productID > maxID)
        {
            maxID = products[i].productID;
        }
    }

    return maxID + 1;
}
