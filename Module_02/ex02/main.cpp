/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:50:52 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/20 12:50:52 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void) 
{
	Fixed a;
	Fixed const b(Fixed( 5.05f ) * Fixed( 2 ));  // buranın sonucu 10.1 gibi bir şey dönüyor 
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << " b value"<< std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	return 0;
}