/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:16:24 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/10 17:58:30 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

class Span
{
public:
    unsigned int _size;
    std::vector<int> container;
    Span();
    Span(unsigned int size);
    ~Span();
    Span(const Span& other);
    Span &operator=(const Span &other);
    void addNumber(int num);
    int shortestSpan();
    int longestSpan();

    class ValueAlreadyExist : public std::exception
    {
    public:
    	const char* what(void) const throw()
    	{
    		return "You'r value already exist in container";
    	}
    };
    class ValueTooHighOrTooLow : public std::exception
    {
    public:
    	const char* what(void) const throw()
    	{
    		return "You'r value too low or to high!";
    	}
    };
    class OneSpanException : public std::exception
    {
    public:
    	const char* what(void) const throw()
    	{
    		return "You have 1 Span and I can't compare anything!";
    	}
    };
    class SpanCapacityException : public std::exception
    {
    public:
    	const char* what(void) const throw()
    	{
    		return "Span capacity exception!";
    	}
    };
};

#endif