#include "Snake.h"

Snake::Snake(Point point, size_t len) : mLen(len), mWay(RIGHT)
{
	int x = point.getX() / 2;
	int y = point.getY() / 2;
	for(size_t i = 0; i < mLen; ++i)
	{
		mHealth.push_back(Point(x++, y++));
	}
}

void Snake::move(Way way)
{
	back();
	switch(way)
	{
		case UP:
			mHealth.front().setY(-1);
			break;
		case DOWN:
			mHealth.front().setY(1);
			break;
		case LEFT:
			mHealth.front().setX(-1);
			break;
		case RIGHT:
			mHealth.front().setX(1);
			break;
	}
}

void Snake::back()
{
	for(auto rbeg = mHealth.rbegin(); rbeg != mHealth.rend() - 1; ++rbeg)
	{
		*rbeg = *(rbeg + 1);
	}
}

void Snake::resize(Point point, size_t len)
{
	mLen = len;
	mWay = RIGHT;
	mHealth.resize(0);
	int x = point.getX() / 2;
	int y = point.getY() / 2;
	for(size_t i = 0; i < mLen; ++i)
	{
		mHealth.push_back(Point(x++, y++));
	}
}

