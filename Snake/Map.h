#pragma once
#include "Snake.h"
#include "Stumb.h"
#include <sstream>

class Map
{
public:
	Map(Point point);
	void flush();

private:
	Point mSize;
	void print();
	std::vector<std::vector<Stumb>> mMap;
	void initMap();
};
