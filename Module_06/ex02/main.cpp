/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:26:40 by eyagiz            #+#    #+#             */
/*   Updated: 2023/01/05 22:34:34 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Base.hpp"
#include <iostream>

Base*	generate(void)
{
    Base *result;

	srand(time(NULL));
    switch (rand() % 3)
    {
        case 0:
            std::cout << "A created" << std::endl;
            result = new A();
            break;
        case 1:
            std::cout << "B created" << std::endl;
            result = new B();
            break;
        case 2:
            std::cout << "C created" << std::endl;
            result = new C();
            break;
    }
    return(result);
}

void	identify(Base *p){
	std::cout << "p: " << &p << std::endl;
	A *a = dynamic_cast<A *>(p);
	B *b = dynamic_cast<B *>(p);
	C *c = dynamic_cast<C *>(p);

	if (a)
		std::cout << "the type is A " << std::endl;
	else if (b)
		std::cout << "the type is B " << std::endl;
	else if (c)
		std::cout << "the type is C " << std::endl;
}

void identify(Base &p){
	try{
		A &a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << "the Type is A" << std::endl;
	}
	catch (std::exception &e) {}

	try{
		B &b = dynamic_cast<B &>(p);
		(void)b;
		std::cout << "the Type is B" << std::endl;
	}
	catch (std::exception &e) {}

	try{
		C &c = dynamic_cast<C &>(p);
		(void)c;
		std::cout << "the Type is C" << std::endl;
	}
	catch (std::exception &e) {}
}

int main(void)
{
	Base *ptr;

	ptr = generate();
	identify(ptr);
	identify(*ptr);
	delete ptr;
}