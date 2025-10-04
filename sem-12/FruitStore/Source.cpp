#include "FruitStore.h"

int main()
{
	FruitStore fs;

	fs.addApple();
	fs.addApple();
	fs.addLemon();
	fs.addOrange();
	fs.addOrange();
	fs.addLemon();

	fs.print();

	fs.makeJuiceWith(2, 1);
	fs.makeJuiceWith(4, 5);
	return 0;
}