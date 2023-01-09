/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:46:54 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:46:54 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() { }

Intern::~Intern() { }

Intern::Intern(const Intern& i)
{
	static_cast<void>(i);
}

Intern& Intern::operator=(const Intern& intern)
{
	static_cast<void>(intern);
	return *this;
}

Form* Intern::CreateShrubberyCreationForm(const std::string& target)
{
	std::cout << "Intern creates shrubbery creation form. (" << target << ')' << std::endl;
	return new ShrubberyCreationForm(target);
}

Form* Intern::CreateRobotomyForm(const std::string& target)
{
	std::cout << "Intern creates robotomy request form. (" << target << ')' << std::endl;
	return new RobotomyRequestForm(target);
}

Form* Intern::CreatePresidentialPardonForm(const std::string& target)
{
	std::cout << "Intern creates presidential pardon form. (" << target << ')' << std::endl;
	return new PresidentialPardonForm(target);
}

Form* Intern::makeForm(const std::string& name, const std::string& target)
{
	std::string form[3] = { "shrubbery creation", "robotomy request", "presidential pardon" };
	Form *(Intern::*func_ptr[3])(const std::string &target) =
		{ &Intern::CreateShrubberyCreationForm, &Intern::CreateRobotomyForm, &Intern::CreatePresidentialPardonForm };
	for (int i = 0 ; i < 3 ; i++)
	{
		if (form[i] == name)
			return (this->*func_ptr[i])(target);
	}
	std::cout << "No form exists for the given name." << std::endl;
	return (NULL);
}