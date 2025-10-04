#include "ArrayTransformer.h"

template<typename T>
class CriteriaTransformer : public ArrayTransformer
{
	T criteria;
public:
	CriteriaTransformer(const T& criteria);
	void transform(int* arr, size_t size) const override;
	ArrayTransformer* clone() const override;
};

template<typename T>
CriteriaTransformer<T>::CriteriaTransformer(const T& criteria) : criteria(criteria)
{
}

template<typename T>
void CriteriaTransformer<T>::transform(int* arr, size_t size) const
{
	if (!arr)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		if (!criteria(arr[i]))
		{
			arr[i] = -1;
		}
	}
}

template<typename T>
ArrayTransformer* CriteriaTransformer<T>::clone() const
{
	return new CriteriaTransformer<T>(*this);
}
