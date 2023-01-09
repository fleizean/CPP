/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:59:20 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/19 13:00:51 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club); // object oluşturulurken silahı ile birlikte oluşturulur
		bob.attack(); // 1 cons for weapon
		club.setType("some other type of club");
		bob.attack();
	}
	{	
		Weapon club = Weapon("crude frozened club");
		HumanB jim("Jim");
		jim.setWeapon(club); // 2 cons for set weapon
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	return 0;
}
