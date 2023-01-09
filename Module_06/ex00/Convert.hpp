/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:25:04 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/05 17:25:04 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <iostream>
#include <string>
#include <cctype> // isprint
#include <sstream> // ostringstream
#include <climits> // int max min kontrol
#include <stdlib.h> // atoi atol

void conversionall(std::string str);
bool isOk(std::string &str);

#endif