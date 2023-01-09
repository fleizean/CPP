/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:47:41 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:47:41 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : Form() { }

ShrubberyCreationForm::~ShrubberyCreationForm() { }

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : Form(target, 145, 137) { }

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& s) : Form(s) { }

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& sform)
{
    Form::operator=(sform);
    return *this;
}

void ShrubberyCreationForm::execute(const Bureaucrat& b) const
{
    std::ofstream out;
    std::string ascii_trees = "                            '.,\n"
                              "                              'b      *\n"
                              "                               '$    #.\n"
                              "                                $:   #:\n"
                              "                                *#  @):\n"
                              "                                :@,@):   ,.**:'\n"
                              "                      ,         :@@*: ..**'\n"
                              "                       '#o.    .:(@'.@*'\n"
                              "                          'bq,..:,@@*'   ,*\n"
                              "                          ,p$q8,:@)'  .p*'\n"
                              "                         '    '@@Pp@@*'\n"
                              "                               Y7'.'\n"
                              "                             :@):.\n"
                              "                             .:@:'.\n"
                              "                           .::(@:.\n";
    if (!getSigned())
		throw NotSignedException();
	if (b.getGrade() > getGradeExec())
		throw GradeTooLowException();
    out.open(getName() + "_shrubbery", std::ofstream::out | std::ofstream::trunc);
    if (!out)
		throw FileErrorException();
    out << ascii_trees;
    out.close();
    std::cout << getName() << "_shrubbery file created." << std::endl;
}

