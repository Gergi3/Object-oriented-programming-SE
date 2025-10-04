#pragma once
#include "Text.h"
#include <fstream>

template<typename T>
class ArgumentText : public Text
{
private:
	T validator;
	size_t l1, l2, l3, l4;

	void printParagraph(std::ostream& os, size_t beg, size_t end) const;

public:
	ArgumentText(const T& validator, const char* text, size_t l1,
		size_t l2, size_t l3, size_t l4);

	virtual Text* clone() const override;
	virtual void print(std::ostream& os) const override;
};

template<typename T>
void ArgumentText<T>::printParagraph(std::ostream& os, size_t beg, size_t end) const
{
	os << "	";
	for (size_t i = beg; i < end; i++)
	{
		os << text[i];
	}
	os << '\n';
}

template<typename T>
ArgumentText<T>::ArgumentText(const T& validator, const char* text, size_t l1,
	size_t l2, size_t l3, size_t l4) :Text(text), l1(l1),l2(l2), 
	l3(l3), l4(l4), validator(validator)
{
}

template<typename T>
Text* ArgumentText<T>::clone() const
{
	return new ArgumentText<T>(*this);
}

template<typename T>
void ArgumentText<T>::print(std::ostream& os) const
{
	printParagraph(os, 0, l1);
	printParagraph(os, l1, l1+l2);
	printParagraph(os, l1 + l2, l1 + l2 + l3);
	printParagraph(os, l1 + l2 + l3, l1 + l2 + l3 + l4);

	bool isValid = validator(text);

	if (isValid)
	{
		os << "Valid ArgumentText" << "\n";
	}
	else
	{
		os << "Invalid ArgumentText" << "\n";
	}
}
