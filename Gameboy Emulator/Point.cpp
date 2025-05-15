#include "Point.h"
#include<iostream>
using namespace std;
Point::Point()
{
	x = 0;
	y = 0;
}
Point::Point(int xCoord, int yCoord)
{
	x = xCoord;
	y = yCoord;
}
void Point::setX(int xCoord)
{
	x = xCoord;
}
void Point::setY(int yCoord)
{
	y = yCoord;
}
void Point::move(int xCoord, int yCoord)
{
	x += xCoord;
	y += yCoord;
}
bool Point::isEqual(const Point& p)
{
	if (x == p.x && y == p.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}