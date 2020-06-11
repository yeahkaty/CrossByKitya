#ifndef RESULT_H
#define RESULT_H
#include <string>
#include <iostream>
using namespace std;
class Result
{
private:
	string name;
	string time;	
	string data;
public:
	string scores;
	Result(string n, string t, string s, string d)
	{
		name = n;
		time = t;
		scores = s;
		data = d;
	};
	string getName() 
	{
		return name;
	}
	string getTime() 
	{
		return time;
	}
	string getScores() 
	{
		return scores;
	}
	string getData()
	{
		return data;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setTime(string time)
	{
		this->time = time;
	}
	void setScores(string scores)
	{
		this->scores = scores;
	}
	void setData(string data)
	{
		this->data = data;
	}
};
#endif