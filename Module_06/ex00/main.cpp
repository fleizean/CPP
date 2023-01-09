/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:25:06 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/05 17:25:06 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

int main(int ac, char **av)
{
    if(ac != 2)
    {
        std::cerr << "Usage: ./convert <scalar_to_convert>\n"
			"Valid scalars to convert: int, float, double or char."
			    << std::endl;
        return(1);
    }
    std::cout << "I am trying to convert your " << av[1] << std::endl;
    std::string str = (std::string)av[1];
    if(isOk(str))
        conversionall(str);
}