#include "Cart.h"
#include <iostream>
#include "Globals.h"
#include "Product.h"
#include <algorithm>

using namespace std;

void Cart::show()
{
    cout << "Products in Cart: " << endl << endl;

    cout << "ID\tCategory\tName\tPrice\tRating\tStock\tSeller" << endl;
    cout << "___________________________________________________________________________________________" << endl;
    cout << "___________________________________________________________________________________________" << endl;

    for (int i = 0; i < ids.size(); i++)
    {
        int index = Product::getProductByID(ids[i]);
        cout << products[index].productID << "\t"
             << products[index].category << "\t"
             << products[index].name << "\t"
             << products[index].price << "\t"
             << products[index].rating << "\t"
             << products[index].stock << "\t"
             << products[index].seller << "\t" << endl;
        cout << "________________________________________________________________________________________" << endl;
    }

    cout << "Total Price: " << this->totalPrice << "$ Only" << endl;
}

void Cart::removeFromCart(int &prodID)
{
    int i;
    for (i = 0; i < ids.size(); i++) {
        cout << ids[i] << endl;
        if (ids[i] == prodID)
        {
            this->totalPrice -= products[Product::getProductByID(ids[i])].price; 
            ids.erase(
                remove(ids.begin(), ids.end(), ids[i]),
                ids.end());
            cout << "Product removed from cart successfully!" << endl;
            break;
        }
    }
    if (i == ids.size())
        cout << "Your cart has no product with the specified ID" << endl;

    products[Product::getProductByID(prodID)].stock++;
}
