/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:50:04 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/20 12:50:35 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Fixed get_area(Point const a, Point const b, Point const c)
{
	Fixed area(((a.get_x() * b.get_y()) + (b.get_x() * c.get_y()) + (c.get_x() * a.get_y()))
			- ((a.get_y() * b.get_x()) + (b.get_y() * c.get_x()) + (c.get_y() * a.get_x())));
	if (area.getRawBits() < 0)
		area.setRawBits(area.getRawBits() * -1);
	return area;
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	if (get_area(a, b, c) == get_area(a, b, point) + get_area(b, c, point) + get_area(c, a, point))
		return true;
	else
		return false;
}
