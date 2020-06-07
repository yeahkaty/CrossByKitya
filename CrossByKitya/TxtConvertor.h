#ifndef TXTCONVERTOR_H
#define TXTCONVERTOR_H

#include "Word.h"
#include "Place.h"
#include "Result.h"
#include "Crossword.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;


static class TxtConvertor
{
private:
	string resultsPath;
	string crossesPath;
public:
	void WriteResults(vector<Result> results)
	{
		resultsPath = "E:\\универ\\спро\\курсач\\results.txt";
		ofstream out;          // поток для записи
		out.open(resultsPath);
		for (int i = 0; i < results.size(); i++) 
		{
			out << results[i].getName() <<", " << results[i].getData() << ", " << results[i].getScores() << ", " << results[i].getTime() << endl;
			
		}
		out.close();
	}
};

#endif