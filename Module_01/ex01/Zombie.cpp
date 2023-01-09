/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:07:33 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 15:07:34 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() : _name("")
{ }

Zombie::Zombie(std::string name) : _name(name)
{ }

Zombie::~Zombie()
{
	std::cout << _name << " zombie destroyed." << std::endl;
}

void Zombie::announce() const
{
	std::cout << _name << " : BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setname(std::string name)
{
	_name = name;
}
