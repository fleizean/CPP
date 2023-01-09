/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:45:23 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/04 12:45:23 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
	Bureaucrat b1("b1", 150); // 150 yetki puanı 
	Bureaucrat b2("b2", 1); // 1 yetki puanı
	Bureaucrat b3("b3", 10); // 10 yetki puanı
	Bureaucrat b4(b3); // 10 yetki puanı

	std::cout << b1 << std::endl;
	std::cout << b2 << std::endl;
	std::cout << b3 << std::endl;
	std::cout << b4 << std::endl;
	std::cout << std::endl;

	try
	{

		std::cout << "=========Test 1=========" << std::endl;
		b1.decrementGrade(); // 150 + 1 = 151 hata durumu
		std::cout << b1 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		std::cout << "=========Test 2=========" << std::endl;
		b2.incrementGrade(); // 1 - 1 = 0 hata durumu
		std::cout << b2 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	std::cout << std::endl;

	try
	{
		std::cout << "=========Test 3=========" << std::endl;
		b3.incrementGrade(); // 10 - 1 = 9 sorun yok
		std::cout << b3 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		std::cout << "=========Test 4=========" << std::endl;
		b4.decrementGrade(); // 10 + 1 = 11 sorun yok
		std::cout << b4 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
