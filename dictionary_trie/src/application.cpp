#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

// I use this function so that std::isspace doesnt throw an error
bool isSpace(char c)
{
    if ((c >= 0 && c <= 255) && std::isspace(c))
    {
        return true;
    }
    return false;
}

bool shouldIgnoreLine(const std::string& line)
{
    if (line.empty() || line[0] == '#') return true;

    size_t start = 0;
    while (start < line.size() && isSpace(line[start]))
    {
        ++start;
    }

    return start == line.size();
}

void insertWord(Dictionary& dictionary, const std::string& word, int lineCount, int& correctEntries, int& incorrectEntries)
{
    try
    {
        dictionary.insert(word.c_str());
        ++correctEntries;
    }
    catch (const incorrect_word_exception& e)
    {
        std::cout << "ERROR: incorrect entry \"" << word << "\" on line " << lineCount << std::endl;
        ++incorrectEntries;
    }
}
bool insertIntoDictionary(const std::string& fileName, Dictionary& dictionary, int& correctEntries, int& entries)
{
    std::ifstream dictionaryFile(fileName, std::ios::in);

    if (!dictionaryFile)
    {
        std::cout << "Dictionary file is Bad!";
        return false;
    }

    std::string line;
    size_t lineCount = 1;

    std::cout << "Loading dictionary from " << fileName << std::endl;
    while (std::getline(dictionaryFile, line))
    {
        if (shouldIgnoreLine(line)) continue;
        insertWord(dictionary, line, lineCount, correctEntries, entries);
        ++lineCount;
    }
    dictionaryFile.close();
    return true;
}

void removeWords(Dictionary& dictionary, const std::string& word, int lineCount, int& filCorrect, int& filIncorrect)
{
    if (dictionary.isCorrectWord(word.c_str()))
    {
        ++filCorrect;
        dictionary.erase(word.c_str());
    }
    else
    {
        std::cout << "ERROR: incorrect entry \"" << word << "\" on line " << lineCount << std::endl;
        ++filIncorrect;
    }
}
bool filterDictionary(const std::string& fileName, Dictionary& dictionary, int& filCorrect, int& filIncorrect)
{
    std::ifstream filterFile(fileName, std::ios::in);

    if (!filterFile)
    {
        std::cout << "Filter file is Bad!";
        return false;
    }

    std::string line;
    size_t lineCount = 1;

    std::cout << "\nRemoving the words listed at " << fileName << std::endl;
    while (std::getline(filterFile, line))
    {
        if (shouldIgnoreLine(line)) continue;
        removeWords(dictionary, line, lineCount, filCorrect, filIncorrect);
        ++lineCount;
    }
    filterFile.close();
    return true;
}

void manageIfWhiteSpace(std::string& word, const Dictionary& dictionary, int lineCount, int& correctWords, int& incorrectWords)
{
    if (word == "Dictionary")
        int s = 10;
    if (!word.empty() && dictionary.contains(word.c_str()))
    {
        ++correctWords;
    }
    else if (!word.empty() && !dictionary.contains(word.c_str()))
    {
        std::cout << "SPELLING ERROR: \"" << word << "\" on line " << lineCount << std::endl;
        ++incorrectWords;
    }
    if (!word.empty())
    {
        word.clear();
    }
}
bool verifyText(const std::string& fileName, Dictionary& dictionary, int& correctWords, int& incorrectWords)
{
    std::ifstream textFile(fileName, std::ios::in);

    if (!textFile)
    {
        std::cout << "Text file is Bad!";
        return false;
    }

    std::cout << "\nVerifying the contents of " << fileName << std::endl;

    std::string line;
    std::string word;

    size_t lineCount = 1;

    while (std::getline(textFile, line))
    {
        for (size_t i = 0; i < line.size(); i++)
        {
            if (!isSpace(line[i]))
            {
                word.push_back(line[i]);
            }
            else if (isSpace(line[i]))
            {
                manageIfWhiteSpace(word, dictionary, lineCount, correctWords, incorrectWords);
            }
        }
        manageIfWhiteSpace(word, dictionary, lineCount, correctWords, incorrectWords);
        ++lineCount;
    }
    textFile.close();
    return true;
}

std::string getCorrectAndIncorrect(int correctEntries, int incorrect)
{
    return std::to_string(correctEntries) + " correct, " + std::to_string(incorrect) + " incorrect";
}
void showStatistics(const Dictionary& dictionary, int dicCorrect, int dicIncorrect,
    int filCorrect, int filIncorrect, int filValid,
    int txtCorrect, int txtIncorrect)
{
    //
    // The new line was added because in the readme file it said that it should be there even tho it wasnt in
    // the example solution. At the beggining of the readme file it also said that it should show the count
    // of actual words the dictionary contains. In the example solution "Resultant dictionary" is 6 but because
    // the dictionary shouldn`t make difference from "abc" and "ABC" therefor it should display 3 in the example.
    //

    std::cout << "\nStatistics:\n" <<
        "    Dictionary entries: " << getCorrectAndIncorrect(dicCorrect, dicIncorrect) << "\n" <<
        "        Filter entries: " << getCorrectAndIncorrect(filCorrect, filIncorrect) << "\n" <<
        "         Removed words: " << std::to_string(filValid) << "\n" <<
        "  Resultant dictionary: " << std::to_string(dictionary.size()) << "\n" <<
        "         Words in text: " << getCorrectAndIncorrect(txtCorrect, txtIncorrect) << std::endl;
}


void displayUsage(const char* executablePath)
{
    try {
        fs::path ep(executablePath);

        std::cout
            << "Usage:\n\t"
            << ep.filename()
            << " <dictionary> <filter> <text>"
            << std::endl;
    }
    catch (...) {
        std::cout << "Cannot parse path from argv[0]";
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        displayUsage(argv[0]);
        return 1;
    }

    Dictionary dictionary;

    int dicCorrect = 0, dicIncorrect = 0;
    int filCorrect = 0, filIncorrect = 0, filValid = 0;
    int txtCorrect = 0, txtIncorrect = 0;

    std::string dictionaryFile = argv[1];
    std::string filterFile = argv[2];
    std::string textFile = argv[3];

    if (!insertIntoDictionary(dictionaryFile, dictionary, dicCorrect, dicIncorrect)) return -1;

    int dicSize = dictionary.size();
    if (!filterDictionary(filterFile, dictionary, filCorrect, filIncorrect)) return -1;
    filValid = dicSize - dictionary.size();

    if (!verifyText(textFile, dictionary, txtCorrect, txtIncorrect)) return -1;

    showStatistics(dictionary, dicCorrect, dicIncorrect,
        filCorrect, filIncorrect, filValid,
        txtCorrect, txtIncorrect);

    return 0;
}