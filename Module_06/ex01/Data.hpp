/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:26:11 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/05 17:26:12 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

#include <string>

typedef struct 
{
    std::string name;
    std::string department;
    std::string job;
    int age;
    bool isActive;
} Data;

uintptr_t serialize(Data* data);
Data* deserialize(uintptr_t raw);

#endif