#pragma once
#include <string>
#include <iostream>

static const int alphabetSize = 26;

struct Node
{
	Node* children[alphabetSize];
	bool isWord;

	Node()
	{
		for (size_t i = 0; i < alphabetSize; i++)
		{
			children[i] = nullptr;
		}
		isWord = false;
	}

	bool isEmpty()
	{
		for (int i = 0; i < alphabetSize; i++)
			if (children[i])
				return false;
		return true;
	}
};



#include <new>  // For std::bad_alloc

class BadAllocThrowingAllocator {
public:
	void* allocate(size_t size) {
		throw std::bad_alloc();
	}

	void deallocate(void* ptr, size_t size) {
		// No deallocation needed as we never actually allocate
	}
};


class Trie
{
private:
	struct Node
	{
		Node* children[alphabetSize];
		bool isWord;

		Node()
		{
			for (size_t i = 0; i < alphabetSize; i++)
			{
				children[i] = nullptr;
			}
			isWord = false;
		}

		bool isEmpty()
		{
			for (int i = 0; i < alphabetSize; i++)
				if (children[i])
					return false;
			return true;
		}
	};
public:
	Trie();
	~Trie();

public:
	void insert(const char* key);
	bool search(const char* key)const;
	void remove(const char* key);

public:
	size_t getWordsCount()const;

private:
	bool removeRecursion(Node* currNode, const char* key, int depth);

	int charToIndex(char c) const;

	int getLowercaseIndex(char c)const;

private:
	Node* root;
	size_t wordsCount;


	void free(Node* node);

};