#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal
{
protected:
    std::string _type;
public:
    WrongAnimal();

    WrongAnimal(WrongAnimal const& src);

    WrongAnimal& operator=(WrongAnimal const& wanimal);

    virtual ~WrongAnimal();

    void setType(const std::string& type);
    
    std::string const& getType() const;

    void makeSound() const;
};

#endif