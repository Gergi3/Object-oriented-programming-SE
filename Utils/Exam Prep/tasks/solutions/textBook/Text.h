#pragma once
#include <fstream>

class Text
{
protected:
	char* text = nullptr;
	unsigned ID = 0;
	static unsigned IDcounter;

private:
	void copyFrom(const Text& other);
	void free();

public:
	Text(const char* text);
	Text(const Text& other);
	Text& operator=(const Text& other);
	virtual ~Text();

	static unsigned getNextID();

	virtual Text* clone() const = 0;
	virtual void print(std::ostream& os) const = 0;
	unsigned getID() const;
};

