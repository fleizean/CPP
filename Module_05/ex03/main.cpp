/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:46:59 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:46:59 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

int main(void)
{
	Intern someRandomIntern;
	Form* rrf;

	std::cout << "===========ShrubberyCreationForm Creation Test===========" << std::endl;
	rrf = someRandomIntern.makeForm("shrubbery creation", "Bender");
	delete rrf;
	std::cout << std::endl;

	std::cout << "============RobotomyRequestForm Creation Test============" << std::endl;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	delete rrf;
	std::cout << std::endl;

	std::cout << "===========PresidentialPardonForm Creation Test===========" << std::endl;
	rrf = someRandomIntern.makeForm("presidential pardon", "Bender");
	delete rrf;
	std::cout << std::endl;

	std::cout << "===============UndefinedForm Creation Test===============" << std::endl;
	rrf = someRandomIntern.makeForm("undefined", "Bender");
	delete rrf;
	std::cout << std::endl;
	
	return 0;
}
