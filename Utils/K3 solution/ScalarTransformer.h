#pragma once
#include "ArrayTransformer.h"

class ScalarTransformer : public ArrayTransformer
{
	int scalar = 0;
public:
	ScalarTransformer(int scalar);

	void transform(int* arr, size_t size) const override;
	ArrayTransformer* clone() const override;
};

