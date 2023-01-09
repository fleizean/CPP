/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:59:17 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 15:59:18 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB
{
private :
	std::string _name;
	Weapon* _weapon;

public :
	HumanB();
	HumanB(std::string name);
	HumanB(std::string name, Weapon& weapon);
	~HumanB();

	void attack() const;
	void setWeapon(Weapon& weapon);
};

#endif
