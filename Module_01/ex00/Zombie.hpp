/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:04:25 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/16 14:47:33 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie
{
private :
	std::string _name;

public :
	Zombie();
	Zombie(std::string name);
	~Zombie();

	void announce() const;
};

Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif
