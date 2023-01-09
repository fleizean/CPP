/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleizean <fleizean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:16:22 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/09 19:29:36 by fleizean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(){
    this->_size = 0;
    this->container.reserve(0);

}

Span::Span(unsigned int size){
    this->_size = size;
    this->container.reserve(size);
}

Span::Span(const Span& other){
        this->_size = other._size;
        this->container = other.container;
    
}

Span &Span::operator=(const Span &other){
    if (this != &other){
        _size = other._size;
        container = other.container;
    }
    return (*this);
}

Span::~Span() { }

void Span::addNumber(int num)
{
    try
    {
        if(num > INT_MAX || num < INT_MIN)
            throw Span::ValueTooHighOrTooLow();
        if(std::find(container.begin(), container.end(), num) != container.end())
            throw Span::ValueAlreadyExist();
        if(_size > container.capacity())
            throw Span::SpanCapacityException();
        container.push_back(num);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        exit(0);
    }
}

static int mySpan(int n1, int n2){
    if (n1 > n2)
        return (n1 - n2);
    return (n2 - n1);
}

int Span::shortestSpan()
{
    try{
        
        if (container.size() < 2)
            throw Span::OneSpanException();

        std::sort(container.begin(), container.end());
        int min = INT_MAX;
	    for (int i = 0; i < container.size() - 1; i++)
	    {
		    if (min > container[i + 1] - container[i])
		    	min = container[i + 1] - container[i];
	    }
        return(min);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        exit(0);
    }
}

int Span::longestSpan()
{
    try{
        if (container.size() < 2)
            throw Span::OneSpanException();
        return *std::max_element(container.begin(), container.end()) - *std::min_element(container.begin(), container.end());
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        exit(0);
    }
}
