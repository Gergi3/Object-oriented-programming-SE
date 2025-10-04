#include <iostream>
#include "ArrayTransformer.h"
#include "CriteriaTransformer.hpp"
#include "MyPair.hpp"
#include "ReplaceTransformer.h"
#include "ScalarTransformer.h"
#include "SwapTransformer.h"
#include "Transformers.h"

class EvenCriteria {
public:
	bool operator() (int num) const {
		return num % 2 == 0;
	}
};

int main() {
	EvenCriteria criteria;

	MyPair<size_t, int> pairs[3]; 
	pairs[0] = MyPair<size_t, int>(0, 2);
	pairs[1] = MyPair<size_t, int>(2, 19);
	pairs[2] = MyPair<size_t, int>(7, 10);

	Transformers transformers;
	transformers.add(new CriteriaTransformer<EvenCriteria>(criteria));
	transformers.add(new SwapTransformer(2, 6));
	transformers.add(new ScalarTransformer(3));
	transformers.add(new ReplaceTransformer(pairs,3)); // pairs: <0,2>, <2,19>, <7,10>

	int arr[10] = { 12, 7, 29, 3, 18, 25, 0, 14, 27, 6 };
	transformers.allTransformations(arr, 10);

	for (size_t i = 0; i < 10; i++)
	{
		std::cout << arr[i] << ' ';
	}
	// step 1: 12, -1, -1, -1, 18, -1, 0, 14, -1, 6
	// step 2: 12, -1, 0, -1, 18, -1, -1, 14, -1, 6 
	// step 3: 36, -3, 0, -3, 54, -3, -3, 42, -3, 18
	// step 4: 2, -3, 19, -3, 54, -3, -3, 10, -3, 18
	return 0;
}