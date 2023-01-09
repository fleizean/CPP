#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"
#include "AAnimal.hpp"

int main(void)
{
	/* Error Area */
	// const AAnimal* animal = new AAnimal();
	// animal->makeSound();
	// delete animal;

	 const AAnimal* dog = new Dog();
	 const AAnimal* cat = new Cat();
	 std::cout << std::endl;

	 dog->makeSound();
	 cat->makeSound();
	 std::cout << std::endl;

	 delete dog;
	 delete cat;
	
	 return 0;
}