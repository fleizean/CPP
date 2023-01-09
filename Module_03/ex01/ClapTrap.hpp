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

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
#include <iostream>

class ClapTrap
{
private:
	std::string _name;
	unsigned int _hitPoint;
	unsigned int _energyPoint;
	unsigned int _attackDamage;
public:
	ClapTrap();
	ClapTrap(std::string const& name);
	ClapTrap(const ClapTrap &clap);
	ClapTrap &operator=(const ClapTrap &clap);
	ClapTrap(std::string const& name, int hitPoints, int energyPoints,
           int attackDamage);
	~ClapTrap();

	//getters
	std::string const& getName() const;
	int getHitPoints() const;
	int getEnergyPoints() const;
	int getAttackDamage() const;

	//setters
    void setEnergyPoint();

	void attack(std::string const& enemy);
 	void takeDamage(unsigned int amount);
 	void beRepaired(unsigned int amount);

	//helper
	bool isAlive(void) const;
};

#endif