/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:32:16 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/05 21:05:00 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(int ac, char **av)
{
    if (ac == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    else
    {
		for (int i = 1; i < ac; i++)
		{
			std::string str = av[i];
			for (size_t j = 0; j < str.length(); j++)
				std::cout << (char)toupper(str[j]);
		}
		std::cout << std::endl;
    }
    return (0);
}