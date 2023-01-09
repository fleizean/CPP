/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:59:13 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/17 16:55:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanA
{
private :
	std::string _name;
	Weapon& _weapon;

public :
	HumanA();
	HumanA(std::string name, Weapon& weapon); // HumanA oluşturulduğunda parametre olarak silah aldığı için ya bir işaretçi ya da bir referans kullanılabilir.
	~HumanA();

	void attack() const;
};

#endif
