/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:50:17 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/20 12:50:18 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point
{
private :
	const Fixed _x;
	const Fixed _y;
public :
	Point(void);
	Point(const Point &pt);
	Point(const Fixed x, const Fixed y);
	Point(const float x, const float y);
	~Point(void);

	Point& operator=(const Point &pt);

	const Fixed& get_x(void) const;
	const Fixed& get_y(void) const;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif
