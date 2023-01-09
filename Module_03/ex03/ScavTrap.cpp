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

#include "ScavTrap.hpp"

/* ************************************************************************** */
/* CONSTRUCTORS                                                               */
/* ************************************************************************** */

ScavTrap::ScavTrap::ScavTrap() : ClapTrap("unnamed", 100, 50, 20)
{
    guard_mode = false;
    setHitPoints(100);
    setEnergyPoints(50);
    setAttackDamage(20);
    std::cout << "ScavTrap default constructor called" << std::endl;
    return;
}

ScavTrap::ScavTrap::ScavTrap(std::string const& name) : ClapTrap(name, 100, 50 , 20)
{
    guard_mode = false;
    setHitPoints(100);
    setEnergyPoints(50);
    setAttackDamage(20);
    std::cout << "ScavTrap parametric constructor called for " << getName() << std::endl;
    return;
}

ScavTrap::ScavTrap(ScavTrap const& src) : ClapTrap(src)
{
    guard_mode = src.guard_mode;
    std::cout << "ScavTrap copy constructor called for " << getName() <<std::endl;
    return;
}

/* ************************************************************************** */
/* ASSIGNMENT OPERATOR                                                        */
/* ************************************************************************** */

ScavTrap& ScavTrap::operator=(ScavTrap const& scav)
{
    std::cout << "ScavTrap assignment operator overload called for " << getName() << std::endl;
    ClapTrap::operator=(scav); // ClapTrapin de aynısını oluşturması için onun copy assignment'ına yolluyorum
    guard_mode = scav.guard_mode;
    return *this;
}

/* ************************************************************************** */
/* DESTRUCTOR                                                                 */
/* ************************************************************************** */

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap destructor called for " << getName() << std::endl;
}

/* ************************************************************************** */
/* ACTIONS                                                                    */
/* ************************************************************************** */

void ScavTrap::attack(const std::string enemy)
{
    if(!isAlive())
        return;
    std::cout << "ScavTrap " << getName() << " attacks " << enemy << ", causing " << getAttackDamage();
    decrEnergyPoint();
    std::cout << " ScavTrap " << getName() << " attacks " << enemy << ", causing " << getAttackDamage();
    std::cout << " of damage! ScavTrap " << getName() << " has " << getEnergyPoints() << " energy";
    std::cout << " left." << std::endl;
}

void ScavTrap::guardGate(void)
{
	if (getHitPoints() > 0)
	{
		guard_mode = true;
		std::cout << "ScavTrap " << getName() << " is now in Gate keeper mode!" << std::endl;
	}
	else
		std::cout << "ScavTrap " << getName() << " cannot enter Gate keeper mode because " << getName() << " is dead!" << std::endl;
}