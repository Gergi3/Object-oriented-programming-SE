#pragma once
#include "ArrayTransformer.h"

class Transformers
{
	ArrayTransformer** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	static constexpr size_t INITIAL_CAPACITY = 16;

	void copyFrom(const Transformers& other);
	void moveFrom(Transformers&& other);
	void free();
	void resize(size_t newCapacity);

public:
	Transformers();
	Transformers(const Transformers& other);
	Transformers& operator=(const Transformers& other);
	Transformers(Transformers&& other) noexcept;
	Transformers& operator=(Transformers&& other) noexcept;
	~Transformers();

	void add(ArrayTransformer* ptr);
	void add(const ArrayTransformer& other);
	void allTransformations(int* arr, size_t size) const;
	void intervalTransformations(int* arr, size_t size, size_t begin, size_t end) const;
	Transformers slice(size_t begin, size_t end) const;
};

