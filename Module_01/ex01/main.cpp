/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:09:05 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/06 00:06:21 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	Zombie *family = zombieHorde(5, "family"); // [single to multiples allocation]

	for (int i = 0; i < 5; i++)
		family[i].announce();
	delete []family;
}
