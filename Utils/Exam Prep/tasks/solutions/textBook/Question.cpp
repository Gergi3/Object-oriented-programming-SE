#include "Question.h"
#include <cstring>
#pragma warning (disable:4996)

Question::Question(const char* question, const char* answer) : Text(question)
{
    strcpy(this->answer, answer);
}

Text* Question::clone() const
{
    return new Question(*this);
}

void Question::print(std::ostream& os) const
{
    os << "Q: " << text << '\n';
    os << "A: " << answer;
}
