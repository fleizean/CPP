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

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <iostream>

class ScavTrap : virtual public ClapTrap // sanal olarak aldığımız yer
{
public:
    // Constructors
    bool guard_mode;
    ScavTrap();
    ScavTrap(std::string const& name);
    ScavTrap(ScavTrap const& src);

    ScavTrap& operator=(ScavTrap const& scav);

    ~ScavTrap();

    //actions
    void guardGate(void);
    void attack(const std::string enemy);
};

#endif
