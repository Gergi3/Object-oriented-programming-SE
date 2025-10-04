#pragma once
#include "Text.h"

class TextBook
{
	static constexpr size_t INITIAL_CAPACITY = 8;
	Text** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void copyFrom(const TextBook& other);
	void free();
	void resize(size_t newCapacity);

	void generateFileName(char* buff, size_t idx) const;

public:
	TextBook();
	TextBook(const TextBook& other);
	TextBook& operator=(const TextBook& other);
	~TextBook();

	void addText(Text* ptr);
	void addText(const Text& other);

	// maybe we can change it with a our member func for clarity 
	// but let's keep it with [] as the task description says
	void operator[](size_t idx) const; 

	friend std::ostream& operator<<(std::ostream& os, const TextBook& tb);
};

