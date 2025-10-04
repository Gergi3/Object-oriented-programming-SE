#include "Poem.h"
#include <cstring>
#pragma warning (disable:4996)


void Poem::copyFrom(const Poem& other)
{
    wordsCnt = other.wordsCnt;
    words = new char* [wordsCnt] {};

    for (size_t i = 0; i < wordsCnt; i++)
    {
        this->words[i] = new char[strlen(other.words[i]) + 1]{};
        strcpy(this->words[i], other.words[i]);
    }
}

void Poem::free()
{
    for (size_t i = 0; i < wordsCnt; i++)
    {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    wordsCnt = 0;
}

Poem::Poem(const char* text, const char** words, size_t wordsCnt) : Text(text)
{
    this->wordsCnt = wordsCnt;
    this->words = new char* [wordsCnt];
    for (size_t i = 0; i < wordsCnt; i++)
    {
        this->words[i] = new char[strlen(words[i]) + 1]{};
        strcpy(this->words[i], words[i]);
    }
}

Poem::Poem(const Poem& other) : Text(other)
{
    copyFrom(other);
}

Poem& Poem::operator=(const Poem& other)
{
    if (this != &other)
    {
        Text::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

Poem::~Poem()
{
    free();
}

Text* Poem::clone() const
{
    return new Poem(*this);
}

void Poem::print(std::ostream& os) const
{
    os << text << '\n';
    os << "{ ";

    for (size_t i = 0; i < wordsCnt; i++)
    {
        os << words[i];
        if (i != wordsCnt - 1)
        {
            os << ", ";
        }
    }

    os << " }" << "\n";
}
