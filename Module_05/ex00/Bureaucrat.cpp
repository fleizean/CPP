/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:45:16 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:45:16 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() { std::cout << "Default constructor called" << std::endl; }

Bureaucrat::~Bureaucrat() { std::cout << "Destructor called" << std::endl; }

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name), _grade(grade)
{
    if(_grade < GRADE_MAX)
        throw Bureaucrat::GradeTooHighException();
    else if(_grade > GRADE_MIN)
        throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& src) : _name(src.getName()), _grade(src.getGrade())
{
    if(_grade < GRADE_MAX)
        throw Bureaucrat::GradeTooHighException();
    else if(_grade > GRADE_MIN)
        throw Bureaucrat::GradeTooLowException();
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& bcrat)
{
    if (this != &bcrat)
    {
        *const_cast<std::string*>(&_name) = bcrat.getName();
        _grade = bcrat.getGrade();
    }
    return *this;
}

// Getter
const std::string Bureaucrat::getName(void) const { return _name; }

int Bureaucrat::getGrade(void) const { return _grade; }

// increment decrement
void Bureaucrat::incrementGrade(void)
{
    if (_grade - 1 < GRADE_MAX)
        throw Bureaucrat::GradeTooHighException();
    _grade--;
}

void Bureaucrat::decrementGrade(void)
{
    if (_grade + 1 > GRADE_MIN)
        throw Bureaucrat::GradeTooLowException();
    _grade++;
}

const char* Bureaucrat::GradeTooHighException::what(void) const throw() { return "Your grade too high."; }

const char* Bureaucrat::GradeTooLowException::what(void) const throw() { return "Your grade too low."; }

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
    os << b.getName() << ", bureaucrat grade " << b.getGrade();
    return os;
}