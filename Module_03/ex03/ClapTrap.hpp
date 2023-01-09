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
	int _hitPoint;
	int _energyPoint;
	int _attackDamage;
public:
	ClapTrap();
	ClapTrap(const ClapTrap &clap);
	ClapTrap(std::string const& name);
	ClapTrap(std::string const& name, int hitPoints, int energyPoints, int attackDamage);
	ClapTrap(int hitPoints, int energyPoints, int attackDamage);

	//assignment operator
	ClapTrap &operator=(const ClapTrap &clap);
	
	//destructor
	virtual ~ClapTrap();

	//getters
	std::string const& getName() const;
	int getHitPoints() const;
	int getEnergyPoints() const;
	int getAttackDamage() const;

	//setters
    void decrEnergyPoint();
	void setHitPoints(int amount);
  	void setEnergyPoints(int amount);
  	void setAttackDamage(int amount);

	// actions
	void attack(std::string const& enemy);
 	void takeDamage(unsigned int amount);
 	void beRepaired(unsigned int amount);

	//helper
	bool isAlive(void) const;
};

#endif