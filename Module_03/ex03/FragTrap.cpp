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

#include "FragTrap.hpp"

/* ************************************************************************** */
/* CONSTRUCTORS                                                               */
/* ************************************************************************** */

FragTrap::FragTrap::FragTrap() : ClapTrap("unnamed2", 100, 100, 30)
{
    std::cout << "FragTrap default constructor called" << std::endl;
    setHitPoints(100);
    if (getEnergyPoints() == 10) setEnergyPoints(100);
    setAttackDamage(30);
    return;
}

FragTrap::FragTrap::FragTrap(std::string const& name) : ClapTrap(name, 100, 100, 20)
{
    setHitPoints(100);
    if (getEnergyPoints() == 10) setEnergyPoints(100);
    setAttackDamage(30);
    std::cout << "FragTrap parametric constructor called for " << getName() << std::endl;
    return;
}

FragTrap::FragTrap(FragTrap const& src) : ClapTrap(src)
{
    std::cout << "FragTrap copy constructor called for " << src.getName() << std::endl;
    return;
}

/* ************************************************************************** */
/* ASSIGNMENT OPERATOR                                                        */
/* ************************************************************************** */

FragTrap& FragTrap::operator=(FragTrap const& frag)
{
    std::cout << "FragTrap copy assignment operator called for " << frag.getName() << std::endl;
    ClapTrap::operator=(frag);
    return *this;
}

/* ************************************************************************** */
/* DESTRUCTOR                                                                 */
/* ************************************************************************** */

FragTrap::~FragTrap()
{
    std::cout << "FragTrap destructor called for " << getName() << std::endl;
}

/* ************************************************************************** */
/* ACTIONS                                                                    */
/* ************************************************************************** */

void FragTrap::highFiveGuys() const
{
    std::cout << "FragTrap " << getName() << " says: \"Hi Guys! Who want a high five?\"" << std::endl;
    return;
}

void FragTrap::attack(std::string const& enemy)
{
    if(!isAlive())
        return;
    decrEnergyPoint();
    std::cout << "FragTrap " << getName() << " attacks " << enemy << ", causing " << getAttackDamage() << " points of damage!" << std::endl;
    std::cout << "FragTrap " << getName() << ", has " << getEnergyPoints() << " energy " << std::endl;
}