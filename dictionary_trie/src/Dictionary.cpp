#include "Dictionary.h"
#include <cctype> // Contains std::isalpha()

//TODO Implement the Dictionary class

void Dictionary::insert(const char* word)
{
	if (Dictionary::isCorrectWord(word))
	{
		words.insert(word);
	}
	else throw incorrect_word_exception();
}

void Dictionary::erase(const char* word) noexcept
{
	try
	{
		if (Dictionary::isCorrectWord(word))
			words.remove(word);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

bool Dictionary::contains(const char* word) const noexcept
{
	try
	{
		if (Dictionary::isCorrectWord(word))
			return words.search(word);
		return false;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
}

size_t Dictionary::size() const noexcept
{
	return words.getWordsCount();
}

// I use this function so that std::isalpha doesnt throw an error
bool Dictionary::isAlpha(char c)
{
	if ((c >= 0 && c <= 255) && std::isalpha(c))
	{
		return true;
	}
	return false;
}

bool Dictionary::isCorrectWord(const char* word) noexcept
{
	if (!word)				return false;
	else if (*word == '\0') return false;
	while (*word)
	{
		if (!isAlpha(*word))
			return false;
		++word;
	}
	return true;
}
