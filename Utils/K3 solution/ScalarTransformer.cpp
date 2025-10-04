#include "ScalarTransformer.h"

ScalarTransformer::ScalarTransformer(int scalar) : scalar(scalar)
{
}

void ScalarTransformer::transform(int* arr, size_t size) const
{
    if (!arr)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        arr[i] *= scalar;
    }
}

ArrayTransformer* ScalarTransformer::clone() const
{
    return new ScalarTransformer(*this);
}
