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

#include "DiamondTrap.hpp"

/* ************************************************************************** */
/* CONSTRUCTORS                                                               */
/* ************************************************************************** */

DiamondTrap::DiamondTrap::DiamondTrap() : ClapTrap("default_clap_name")
{
    std::cout << "DiamondTrap default constructor called" << std::endl;
    DiamondTrap::_name = "unnamed";
    return;
}

DiamondTrap::DiamondTrap::DiamondTrap(std::string const& name) : ClapTrap(name + "_clap_name")
{
    DiamondTrap::_name = name;
    setHitPoints(FragTrap::getHitPoints());
    setEnergyPoints(ScavTrap::getHitPoints());
    setAttackDamage(FragTrap::getAttackDamage());
    std::cout << "DiamondTrap parametric constructor called for " << getName() << std::endl;
    return;
}

DiamondTrap::DiamondTrap(DiamondTrap const& src) : ClapTrap(src) , ScavTrap(src) , FragTrap(src)
{
    std::cout << "DiamondTrap copy constructor called for " << getName() << std::endl;
    DiamondTrap::_name = src.DiamondTrap::_name;
    setHitPoints(src.getHitPoints());
    setEnergyPoints(src.getEnergyPoints());
    setAttackDamage(src.getAttackDamage());
    return;
}

/* ************************************************************************** */
/* ASSIGNMENT OPERATOR                                                        */
/* ************************************************************************** */

DiamondTrap& DiamondTrap::operator=(DiamondTrap const& diamond)
{
    std::cout << "DiamondTrap copy assignment operator called for " << diamond.DiamondTrap::_name << std::endl;
    ClapTrap::operator=(diamond);
    _name = diamond.DiamondTrap::_name;
    return *this;
}

/* ************************************************************************** */
/* DESTRUCTOR                                                                 */
/* ************************************************************************** */

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap destructor called for " << DiamondTrap::_name << std::endl;
}

void DiamondTrap::whoAmI() const
{
    std::cout << "I am a DiamondTrap, my name is " << DiamondTrap::_name << ". My ClapTrap name is " << ClapTrap::getName() << std::endl;
    std::cout << "hit point: " << getHitPoints() << std::endl;
    std::cout << "energy point: " << getEnergyPoints() << std::endl;
    std::cout << "damage : " << getAttackDamage() << std::endl;
    return;
}

void DiamondTrap::attack(std::string const& enemy)
{
    ScavTrap::attack(enemy);
}