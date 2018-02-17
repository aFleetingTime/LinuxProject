#pragma once
#include <vector>
#include "Point.h"
#include "Way.h"

class Snake
{
public:
	void move();
	std::vector<Point> getHealth();
	void resize(Point point, size_t len);
	static Snake *getSnake();
	void setWay(Way way);
	Way getWay();

private:
	Snake();
	static Snake *mSnake;
	std::vector<Point> mHealth;
	size_t mLen;
	Way mWay;
	void back();
};
