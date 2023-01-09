#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal 
{
 protected:
  std::string _type;

 public:
  /* default constructor */
  Animal();

  /* copy constructor */
  Animal(Animal const& src);

  /* copy assignment operator */
  Animal& operator=(Animal const& animal);

  /* destructor */
  virtual ~Animal();

  /* getter */
  virtual std::string const& getType() const; // gereksiz olabilir

  virtual void makeSound() const;
};

#endif