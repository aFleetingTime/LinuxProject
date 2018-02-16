#pragma	once 
#include <utility>

class Point
{
public:
	Point();
	Point(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	std::pair<int, int> getXY();

private:
	std::pair<int, int> mPoint;
};
