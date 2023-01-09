/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:50:27 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/20 12:50:28 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int Fixed::_bits = 8;

Fixed::Fixed(void) : _value(0)
{ }

Fixed::Fixed(const int value)
{
	_value = value << _bits;
}

Fixed::Fixed(const float value)
{
	_value = roundf(value * (1 << _bits));
}

Fixed::Fixed(const Fixed& fix)
{
	*this = fix;
}

Fixed::~Fixed(void)
{ }

Fixed& Fixed::operator=(const Fixed& fix)
{
	_value = fix._value;
	return *this;
}

bool Fixed::operator>(const Fixed &fix) const
{
	return _value > fix.getRawBits();
}

bool Fixed::operator<(const Fixed &fix) const
{
	return _value < fix.getRawBits();
}

bool Fixed::operator>=(const Fixed &fix) const
{
	return _value >= fix.getRawBits();
}

bool Fixed::operator<=(const Fixed &fix) const
{
	return _value <= fix.getRawBits();
}

bool Fixed::operator==(const Fixed &fix) const
{
	return _value == fix.getRawBits();
}

bool Fixed::operator!=(const Fixed &fix) const
{
	return _value != fix.getRawBits();
}

Fixed Fixed::operator+(const Fixed &fix) const
{
	return Fixed(this->toFloat() + fix.toFloat());
}

Fixed Fixed::operator-(const Fixed &fix) const
{
	return Fixed(this->toFloat() - fix.toFloat());
}

Fixed Fixed::operator*(const Fixed &fix) const
{
 return Fixed(this->toFloat() * fix.toFloat());
}

Fixed Fixed::operator/(const Fixed &fix) const
{
	return Fixed(this->toFloat() / fix.toFloat());
}

Fixed& Fixed::operator++(void)
{
	_value++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed fix(*this);

	_value++;
	return fix;
}

Fixed& Fixed::operator--(void)
{
	_value--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed fix(*this);

	_value--;
	return fix;
}

int Fixed::getRawBits(void) const
{
	return _value;
}

void Fixed::setRawBits(int const raw)
{
	_value = raw;
}

int Fixed::toInt(void) const
{
	return (_value >> _bits);
}

float Fixed::toFloat(void) const
{
	return ((float)_value / (1 << _bits));
}

Fixed& Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f1.getRawBits() < f2.getRawBits())
		return f1;
	return f2;
}

const Fixed& Fixed::min(const Fixed &f1, const Fixed &f2)
{
	if (f1.getRawBits() < f2.getRawBits())
		return f1;
	return f2;
}

Fixed& Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f1.getRawBits() > f2.getRawBits())
		return f1;
	return f2;
}

const Fixed& Fixed::max(const Fixed &f1, const Fixed &f2)
{
	if (f1.getRawBits() > f2.getRawBits())
		return f1;
	return f2;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fix)
{
	os << fix.toFloat();
	return os;
}
