/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:47:29 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:47:29 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
Bureaucrat b1("b1", 1);
    Bureaucrat b2("b2", 50);
    Bureaucrat b3("b3", 150);

    std::cout << "===========ShrubberyCreationForm Success Test===========" << std::endl;
    ShrubberyCreationForm s1("Shrubbery");
    b1.signForm(s1);
    //b1.executeForm(s1);
    b1.signForm(s1);
    std::cout << std::endl;
    std::cout << s1 << std::endl;
    std::cout << std::endl << std::endl;
}
