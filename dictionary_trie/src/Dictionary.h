#pragma once

#include <stdexcept>
#include <unordered_set>

#include "Trie.h"

class incorrect_word_exception : public std::runtime_error 
{
public:
  incorrect_word_exception()
    : runtime_error("incorrect word")
  {
    // Nothing to do here
  }
};

class Dictionary
{
public:
  void insert(const char* word);
  void erase(const char* word) noexcept;
  bool contains(const char* word) const noexcept;
  size_t size() const noexcept;
  static bool isCorrectWord(const char* word) noexcept;

private:
    static bool isAlpha(char c);
    Trie words;
};
