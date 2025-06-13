#include "TextBook.h"
#include <stdexcept>
#include <cstring>
#pragma warning (disable:4996)

static char digitToChar(size_t digit)
{
	return '0' + digit;
}

static void reverse(char* str)
{
	if (!str)
	{
		return;
	}

	int l = 0;
	int r = strlen(str) - 1;

	while (l <= r)
	{
		std::swap(str[l], str[r]);
		l++;
		r--;
	}
}

static void numToString(char* buff, size_t num)
{
	size_t idx = 0;

	if (num == 0)
	{
		buff[idx++] = '0';
	}

	while (num != 0)
	{
		size_t digit = num % 10;
		buff[idx++] = digitToChar(digit);
		num /= 10;
	}

	buff[idx] = '\0';

	reverse(buff);
}

void TextBook::copyFrom(const TextBook& other)
{
	data = new Text * [other.capacity];
	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

void TextBook::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

void TextBook::resize(size_t newCapacity)
{
	capacity = newCapacity;

	Text** tmp = new Text * [capacity];

	for (size_t i = 0; i < size; i++)
	{
		tmp[i] = data[i];
	}
	delete[] data;
	data = tmp;
	tmp = nullptr;
}

void TextBook::generateFileName(char* buff, size_t idx) const
{
	if (!buff)
	{
		return;
	}

	strcpy(buff, "text_");
	char idxBuff[32]{};
	numToString(idxBuff, idx);
	strcat(buff, idxBuff);
	strcat(buff, ".txt");
}

TextBook::TextBook()
{
	size = 0;
	capacity = INITIAL_CAPACITY;
	data = new Text * [capacity] {};
}

TextBook::TextBook(const TextBook& other)
{
	copyFrom(other);
}

TextBook& TextBook::operator=(const TextBook& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

TextBook::~TextBook()
{
	free();
}

void TextBook::addText(Text* ptr)
{
	if (!ptr)
	{
		return;
	}

	if (size == capacity)
	{
		resize(2 * capacity);
	}
	data[size++] = ptr;
}

void TextBook::addText(const Text& other)
{
	addText(other.clone());
}

void TextBook::operator[](size_t idx) const
{
	if (idx >= size)
	{
		throw std::out_of_range("Index out of range!");
	}
	char fileName[256]{};
	generateFileName(fileName, idx);

	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		throw std::runtime_error("File couldn't open!");
	}

	data[idx]->print(ofs);

	ofs.close();
}

std::ostream& operator<<(std::ostream& os, const TextBook& tb)
{
	for (size_t i = 0; i < tb.size; i++)
	{
		tb.data[i]->print(os);
		os << '\n';
	}
	return os;
}
