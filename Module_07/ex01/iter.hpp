/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:22:25 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/06 01:22:25 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include "iostream"

template<typename T> void iter(T *array, size_t len, void(*f)(T const &)){
    for (size_t i = 0; i < len; i++)
        f(array[i]);
}

#endif
