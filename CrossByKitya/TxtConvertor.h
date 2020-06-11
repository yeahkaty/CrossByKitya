#ifndef TXTCONVERTOR_H
#define TXTCONVERTOR_H

#include "Word.h"
#include "Place.h"
#include "Result.h"
#include "Crossword.h"
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


static class TxtConvertor
{
private:
	string resultsPath;
	string crossesPath;
	vector<string> SplitBy(string str, char separator, int from = 0) {
		vector<char> buffer;
		vector<string> result;
		for (int i = from; i < str.length(); i++) {
			if (str[i] == separator) {
				result.push_back(string(buffer.begin(), buffer.end()));
				buffer.clear();
			}
			else {
				buffer.push_back(str[i]);
			}
		}
		result.push_back(string(buffer.begin(), buffer.end()));
		buffer.clear();
		return result;
	}
public:
	vector<Result> SortResults(vector<Result> results)
	{

		sort(results.begin(), results.end(), [](Result a, Result b) { return a.getScores() > b.getScores(); });
		return (results);
	}
	void WriteResults(vector<Result> results)
	{
		//resultsPath = "E:\\универ\\спро\\курсач\\results.txt";
		ofstream out("results.txt");          // поток для записи
		
		//out.open(resultsPath);
		for (int i = 0; i < results.size(); i++)
		{
			out << results[i].getName() << ", " << results[i].getTime() << ", " << results[i].getScores() << ", " << results[i].getData() << endl;
		}
		out.close();
	}
	vector<Result> ReadResults()
	{
		vector<Result> Reads;
		//resultsPath = "E:\\универ\\спро\\курсач\\results.txt";
		ifstream f("results.txt");
		string line;
		int c = 0;
		while (getline(f, line) &&  c<9)
		{
			vector<string> words = SplitBy(line, ',');
			Reads.push_back(Result(words[0], words[1], words[2], words[3]));
			c++;
		}

		return (Reads);
	}
	vector<Crossword> ReadCrosswords()
	{

		//crossesPath = "E:\\универ\\спро\\курсач\\crosses.txt";
		vector<Crossword>result;
		ifstream f("crosses.txt");
		string line1;
		string line2;
		bool IsFirstRow = true;
		Crossword CrosswordNow = Crossword();
		map<Word, Place>mapNow;
				
		while (getline(f, line1))
		{
			if (line1[0] == '$')
			{
				if (IsFirstRow)
				{
					IsFirstRow = false;
				}
				else
				{
					CrosswordNow.setMap(mapNow);
					result.push_back(CrosswordNow);
					CrosswordNow = Crossword();
					mapNow.clear();
				}
				vector<string> crosswordParams = SplitBy(line1, ',', 1);
				CrosswordNow.setSize_horizontal(stoi(crosswordParams[0]));
				CrosswordNow.setSize_vertical(stoi(crosswordParams[1]));
				CrosswordNow.setName(crosswordParams[2]);
				CrosswordNow.setLevel(stoi(crosswordParams[3]));
				CrosswordNow.setDescription(crosswordParams[4]);
				CrosswordNow.setAuthor(crosswordParams[5]);
			}
			else
			{
				//getline(f, line1);
				getline(f, line2);
				vector<string> wordParams = SplitBy(line1, ',');
				Word wordNow = Word(stoi(wordParams[0]), wordParams[1], wordParams[2]);
				vector<string> placeParams = SplitBy(line2, ',');
				Place placeNow = Place(stoi(placeParams[0]), stoi(placeParams[1]), stoi(placeParams[2]));
				mapNow.emplace(pair<Word, Place>(wordNow, placeNow));

				//mapNow[wordNow] = placeNow;
			}
		}
		CrosswordNow.setMap(mapNow);
		if (CrosswordNow.getSize_horizontal() != 0) {
			result.push_back(CrosswordNow);
		}
		
		return (result);
	}
};
#endif