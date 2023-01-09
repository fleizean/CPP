#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include "Animal.hpp"

class Cat : public Animal
{
public:
    Cat();
    
    Cat(Cat const& src);

    Cat& operator=(Cat const& cat);

    virtual ~Cat();

    virtual void makeSound() const;
};

#endif