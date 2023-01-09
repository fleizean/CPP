/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:46:56 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:46:56 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
public:
    Intern();
    Intern(const Intern& i);
    ~Intern();
    Intern& operator=(const Intern& intern);
    
    Form* CreateShrubberyCreationForm(const std::string& target);
    Form* CreateRobotomyForm(const std::string& target);
    Form* CreatePresidentialPardonForm(const std::string& target);

    Form* makeForm(const std::string& type, const std::string& name);
};

#endif