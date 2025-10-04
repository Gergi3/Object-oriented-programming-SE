#include "Apple.h"
#include <iostream>

Fruit* Apple::clone() const
{
    return new Apple(*this);
}

void Apple::makeJuice(const Fruit* fruit) const
{
    fruit->makeJuiceWithApple(this);
}

void Apple::makeJuiceWithApple(const Apple* apple) const
{
    std::cout << "Apple & Apple Juice" << std::endl;
}

void Apple::makeJuiceWithLemon(const Lemon* lemon) const
{
    std::cout << "Apple & Lemon Juice" << std::endl;
}

void Apple::makeJuiceWithOrange(const Orange* orange) const
{
    std::cout << "Apple & Orange Juice" << std::endl;
}

void Apple::print() const
{
    std::cout << "Apple" << std::endl;
}
