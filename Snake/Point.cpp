#include "Point.h"

Point::Point() : mPoint(0, 0) {}
Point::Point(int x, int y) : mPoint(x, y) {}

void Point::setX(int x)
{
	mPoint.first += x;
}
void Point::setY(int y)
{
	mPoint.second += y;
}
int Point::getX()
{
	return mPoint.first;
}
int Point::getY()
{
	return mPoint.second;
}
std::pair<int, int> Point::getXY()
{
	return mPoint;
}
