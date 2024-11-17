#pragma once
#include "Trie.h"

//TODO da podsigurq che vski put kato polzvam new se zadelq pravilno pamet
Trie::Trie()
{
	root = new Node();
	wordsCount = 0;
}

Trie::~Trie()
{
	free(root);
	root = nullptr;
	wordsCount = 0;
}

void Trie::insert(const char* key)
{
	int index = 0;
	Node* currNode = root;

	while (*key)
	{
		int index = getLowercaseIndex(*key);
		if (!currNode->children[index])
		{
			try
			{
				currNode->children[index] = new Node();
			}
			catch (const std::bad_alloc& e)
			{
				free(root);
				root = new Node();
				wordsCount = 0;
				throw std::bad_alloc();
			}
		}
		currNode = currNode->children[index];
		++key;
	}

	if (!currNode->isWord)
	{
		currNode->isWord = true;
		++wordsCount;
	}
}

bool Trie::search(const char* key)const
{
	if (!key)
		return false;
	int index = 0;
	Node* currNode = root;
	while (*key) 
	{
		index = getLowercaseIndex(*key);
		if (currNode->children[index] == nullptr)
		{
			return false;
		}
		currNode = currNode->children[index];
		++key;
	}
	return currNode->isWord;
}

void Trie::remove(const char* key)
{
	if (!key)
		return;
	else
		removeRecursion(root, key, 0);
}
bool Trie::removeRecursion(Node* currNode, const char* key, int depth)
{
	if (depth == std::strlen(key)) 
	{
		if (!currNode->isWord)
		{
			return false;
		}
		currNode->isWord = false;
		--wordsCount;
		return currNode->isEmpty();
	}

	int childIndex = getLowercaseIndex(key[depth]);
	Node* node = currNode->children[childIndex];
	if (!node) 
	{
		return false;
	}

	if (removeRecursion(node, key, depth + 1))
	{
		delete node;
		currNode->children[childIndex] = nullptr;
		return !currNode->isWord && currNode->isEmpty();
	}

	return false;
}

size_t Trie::getWordsCount() const
{
	return wordsCount;
}

int Trie::charToIndex(char c) const
{
	return c - 'a';
}

int Trie::getLowercaseIndex(char c)const
{
	if (c >= 'A' && c <= 'Z')
		return charToIndex(c + 32);
	else return charToIndex(c);
}

void Trie::free(Node* node)
{
	if (!node) return;
	for (size_t i = 0; i < alphabetSize; i++)
	{
		if (node->children[i])
			free(node->children[i]);
	}
	delete node;
}
