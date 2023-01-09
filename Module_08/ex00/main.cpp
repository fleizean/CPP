/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleizean <fleizean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:16:12 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/09 19:37:24 by fleizean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <ctime>

int main(int ac, char **av)
{
    if(ac != 2){
        std::cout << "./easyfind <your vector size>" << "\n";
        return(1);
    }
    std::string num; // num aranacak eleman
    int size = atoi(av[1]); // vectorün boyutunu belirlemek için
	std::string command;
    std::vector<int> vec;
   	for(int i = 0; i < size; i++)
		vec.push_back(rand() % (size - 1 + 1 ) + 1); // random sayı formül: rand() % (size - min + 1) + 1 = aralığa göre rand atıyorum
	while(1)
	{
		std::cout << std::endl << "Choose one command and input >> [ EASYFIND(1) | PRINT(2) | EXIT(3)] : ";
		if (!(std::getline(std::cin, command)))
            ;
		if(std::cin.eof())
			;
		if(!command.compare("EASYFIND") || !command.compare("1"))
		{
   			try
   			{
				std::cout << std::endl << "Enter value: ";
				if (!(std::getline(std::cin, num)))
            		;
				if(std::cin.eof())
					;
   			    easyfind(vec, atoi(num.c_str()));
   			}
   			catch(const std::exception& e)
   			{
   			    std::cerr << e.what() << '\n';
   			}
		}
		else if(!command.compare("PRINT") || !command.compare("2"))
			printcontainer(vec);
		else if(!command.compare("EXIT") || !command.compare("3"))
			exit(0);
	}
}