/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 00:17:01 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/30 00:17:01 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap def;
	ClapTrap c1("Clap1");
	ClapTrap c2("Clap2");
	ClapTrap c3(c1);
	ClapTrap c4 = c2;

	std::cout << std::endl;
	while (c1.isAlive() && c2.isAlive())
	{
		c1.attack("Clap2");
		c2.takeDamage(c1.getAttackDamage()); // Damage'i farklı verebiliriz.
		std::cout << std::endl;
	}
	std::cout << std::endl;
	def.beRepaired(10);
	std::cout << std::endl;
	
	return 0;
}
