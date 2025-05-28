#pragma once

class ArrayTransformer
{
public:
	virtual void transform(int* arr, size_t size) const = 0;
	virtual ArrayTransformer* clone() const = 0;
	virtual ~ArrayTransformer() = default;
};

