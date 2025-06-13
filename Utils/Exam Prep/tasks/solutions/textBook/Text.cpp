#include "Text.h"
#include <cstring>

#pragma warning (disable:4996)

unsigned Text::IDcounter = 0;

void Text::copyFrom(const Text& other)
{
	this->text = new char[strlen(other.text) + 1]{};
	strcpy(this->text, other.text);
	this->ID = IDcounter++;
}

void Text::free()
{
	delete[] text;
	text = nullptr;
	ID = 0;
}

Text::Text(const char* text)
{
	this->text = new char[strlen(text) + 1]{};
	strcpy(this->text, text);
	this->ID = IDcounter++;
}

Text::Text(const Text& other)
{
	copyFrom(other);
}

Text& Text::operator=(const Text& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Text::~Text()
{
	free();
}

unsigned Text::getNextID()
{
	return IDcounter;
}

unsigned Text::getID() const
{
	return ID;
}