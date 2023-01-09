/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:47:07 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:47:07 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : Form() { }

RobotomyRequestForm::~RobotomyRequestForm() { }

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) : Form(target, 72, 45) { }

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& r) : Form(r) { }

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& rform)
{
    Form::operator=(rform);
    return *this;
}

void RobotomyRequestForm::execute(const Bureaucrat& b) const
{
    if (!getSigned())
		throw NotSignedException();
	if (b.getGrade() > getGradeExec())
		throw GradeTooLowException();
    srand(time(NULL));
    std::cout << "Drrrrrrrrrrrr..." << std::endl;
    if (rand() % 2)
        std::cout << getName() << " has been robotomized successfully 50% of the time." << std::endl;
    else
        std::cout << getName() << " has been failed robotomize." << std::endl;
}

