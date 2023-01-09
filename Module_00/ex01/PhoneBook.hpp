/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:44:58 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 15:24:13 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iomanip>
# include <iostream>
# include <string>
# include <cstring>
# include "Info.hpp"

# define SUCCESS 1
# define ERROR -1
# define MAX_INPUT_SIZE 100

class PhoneBook
{
private:
    int contactNum_;
    Info contact[8];

    std::string cutLettersToTen(const std::string str) const;

public:
    PhoneBook(void) : contactNum_(0){};
    int addContact(void);
    int searchContact(void);
    void printAllContact(void) const;
    void PrintDetailContact(const int i) const;
    int getContactNum(void) const;
};

#endif