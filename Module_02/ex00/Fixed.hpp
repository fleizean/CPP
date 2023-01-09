/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:20:52 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/19 17:22:00 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private :
	int _value;
	static const int _bits;
public :
	Fixed(void);
	Fixed(const Fixed &fix);
	~Fixed(void);
	
	Fixed& operator=(const Fixed &fix);

	int getRawBits(void) const;
	void setRawBits(int const raw);
};

#endif
