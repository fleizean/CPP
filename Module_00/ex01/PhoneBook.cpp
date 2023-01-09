/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:59:56 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/06 02:46:56 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int PhoneBook::getContactNum(void) const { return (contactNum_); }

int PhoneBook::addContact(void) 
{
    int i;
    static int k = 0;
    std::string str;

    if (contactNum_ == 8)
    {
        std::cout << "Phonebook is full!!" << std::endl;
        i = k;
        k++;
        if (k == 8)
            k = 0;
    }
    else
        i = contactNum_++;
    std::cout << std::endl;
    std::cout << "First Name : ";
    if (!(std::getline(std::cin, str)))
        return (ERROR);
    contact[i].setFirstName(str);
    
    std::cout << "Last Name : ";
    if (!(std::getline(std::cin, str)))
        return (ERROR);
    contact[i].setLastName(str);

    std::cout << "Nickname : ";
    if (!(std::getline(std::cin, str)))
        return (ERROR);
    contact[i].setNickname(str);

    std::cout << "Login : ";
    if (!(std::getline(std::cin, str)))
        return (ERROR);
    contact[i].setLogin(str);

    std::cout << "Email : ";
    if (!(std::getline(std::cin, str)))
        return (ERROR);
    contact[i].setEmailAddress(str);

    do
    {
        std::cout << "\033[31mWARNING >> Please write a phone number of ten lengths." << std::endl;
        std::cout << "\033[0mPhone Number : ";
        if (!(std::getline(std::cin, str)))
            return (ERROR);
    }
    while(str.length() != 10);
    contact[i].setPhoneNumber(str);

    return (SUCCESS);
}

int PhoneBook::searchContact(void)
{
    int i;
    
    if (getContactNum() == 0)
    {
        std::cout << "The PhoneBook is empty!" << std::endl;
        return (ERROR);
    }
    printAllContact();
    std::cout << std::endl;
    std::cout << "Select the index : " ;
    std::cin >> i;
    if (std::cin.eof())
        exit(1);
    if (std::cin.fail() || i <= 0 || i > 8)
    {
        std::cout << "Wrong input!" << std::endl;
        std::cin.clear();
        std::cin.ignore(MAX_INPUT_SIZE, '\n');
    }
    else
    {
        std::cin.ignore(MAX_INPUT_SIZE, '\n');
        PrintDetailContact(i);
    }
    return (SUCCESS);
}

std::string PhoneBook::cutLettersToTen(const std::string str) const
{
    std::string temp;

    if (str.length() > 10)
        temp = str.substr(0, 9) + ".";
    else
        temp = str;
    return (temp);
}

void PhoneBook::printAllContact(void) const
{
    std::cout << std::endl;
    std::cout << "──────────────────────────────────────────────────────" << std::endl;
    std::cout << std::setw(10) << "Index" << " | ";
    std::cout << std::setw(10) << "First Name" << " | ";
    std::cout << std::setw(10) << "Last Name" << " | ";
    std::cout << std::setw(10) << "Nickname" << std::endl;
    std::cout << "──────────────────────────────────────────────────────" << std::endl;

    for (int i = 1; i <= contactNum_; i++)
    {
        std::cout << std::setw(10) << i << " | ";
        std::cout << std::setw(10) << cutLettersToTen(contact[i - 1].getFirstName()) << " | ";
        std::cout << std::setw(10) << cutLettersToTen(contact[i - 1].getLastName()) << " | ";
        std::cout << std::setw(10) << cutLettersToTen(contact[i - 1].getNickname()) << std::endl;
        std::cout << "──────────────────────────────────────────────────────" << std::endl;
    }
}

void PhoneBook::PrintDetailContact(const int i) const
{
    Info dbInfo = contact[i - 1];

    std::cout << std::endl;
    std::cout << "────────────────────────Details────────────────────────" << std::endl;
    std::cout << "First Name : " << dbInfo.getFirstName() << std::endl;
    std::cout << "Last Name : " << dbInfo.getLastName() << std::endl;
    std::cout << "Nickname : " << dbInfo.getNickname() << std::endl;
    std::cout << "Login : " << dbInfo.getLogin() << std::endl;
    std::cout << "Email : " << dbInfo.getEmailAddress() << std::endl;
    std::cout << "Phone Number : " << dbInfo.getPhoneNumber() << std::endl;
    std::cout << "───────────────────────────────────────────────────────" << std::endl;
}