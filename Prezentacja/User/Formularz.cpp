#include "Formularz.h"
#include <iostream>


void Form::getFullName()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    // your code here
}

void Form::getPassword()
{
    std::string password;
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    // your code here
}

void Form::getEmail()
{
    std::string email;
    std::cout << "Enter your email: ";
    std::getline(std::cin, email);

    // your code here
}

bool Form::validate(const std::string& str, const std::regex& reg)
{
    // your code here

    return false;
}

bool Form::validateIt(const std::string& str, const std::regex& reg)
{
    // your code here

    return false;
}

void Form::sentByPOSTMethod()
{
    if (!userName.empty() && !userPassword.empty() && !userEmail.empty()) {
        std::cout << "Form has been sent successfully.\n";
        return;
    }

    std::cout << "Form has some issues, contact your administrator for more information...\n";
}
