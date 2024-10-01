#include <stdio.h>
#include <algorithm>
#define NUM_ALPHABETS 26

int GetNumOfAlphabet(const char* InChar)
{
	return (*InChar - 'a');
}

struct Trie
{
	bool IsTermination = false;
	Trie* Children[NUM_ALPHABETS + 1];

	Trie() : IsTermination(false)
	{
		std::fill_n(Children, Children + NUM_ALPHABETS + 1, nullptr);
	}

	~Trie()
	{
		for (int i = 0; i < NUM_ALPHABETS + 1; ++i)
		{
			if (Children[i] != nullptr)
			{
				delete Children[i];
			}
		}
	}

	void Insert(const char* NextChar)
	{
		if (*NextChar == '\0')
		{
			IsTermination = true;
		}
		else
		{
			if (Children[GetNumOfAlphabet(NextChar)] == nullptr)
			{
				Children[GetNumOfAlphabet(NextChar)] = new Trie();
			}
			Children[GetNumOfAlphabet(NextChar)]->Insert(NextChar + 1);
		}
	}

	Trie* Find(const char* NextChar)
	{
		if (*NextChar == '\0')
		{
			if (IsTermination == true)
			{
				return this;
			}
			else
			{
				return nullptr;
			}
		}
		else if(Children[GetNumOfAlphabet(NextChar)] != nullptr)
		{
			return Children[GetNumOfAlphabet(NextChar)]->Find(NextChar + 1);
		}
		else
		{
			return nullptr;
		}
	}
};