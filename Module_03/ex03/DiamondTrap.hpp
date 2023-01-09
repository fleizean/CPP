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

#ifndef DIAMONDTRAPP_HPP
#define DIAMONDTRAPP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "iostream"

class DiamondTrap : public ScavTrap, public FragTrap
{
private:
    std::string _name;
public:
    // constructors
    DiamondTrap();
    DiamondTrap(std::string const& name);
    DiamondTrap(DiamondTrap const& src);
    
    // assigment operator
    DiamondTrap& operator=(DiamondTrap const& diamond);

    // destructor
    ~DiamondTrap();
    
    // actions
    void whoAmI() const;
    void attack(std::string const& enemy);
};

#endif