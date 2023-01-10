/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:16:20 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/10 17:55:01 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
    Span sp = Span(5);
    sp.addNumber(-1);
    sp.addNumber(-6);
    sp.addNumber(17);
    sp.addNumber(3);
    sp.addNumber(4);
    std::cout << sp.shortestSpan() << std::endl; // en kısa sayı mesafesini buluyor
    std::cout << sp.longestSpan() << std::endl; // en uzun sayı mesafesini buluyor
    return 0;
}