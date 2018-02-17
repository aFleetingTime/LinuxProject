#include "Map.h"
#include <iostream>

Map::Map(Point point) : mSize(point)
{
	for(int i = 0; i < point.getX(); ++i)
	  mMap.push_back(std::vector<Stumb>(point.getY()));
	initMap();
}

void Map::flush()
{
	Snake *snake = Snake::getSnake();
	std::vector<Point> health = snake->getHealth();
	for(auto beg = health.begin(); beg != health.end(); ++beg)
		mMap[beg->getX()][beg->getY()] = SNAKE;
	print();
}

void Map::print()
{
	system("clear");
	std::ostringstream oss;
	for(auto beg = mMap.begin(); beg != mMap.end(); ++beg)
	{
		for(auto ybeg = (*beg).begin(); ybeg != (*beg).end(); ++ybeg)
		{
			switch(*ybeg)
			{
				case SWALL:
					oss << "■";
					break;
				case SNULL:
					oss << " ";
					break;
				case SFOOD:
					oss << "★";
					break;
				case SNAKE:
					oss << "●";
					break;
			}
		}
		oss << '\n';
	}
	std::cout << oss.str() << std::endl;
}

#if 0
void Map::print()
{
	ostringstream map;
	for(auto beg = mMap.begin(); beg != mMap.end(); ++beg)
	{
		for(auto ybeg = (*beg).begin(); ybeg != (*beg).end(); ++ybeg)
		{
			switch(*ybeg)
			{
				case SWALL:
					oss << "■";
					break;
				case SNULL:
					oss << " ";
					break;
				case SFOOD:
					oss << "★";
					break;
				case SNAKE:
					oss << "●";
					break;
			}
		}
	}
}
#endif

//Point Map::mSize;
//std::vector<std::vector<Stumb>> Map::mMap;
void Map::initMap()
{
	for(int i = 0; i < mSize.getX(); ++i)
	{
		if(i != 0 && i != mSize.getX() - 1)
		{
			mMap[i].front() = SWALL;
			mMap[i].back() = SWALL;
			for(auto beg = mMap[i].begin() + 1; beg != mMap[i].end() - 1; ++beg)
				*beg = SNULL;
		}
		else
		{
			for(Stumb &stumb : mMap[i])
			  stumb = SWALL;	

		}
	}
}

