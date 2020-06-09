#ifndef PLACE_H
#define PLACE_H
#include <string>
#include <iostream>
using namespace std;
class Place
{
	bool isHorizontal;
	int xPlace;
	int yPlace;
public:
	Place (bool g, int x, int y)
	{
		isHorizontal = g;
		xPlace = x;
		yPlace = y;
	};
	Place()
	{

	};
	bool getIsHorizontal()
	{
		return isHorizontal;
	}
	int getXPlace()
	{
		return xPlace;
	}
	int getYPlace()
	{
		return yPlace;
	}
	void setIsHorizontal(bool isHorizontal)
	{
		this->isHorizontal = isHorizontal;
	}
	void setXPlace(int xPlace)
	{
		this->xPlace = xPlace;
	}
	void setYPlace(int yPlace)
	{
		this->yPlace = yPlace;
	}
};
#endif
