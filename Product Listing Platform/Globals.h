#pragma once
#include <vector>
#include <string>
#include <optional>
#include <functional>

class User;
class Product;
class Admin;
class Bank;

extern std::vector<User> users;       
extern std::vector<Product> products; 
extern std::vector<Admin> admins;     
extern std::vector<Bank> accounts;    
extern bool asAdmin;             
extern std::optional<int> cAdminID;  
extern std::optional<int> cUserID;     

float getValidatedFloatInput(const std::string &prompt);
int getValidatedIntInput(const std::string &prompt);
