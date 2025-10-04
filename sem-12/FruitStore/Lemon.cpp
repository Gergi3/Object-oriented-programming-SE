#include "Lemon.h"
#include <iostream>

Fruit* Lemon::clone() const
{
	return new Lemon(*this);
}

void Lemon::makeJuice(const Fruit* fruit) const
{
	fruit->makeJuiceWithLemon(this);
}

void Lemon::makeJuiceWithApple(const Apple* apple) const
{
	std::cout << "Lemon & Apple Juice" << std::endl;
}

void Lemon::makeJuiceWithLemon(const Lemon* lemon) const
{
	std::cout << "Lemon & Lemon Juice" << std::endl;
}

void Lemon::makeJuiceWithOrange(const Orange* orange) const
{
	std::cout << "Lemon & Orange Juice" << std::endl;
}

void Lemon::print() const
{
	std::cout << "Lemon" << std::endl;
}
