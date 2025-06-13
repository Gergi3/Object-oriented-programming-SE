#pragma once
#include "Text.h"

class Poem : public Text
{
	char** words = nullptr;
	size_t wordsCnt = 0;

	void copyFrom(const Poem& other);
	void free();

public:
	Poem(const char* text, const char** words, size_t wordsCnt);
	Poem(const Poem& other);
	Poem& operator=(const Poem& other);
	~Poem();

	Text* clone() const override;
	void print(std::ostream& os) const override;
};

