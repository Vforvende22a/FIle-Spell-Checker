#Trie-Based Spell Checker

This project implements a spell checker using a [prefix tree (Trie)](https://en.wikipedia.org/wiki/Trie). The program processes three text files to build a dictionary, filter out words, and verify a text file's words against the dictionary.

## Description

The program takes three file paths as command-line arguments:

1. **Dictionary file**: Contains the initial list of words for the dictionary.
2. **Filter file**: Specifies words to be removed from the dictionary.
3. **Text file**: Contains the text to be checked against the filtered dictionary.

## How It Works

This program processes three input files to perform dictionary management and spell-checking:

1. **Load Words into a Trie**:
   - Reads words from the dictionary file and inserts them into a Trie structure.
   - Ignores case (e.g., `abc` and `ABC` are treated as the same word).
   - Skips invalid entries (e.g., lines containing spaces, numbers, or special characters).
   - Handles duplicate words gracefully by storing only one instance.

2. **Filter Words**:
   - Reads words from the filter file and removes them from the Trie.
   - Case-insensitivity ensures both `abc` and `ABC` are removed as the same word.
   - Skips invalid entries while reporting errors.
   - Accounts for duplicates, ensuring only one removal per word.

3. **Check Text File**:
   - Reads the text file line by line.
   - Splits lines into words using whitespace as a delimiter.
   - Checks each word against the Trie.
   - Reports words that are not found in the Trie as spelling errors.

4. **Generate Summary Statistics**:
   - Reports the total number of valid and invalid entries in the dictionary file.
   - Reports the total number of valid and invalid entries in the filter file.
   - Displays the number of words successfully removed from the Trie.
   - Outputs the final count of words remaining in the dictionary.
   - Counts and reports correct and incorrect words in the text file.

## Features

- **Case-insensitive**: Treats uppercase and lowercase letters as equivalent.
- **Validation**: Reports invalid entries in the dictionary and filter files.
- **Error Reporting**: Identifies words in the text file that do not exist in the final dictionary.
- **Statistics**:
  - Number of valid and invalid entries in the dictionary.
  - Number of valid and invalid entries in the filter file.
  - Total words removed from the dictionary.
  - Final dictionary size.
  - Number of correct and incorrect words in the text file.

## Assumptions

- Words consist only of English letters (a–z).
- Invalid entries (e.g., containing spaces, numbers, or symbols) are skipped, but processing continues.
- Comment lines (starting with `#`) and empty lines are ignored.
- Duplicate entries are treated as a single word during processing.

## Input File Formats

### Dictionary file

Each word is on a separate line. Lines starting with `#` are comments. Empty lines are ignored.

### Filter file

Similar as the dictionary file. Specifies words to be removed from the dictionary.

### Text file

Contains one or more lines of text. Words are separated by whitespace.

## Example with the sample-inputs
    Loading dictionary from .\input\dictionary.txt...
    ERROR: incorrect entry "This is an incorrect entry, it has spaces." on line 8
    ERROR: incorrect entry " spaceOnTheLeft" on line 9
    ERROR: incorrect entry "spaceOnTheRight " on line 10
    ERROR: incorrect entry "an0ther1ncorrectW0rd" on line 11
    
    Removing the words listed at .\input\filter.txt...
    ERROR: incorrect entry "1234567890" on line 3
    
    Verifying the contents of .\input\text.txt...
    SPELLING ERROR: "abc" on line 1
    SPELLING ERROR: "abbcd" on line 1
    SPELLING ERROR: "xyz" on line 1
    SPELLING ERROR: "an0ther1ncorrectW0rd" on line 2
    
    Statistics:
        Dictionary entries: 7 correct, 4 incorrect
            Filter entries: 2 correct, 1 incorrect
      Resultant dictionary: 6
             Words in text: 2 correct, 4 incorrect
