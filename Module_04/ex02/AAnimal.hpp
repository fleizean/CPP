#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal 
{
 protected:
  std::string _type;

 public:
  /* default constructor */
  AAnimal();

  /* copy constructor */
  AAnimal(AAnimal const& src);

  /* copy assignment operator */
  virtual AAnimal& operator=(AAnimal const& animal);

  /* destructor */
  virtual ~AAnimal();

  /* getter */
  std::string const& getType() const;

  virtual void makeSound() const = 0;
};

#endif