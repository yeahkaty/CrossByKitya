#ifndef WORD_H
#define  WORD_H
#include <string>
#include <iostream>
using namespace std;
class Word
{
private:
	int length;
	string description;
	string word;
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

};
#endif
