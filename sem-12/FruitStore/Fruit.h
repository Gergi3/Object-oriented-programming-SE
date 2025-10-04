#pragma once

class Apple;
class Lemon;
class Orange;

class Fruit
{
public:
	Fruit() = default;
	virtual Fruit* clone() const = 0;
	virtual void print() const = 0;

	virtual void makeJuice(const Fruit* fruit) const = 0;
	virtual void makeJuiceWithApple(const Apple* apple) const = 0;
	virtual void makeJuiceWithLemon(const Lemon* lemon) const = 0;
	virtual void makeJuiceWithOrange(const Orange* orange) const = 0;

	virtual ~Fruit() = default;
};

