#include "Transformers.h"
#include <utility>
#include <stdexcept>
#include <iostream>

void Transformers::copyFrom(const Transformers& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new ArrayTransformer * [capacity] {};

	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

void Transformers::moveFrom(Transformers&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

void Transformers::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

void Transformers::resize(size_t newCapacity)
{
	ArrayTransformer** temp = new ArrayTransformer * [newCapacity] {};
	
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}

	capacity = newCapacity;
	delete[] data;
	data = temp;
}

Transformers::Transformers()
{
	size = 0;
	capacity = INITIAL_CAPACITY;
	data = new ArrayTransformer*[capacity] {};
}

Transformers::Transformers(const Transformers& other)
{
	copyFrom(other);
}

Transformers& Transformers::operator=(const Transformers& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Transformers::Transformers(Transformers&& other) noexcept
{
	moveFrom(std::move(other));
}

Transformers& Transformers::operator=(Transformers&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Transformers::~Transformers()
{
	free();
}

void Transformers::add(ArrayTransformer* ptr)
{
	if (!ptr)
	{
		return;
	}

	if (size == capacity)
	{
		resize(2 * capacity);
	}

	data[size++] = ptr;
}

void Transformers::add(const ArrayTransformer& other)
{
	add(other.clone());
}

void Transformers::allTransformations(int* arr, size_t size) const
{
	if (!arr)
	{
		return;
	}

	for (size_t i = 0; i < this->size; i++)
	{
		data[i]->transform(arr, size);
	}
}

void Transformers::intervalTransformations(int* arr, size_t size, size_t begin, size_t end) const
{
	if (!arr)
	{
		return;
	}

	if (begin > end || begin >= size || end >= size)
	{
		throw std::exception("Invalid indexes!");
	}

	for (size_t i = begin; i <= end; i++)
	{
		data[i]->transform(arr, size);
	}
}

Transformers Transformers::slice(size_t begin, size_t end) const
{
	if (begin > end || begin >= size || end >= size)
	{
		throw std::exception("Invalid indexes!");
	}

	Transformers toReturn;

	for (size_t i = begin; i <= end; i++)
	{
		toReturn.add(data[i]->clone());
	}

	return toReturn;
}
