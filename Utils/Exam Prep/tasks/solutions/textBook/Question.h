#pragma once
#include "Text.h"

class Question : public Text
{
private:
	static constexpr size_t MAX_SIZE = 1024;
	char answer[MAX_SIZE + 1]{};
public:
	Question(const char* question, const char* answer);
	virtual Text* clone() const override;
	virtual void print(std::ostream& os) const override;
};

