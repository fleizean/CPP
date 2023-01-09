/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:09:53 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/19 12:55:17 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	Zombie dad = Zombie("Daddy"); // stack area
	Zombie* mom = newZombie("Mommy"); // heap area

	dad.announce();
	mom->announce();
	randomChump("Brother");

	delete mom;
}
