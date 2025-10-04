#include "Orange.h"
#include <iostream>

Fruit* Orange::clone() const
{
	return new Orange(*this);
}

void Orange::makeJuice(const Fruit* fruit) const
{
	fruit->makeJuiceWithOrange(this);
}

void Orange::makeJuiceWithApple(const Apple* apple) const
{
	std::cout << "Orange & Apple Juice" << std::endl;
}

void Orange::makeJuiceWithLemon(const Lemon* lemon) const
{
	std::cout << "Orange & Lemon Juice" << std::endl;
}

void Orange::makeJuiceWithOrange(const Orange* orange) const
{
	std::cout << "Orange & Orange Juice" << std::endl;
}

void Orange::print() const
{
	std::cout << "Orange" << std::endl;
}
