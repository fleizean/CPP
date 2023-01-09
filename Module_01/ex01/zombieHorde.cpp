/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:08:12 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 15:38:31 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
	if (N <= 0)
	{
		std::cout << "Parameter N is invalid" << std::endl;
		return NULL;
	}
	Zombie* horde = new Zombie[N]; // heap
	for (int i = 0; i < N; i++)
		horde[i].setname(name);
	return horde;
}
