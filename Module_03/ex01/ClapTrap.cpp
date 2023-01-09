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

#include "ClapTrap.hpp"

/* ************************************************************************** */
/* CONSTRUCTORS                                                               */
/* ************************************************************************** */

ClapTrap::ClapTrap() : _name("unnamed ClapTrap"), _hitPoint(10), _energyPoint(10), _attackDamage(0)
{
    std::cout << "Default constructor called" << std::endl;
    return;
}

ClapTrap::ClapTrap(ClapTrap const &clap)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = clap;
    return;
}

ClapTrap::ClapTrap(std::string const& name) : _name(name), _hitPoint(10), _energyPoint(10), _attackDamage(0)
{
    std::cout << "String constructor called" << std::endl;
    return;
}

ClapTrap::ClapTrap(std::string const& name, int hitPoints, int energyPoints,
                   int attackDamage) : _name(name), _hitPoint(hitPoints), _energyPoint(energyPoints), _attackDamage(attackDamage) 
{
    std::cout << "ClapTrap parametric constructor called (string + int + int + "
               "int) for " << _name << std::endl;
    return;
}

/* ************************************************************************** */
/* ASSIGNMENT OPERATOR                                                        */
/* ************************************************************************** */

ClapTrap& ClapTrap::operator=(const ClapTrap &clap)
{
    _name = clap.getName();
    _hitPoint = clap.getHitPoints();
    _energyPoint = clap.getEnergyPoints();
    _attackDamage = clap.getAttackDamage();
    std::cout << "ClapTrap Copy assignment operator : " << _name << std::endl;
    return *this;
}

/* ************************************************************************** */
/* DESTRUCTOR                                                                 */
/* ************************************************************************** */

ClapTrap::~ClapTrap() 
{
    std::cout << "Destructor called" << std::endl; 
}

/* ************************************************************************** */
/* GETTERS                                                                    */
/* ************************************************************************** */

std::string const& ClapTrap::getName() const { return _name; }

int ClapTrap::getHitPoints() const { return _hitPoint; }

int ClapTrap::getEnergyPoints() const { return _energyPoint; }

int ClapTrap::getAttackDamage() const { return _attackDamage; }

void ClapTrap::setEnergyPoint() { _energyPoint--; } // 1 azalmasını istiyor

/* ************************************************************************** */
/* ACTIONS                                                                    */
/* ************************************************************************** */

void ClapTrap::attack(std::string const& enemy)
{
    if(!isAlive())
        return;
    std::cout << "ClapTrap " << _name << ", attacks " << enemy << " causing " << _attackDamage; 
    std::cout << " of damage!" << std::endl;
    _energyPoint--;
    std::cout << "ClapTrap " << _name << ", has " << _energyPoint << " energy ";
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if(_hitPoint <= 0)
    {
        std::cout << "ClapTrap " << _name << " already dead!" << std::endl;
        return;
    }
    std::cout << "ClapTrap " << _name << " has taken " << amount << " points of damage!" << std::endl;
    if(_hitPoint <= amount)
    {
        _hitPoint = 0;
       std::cout << "ClapTrap " << _name << " has " << _hitPoint << " hit point" << std::endl;
		std::cout << "ClapTrap " << _name << " died!" << std::endl;
    }
    else
	{
		_hitPoint -= amount;
		std::cout << "ClapTrap " << _name << " has " << _hitPoint << " hit point" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if(!isAlive())
        return;
    _hitPoint += amount;
    _energyPoint--;
    std::cout << "ClapTrap " << _name << " has been repaired of " << amount << " hit point!" << std::endl;
    std::cout << "ClapTrap " << _name << " has " << _hitPoint << " hit point" << std::endl;
    std::cout << "ClapTrap " << _name << " has " << _energyPoint << " energy" << std::endl;
}

/* ************************************************************************** */
/* HELPERS                                                                    */
/* ************************************************************************** */

bool ClapTrap::isAlive(void) const
{
	if (getHitPoints() <= 0)
	{
		std::cout << "ClapTrap " << _name << " cannot be repaired because he's" << " already dead!" << std::endl;
		return false;
	}
	else if (getEnergyPoints() <= 0)
	{
		std::cout << "ClapTrap " << _name << " has no energy point left!" << std::endl;
		return false;
	}
	else
		return true;
}