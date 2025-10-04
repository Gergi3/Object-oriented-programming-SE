#include "FruitStore.h"
#include "Apple.h"
#include "Lemon.h"
#include "Orange.h"
#include <utility>

void FruitStore::copyFrom(const FruitStore& other)
{
	size = other.size;
	capacity = other.capacity;
	fruits = new Fruit * [capacity] {};

	for (size_t i = 0; i < size; i++)
	{
		fruits[i] = other.fruits[i]->clone();
	}
}

void FruitStore::moveFrom(FruitStore&& other)
{
	size = other.size;
	capacity = other.capacity;
	fruits = other.fruits;

	other.fruits = nullptr;
	other.size = other.capacity = 0;
}

void FruitStore::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete fruits[i];
	}

	delete[] fruits;
	fruits = nullptr;
	size = capacity = 0;
}

void FruitStore::addFruit(Fruit* fruit)
{
	if (!fruit)
	{
		return;
	}

	if (size == capacity)
	{
		resize(GROWTH_FACTOR * capacity);
	}

	fruits[size++] = fruit;
}

void FruitStore::resize(size_t newCapacity)
{
	Fruit** temp = new Fruit*[newCapacity]{};

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = fruits[i];
	}

	delete[] fruits;
	fruits = temp;
	capacity = newCapacity;
}

FruitStore::FruitStore()
{
	capacity = INITIAL_CAPACITY;
	fruits = new Fruit * [capacity] {};
}

FruitStore::FruitStore(const FruitStore& other)
{
	copyFrom(other);
}

FruitStore& FruitStore::operator=(const FruitStore& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

FruitStore::FruitStore(FruitStore&& other) noexcept
{
	moveFrom(std::move(other));
}

FruitStore& FruitStore::operator=(FruitStore&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

FruitStore::~FruitStore()
{
	free();
}

void FruitStore::addApple()
{
	addFruit(new Apple());
}

void FruitStore::addLemon()
{
	addFruit(new Lemon());
}

void FruitStore::addOrange()
{
	addFruit(new Orange());
}

void FruitStore::print() const
{
	for (size_t i = 0; i < size; i++)
	{
		fruits[i]->print();
	}
}

void FruitStore::makeJuiceWith(size_t first, size_t second) const
{
	if (first >= size || second >= size)
	{
		return;
	}

	fruits[first]->makeJuice(fruits[second]);
}

size_t FruitStore::getSize() const
{
	return size;
}
