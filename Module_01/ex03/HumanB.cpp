/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:59:09 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 15:59:10 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{ }

HumanB::HumanB(std::string name, Weapon& weapon) : _name(name), _weapon(&weapon)
{ }

HumanB::~HumanB()
{ }

void HumanB::attack() const
{
	if (_weapon == NULL)
		std::cout << _name << " has no weapon" << std::endl;
	else
		std::cout << _name << " attacks with thier " << _weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon& weapon)
{
	_weapon = &weapon;
}