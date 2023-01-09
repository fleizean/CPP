/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:21:40 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/19 12:21:40 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>

class Harl
{
private :
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

public :
	Harl(void);
	~Harl(void);

	void complain(std::string level);
};

#endif
