#pragma once
#include "Fruit.h"

class Lemon : public Fruit
{
public:
	Lemon() = default;
	Fruit* clone() const override;
	void print() const override;

	void makeJuice(const Fruit* fruit) const override;
	void makeJuiceWithApple(const Apple* apple) const override;
	void makeJuiceWithLemon(const Lemon* lemon) const override;
	void makeJuiceWithOrange(const Orange* orange) const override;
};

