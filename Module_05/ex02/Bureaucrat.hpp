/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:47:21 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:47:21 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <exception>
#include <string>

#include "Form.hpp"

#define GRADE_MAX 1
#define GRADE_MIN 150

class Form;

class Bureaucrat
{
private:
    const std::string _name;
    int _grade;
public:
    Bureaucrat();
    Bureaucrat(std::string name, int grade);
    Bureaucrat(const Bureaucrat& src);
    ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& bcrat);

    //getter
    const std::string getName() const;
    int getGrade() const;

    void incrementGrade(); // azalt
    void decrementGrade(); // arttır

    void signForm(Form& form) const;

    void executeForm(const Form& form) const;

    // hata yakalamak için tanımlamalar
    class GradeTooHighException : public std::exception
    {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
    public:
        const char* what() const throw();
    };
    
};

std::ostream& operator<<(std::ostream& o, const Bureaucrat& b);

#endif