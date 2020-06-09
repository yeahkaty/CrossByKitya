#ifndef CROSSWORD_H
#define CROSSWORD_H
#include "Word.h"
#include "Place.h"
#include <string>
#include <iostream>
#include <map>
using namespace std;
class Crossword
{
private:
	int size_vertical;
	int size_horizontal;
	string name;
	int level;
	string description;
	string author;
	map <Word, Place> wordMap;
public:
	Crossword (int s_v, int s_h, string n, int l, string d, string a, map<Word, Place> w)
	{
		size_vertical = s_v;
		size_horizontal = s_h;
		name = n;
		level = l;
		description = d;
		author = a;
		wordMap = w;
	};
	Crossword()
	{
		size_vertical = 0;
		size_horizontal = 0;
		level = 0;
	};
	int getSize_vertical()
	{
		return size_vertical;
	}
	int getSize_horizontal()
	{
		return size_horizontal;
	}
	string getName()
	{
		return name;
	}
	int getLevel()
	{
		return level;
	}
	string getDescription()
	{
		return description;
	}
	string getAuthor()
	{
		return author;
	}
	map <Word, Place>* getMap()
	{
		return  &wordMap;
	}
	void setSize_vertical(int size_vertical)
	{
		this->size_vertical = size_vertical;
	}
	void setSize_horizontal(int size_horizontal)
	{
		this->size_horizontal = size_horizontal;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setLevel(int level)
	{
		this->level = level;
	}
	void setDescription(string description)
	{
		this->description = description;
	}
	void setAuthor(string author)
	{
		this->author = author;
	}
	void setMap(map <Word, Place> wordMap)
	{
		this->wordMap = wordMap;
	}
};

#endif