#pragma once
class Point
{
public:
	int x;
	int y;
	Point();
	Point(int xCoord, int yCoord);
	void setX(int xCoord);
	void setY(int yCoord);
	void move(int xCoord, int yCoord);
	bool isEqual(const Point& p);

};
