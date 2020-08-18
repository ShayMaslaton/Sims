#pragma once
#include "Point2D.h"

const int MIN_SZ = 40;

class Room
{
public:
	Room();
	~Room();
	Room(Point2D* lt, int w, int h);
	int getWidth();
	int getHeight();
	Point2D* getLeftTop();
	void setLeftTop(Point2D* p);
	void setWidth(int w);
	void setHeight(int h);
	Point2D ChoosePoint();
	Point2D getCenter();

private:
	Point2D* LeftTop;
	int width, height;
};

