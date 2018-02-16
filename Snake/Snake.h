#pragma once
#include <vector>
#include "Point.h"
#include "Way.h"

class Snake
{
public:
	Snake(Point point, size_t len);
	void move(Way way);
	std::vector<Point> getHealth();
	void resize(Point point, size_t len);

private:
	std::vector<Point> mHealth;
	size_t mLen;
	Way mWay;
	void back();
};
