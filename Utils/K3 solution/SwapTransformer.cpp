#include "SwapTransformer.h"
#include <iostream>

SwapTransformer::SwapTransformer(size_t left, size_t right)
{
    if (left > right)
    {
        std::swap(left, right);
    }
    this->left = left;
    this->right = right;
}

void SwapTransformer::transform(int* arr, size_t size) const
{
    if (!arr || left >= size || right >= size)
    {
        return;
    }
    std::swap(arr[left], arr[right]);
}

ArrayTransformer* SwapTransformer::clone() const
{
    return new SwapTransformer(*this);
}
