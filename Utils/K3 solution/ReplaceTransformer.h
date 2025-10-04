#pragma once
#include "ArrayTransformer.h"
#include "MyPair.hpp"

class ReplaceTransformer : public ArrayTransformer
{
	MyPair<size_t, int>* pairs;
	size_t size;

	void copyFrom(const ReplaceTransformer& other);
	void moveFrom(ReplaceTransformer&& other);
	void free();

public:
	ReplaceTransformer(const MyPair<size_t, int>* pairs, size_t size);
	ReplaceTransformer(const ReplaceTransformer& other);
	ReplaceTransformer& operator=(const ReplaceTransformer& other);
	ReplaceTransformer(ReplaceTransformer&& other) noexcept;
	ReplaceTransformer& operator=(ReplaceTransformer&& other) noexcept;
	~ReplaceTransformer();

	void transform(int* arr, size_t size) const override;
	ArrayTransformer* clone() const override;
};

