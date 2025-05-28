#include "ReplaceTransformer.h"
#include <utility>

void ReplaceTransformer::copyFrom(const ReplaceTransformer& other)
{
    size = other.size;
    pairs = new MyPair<size_t, int>[size] {};

    for (size_t i = 0; i < size; i++)
    {
        pairs[i] = other.pairs[i];
    }
}

void ReplaceTransformer::moveFrom(ReplaceTransformer&& other)
{
    pairs = other.pairs;
    other.pairs = nullptr;
    size = other.size;
    other.size = 0;
}

void ReplaceTransformer::free()
{
    delete[] pairs;
    pairs = nullptr;
    size = 0;
}

ReplaceTransformer::ReplaceTransformer(const MyPair<size_t, int>* pairs, size_t size)
{
    this->size = size;
    this->pairs = new MyPair<size_t, int>[size] {};

    for (size_t i = 0; i < size; i++)
    {
        this->pairs[i] = pairs[i];
    }
}

ReplaceTransformer::ReplaceTransformer(const ReplaceTransformer& other) : ArrayTransformer(other)
{
    copyFrom(other);
}

ReplaceTransformer& ReplaceTransformer::operator=(const ReplaceTransformer& other)
{
    if (this != &other)
    {
        ArrayTransformer::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

ReplaceTransformer::ReplaceTransformer(ReplaceTransformer&& other) noexcept : ArrayTransformer(std::move(other))
{
    moveFrom(std::move(other));
}

ReplaceTransformer& ReplaceTransformer::operator=(ReplaceTransformer&& other) noexcept
{
    if (this != &other)
    {
        ArrayTransformer::operator=(std::move(other));
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

ReplaceTransformer::~ReplaceTransformer()
{
    free();
}

void ReplaceTransformer::transform(int* arr, size_t size) const
{
    if (!arr)
    {
        return;
    }

    for (size_t i = 0; i < this->size; i++)
    {
        if (pairs[i].first >= size)
        {
            continue;
        }
        arr[pairs[i].first] = pairs[i].second;
    }
}

ArrayTransformer* ReplaceTransformer::clone() const
{
    return new ReplaceTransformer(*this);
}
