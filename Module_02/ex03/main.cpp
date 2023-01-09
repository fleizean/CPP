/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:49:20 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/20 12:53:13 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int main(void)
{
	Point a1(8, 3);
	Point b1(5, 9);
	Point c1(1, 1);
	Point p1(4, 4);
	Point p2(4, 1);

	Point a2(5.5, -2.5);
	Point b2(2.5, -5.0);
	Point c2(1.5, -1.0);
	Point p3(3.5, -3.0);
	Point p4(5.0, -0.5);

	Fixed x1(8), y1(3);
	Fixed x2(5), y2(9);
	Fixed x3(1), y3(1);
	Fixed x4(4), y4(4);
	Fixed x5(4), y5(1);
	Point a3(x1, y1);
	Point b3(x2, y2);
	Point c3(x3, y3);
	Point p5(x4, y4);
	Point p6(x5, y5);

	if (bsp(a1, b1, c1, p1))
		std::cout << "p1 is in the triangle" << std::endl;
	else
		std::cout << "p1 is out of the triangle" << std::endl;
	if (bsp(a1, b1, c1, p2))
		std::cout << "p2 is in the triangle" << std::endl;
	else
		std::cout << "p2 is out of the triangle" << std::endl;
	
	if (bsp(a2, b2, c2, p3))
		std::cout << "p3 is in the triangle" << std::endl;
	else
		std::cout << "p3 is out of the triangle" << std::endl;
	if (bsp(a2, b2, c2, p4))
		std::cout << "p4 is in the triangle" << std::endl;
	else
		std::cout << "p4 is out of the triangle" << std::endl;

	if (bsp(a3, b3, c3, p5))
		std::cout << "p3 is in the triangle" << std::endl;
	else
		std::cout << "p3 is out of the triangle" << std::endl;
	if (bsp(a3, b3, c3, p6))
		std::cout << "p4 is in the triangle" << std::endl;
	else
		std::cout << "p4 is out of the triangle" << std::endl;

	return 0;
}
