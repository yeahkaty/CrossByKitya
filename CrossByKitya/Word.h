#ifndef WORD_H
#define  WORD_H
#include <string>
#include <iostream>
using namespace std;
class Word
{
private:
	string description;
	string word;
public:
	int length;
	Word (int l, string d, string w)
	{
		length = l;
		description = d;
		word = w;
	};
	int getLength()
	{
		return length;
	}
	string getDescription()
	{
		return description;
	}
	string getWord()
	{
		return word;
	}
	void setLength(int length)
	{
		this->length = length;
	}
	void setDescription(string description)
	{
		this->description = description;
	}
	void setWord(string word)
	{
		this->word = word;
	}
	bool operator< (const Word& word) const
	{
		if (word.length < this->length)
			return true;
		else
			return false;
	}
};
#endif
