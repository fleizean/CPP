/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:57:06 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 15:59:24 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon
{
private :
	std::string _type;

public :
	Weapon();
	Weapon(std::string type);
	~Weapon();

	const std::string& getType() const;
	void setType(std::string type);
};

#endif
