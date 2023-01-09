#include "Dog.hpp"

// Default constructor
Dog::Dog()
{
    std::cout << "Dog default constructor called" << std::endl;
    _type = "Dog";
}

// Copy constructor
Dog::Dog(Dog const& src) : Animal(src)
{
    std::cout << "Cat copy constructor called" << std::endl;
}

// Copy assignment operator
Dog& Dog::operator=(Dog const& dog)
{
    std::cout << "Cat copy assignment operator called" << std::endl;
    Animal::operator=(dog);
    return *this;
}

// Destructor
Dog::~Dog() { std::cout << "Dog destructor called" << std::endl; }

// Public method
void Dog::makeSound() const { std::cout << "Woof!" << std::endl; }
