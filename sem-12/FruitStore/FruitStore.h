#pragma once
#include "Fruit.h"

class FruitStore
{
	Fruit** fruits = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	static constexpr size_t INITIAL_CAPACITY = 16;
	static constexpr size_t GROWTH_FACTOR = 2;

	void copyFrom(const FruitStore& other);
	void moveFrom(FruitStore&& other);
	void free();

	void addFruit(Fruit* fruit);
	void resize(size_t newCapacity);

public:
	FruitStore();
	FruitStore(const FruitStore& other);
	FruitStore& operator=(const FruitStore& other);
	FruitStore(FruitStore&& other) noexcept;
	FruitStore& operator=(FruitStore&& other) noexcept;
	~FruitStore();

	void addApple();
	void addLemon();
	void addOrange();

	void print() const;
	void makeJuiceWith(size_t first, size_t second) const;

	size_t getSize() const;
};

