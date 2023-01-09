/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:45:34 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:45:34 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
    const std::string _name;
    bool _signed;
    const int _grade_sign;
    const int _grade_exec;
public:
    Form();
    Form(const std::string& name, const int& grade_sign, const int& grade_exec);
    Form(const Form& f);
    ~Form();
    Form& operator=(const Form& f);

    const std::string getName() const;
    bool getSigned() const;
    int getGradeSign() const;
    int getGradeExec() const;

    void beSigned(Bureaucrat b);

    class GradeTooHighException : public std::exception
	{
	public:
		const char* what(void) const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char* what(void) const throw();
	};
    class AlreadySignedException : public std::exception
    {
    public:
        const char* what(void) const throw();
    };
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif