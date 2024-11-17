#include "catch2/catch_all.hpp"
#include "Dictionary.h"
//TODO Add your own unit tests to this file,
// or create additional files in this directory.

// TEST_CASE("Sample test")
// {
//     CHECK(true);
// }

// Dictionary class isCorrectWord method tests
TEST_CASE("Dictionary::isCorrectWord Tests")
{
    Dictionary dictionary;

    SECTION("Valid words with English characters") 
    {
        
        REQUIRE(dictionary.isCorrectWord("hello"));
        REQUIRE(dictionary.isCorrectWord("WORLD"));
        REQUIRE(dictionary.isCorrectWord("TeSt"));
        REQUIRE(dictionary.isCorrectWord("tEsT"));
    }

    SECTION("Invalid words with non-English characters or symbols")
    {
        REQUIRE_FALSE(dictionary.isCorrectWord("Catch2"));
        REQUIRE_FALSE(dictionary.isCorrectWord("héllo"));  
        REQUIRE_FALSE(dictionary.isCorrectWord("world!")); 
        REQUIRE_FALSE(dictionary.isCorrectWord("123"));    
        REQUIRE_FALSE(dictionary.isCorrectWord(""));       
        REQUIRE_FALSE(dictionary.isCorrectWord(nullptr));  
        REQUIRE_FALSE(dictionary.isCorrectWord("hello world")); 
        REQUIRE_FALSE(dictionary.isCorrectWord("hello-world")); 
    }
}

// Dictionary class insert method tests
TEST_CASE("Dictionary::insert Tests") 
{
    Dictionary dict;

    SECTION("Inserting valid words")
    {
        REQUIRE_NOTHROW(dict.insert("hello"));
        REQUIRE_NOTHROW(dict.insert("WORLD"));
    }

    SECTION("Inserting invalid words") 
    {
        REQUIRE_THROWS_AS(dict.insert("héllo"), incorrect_word_exception);  
        REQUIRE_THROWS_AS(dict.insert("world!"), incorrect_word_exception); 
        REQUIRE_THROWS_AS(dict.insert("123"), incorrect_word_exception);    
        REQUIRE_THROWS_AS(dict.insert(""), incorrect_word_exception);       
        REQUIRE_THROWS_AS(dict.insert(nullptr), incorrect_word_exception);  
    }
}

// Dictionary class contains method tests
TEST_CASE("Dictionary::contains Tests") 
{
    Dictionary dict;

    SECTION("Words that exist in the dictionary")
    {
        dict.insert("test");
        dict.insert("TEaCh");
        dict.insert("teaCHER");
        dict.insert("helLO");
        dict.insert("heYY");

        REQUIRE(dict.contains("test"));
        REQUIRE(dict.contains("teach"));
        REQUIRE(dict.contains("teacher"));
        REQUIRE(dict.contains("hello"));
        REQUIRE(dict.contains("HELLO"));
        REQUIRE(dict.contains("hElLO"));
        REQUIRE(dict.contains("HelLo"));
        REQUIRE(dict.contains("heyy"));
    }

    SECTION("Words that do not exist in the dictionary") 
    {
        dict.insert("example");
        dict.insert("dictionary");
        dict.insert("test");
        dict.insert("TEaCh");
        dict.insert("teaCHER");

        REQUIRE_FALSE(dict.contains("teachers"));
        REQUIRE_FALSE(dict.contains("tea"));
        REQUIRE_FALSE(dict.contains("nonexistent"));
        REQUIRE_FALSE(dict.contains("missing"));
        REQUIRE_FALSE(dict.contains("notaword"));
    }

    SECTION("Words in an empty dictionary") 
    {
        REQUIRE_FALSE(dict.contains("nothing"));
        REQUIRE_FALSE(dict.contains("empty"));
    }

    SECTION("Invalid words")
    {
        REQUIRE_FALSE(dict.contains("123"));
        REQUIRE_FALSE(dict.contains(""));
        REQUIRE_FALSE(dict.contains(nullptr));
    }
}

// Dictionary class erase method tests
TEST_CASE("Dictionary::erase Tests")
{
    Dictionary dict;

    SECTION("Erasing words that exist")
    {
        dict.insert("hello");
        dict.insert("world");
        dict.insert("test");

        int wordsCount = dict.size();

        REQUIRE_NOTHROW(dict.erase("hello"));
        REQUIRE(dict.size() < wordsCount);
        wordsCount = dict.size();

        REQUIRE_NOTHROW(dict.erase("world"));
        REQUIRE(dict.size() < wordsCount);


        REQUIRE_FALSE(dict.contains("hello"));
        REQUIRE_FALSE(dict.contains("world"));
        REQUIRE(dict.contains("test"));
    }

    SECTION("Erasing words that do not exist")
    {
        dict.insert("example");
        dict.insert("dictionary");

        REQUIRE_NOTHROW(dict.erase("nonexistent"));
        REQUIRE_NOTHROW(dict.erase("missing"));

        REQUIRE(dict.contains("example"));
        REQUIRE(dict.contains("dictionary"));
    }

    SECTION("Erasing from an empty dictionary") 
    {
        REQUIRE_NOTHROW(dict.erase("nothing"));
    }

    SECTION("Erasing invalid words") 
    {
        REQUIRE_NOTHROW(dict.erase("123"));
        REQUIRE_NOTHROW(dict.erase(""));
        REQUIRE_NOTHROW(dict.erase(nullptr));
    }
}