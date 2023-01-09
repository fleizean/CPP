/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:12:54 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 14:47:37 by eyagiz           ###   ########.fr       */
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
