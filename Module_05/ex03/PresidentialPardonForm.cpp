/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:47:02 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:47:02 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : Form() { }

PresidentialPardonForm::~PresidentialPardonForm() { }

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) : Form(target, 25, 5) { }

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& p) : Form(p) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& pform)
{
    Form::operator=(pform);
    return *this;
}

void PresidentialPardonForm::execute(const Bureaucrat& b) const
{
    if(!getSigned())
        throw NotSignedException();
    if(b.getGrade() > getGradeExec())
        throw GradeTooLowException();
    std::cout << getName() << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}