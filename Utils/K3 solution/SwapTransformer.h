#pragma once
#include "ArrayTransformer.h"

class SwapTransformer : public ArrayTransformer
{
	size_t left = 0;
	size_t right = 0;
public:

	SwapTransformer(size_t left, size_t right);

	void transform(int* arr, size_t size) const override;
	ArrayTransformer* clone() const override;
};

